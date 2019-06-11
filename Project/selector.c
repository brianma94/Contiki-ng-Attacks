#include "contiki.h"
#include "random.h"
#include "net/netstack.h"
#include "net/routing/rpl-lite/rpl-timers.h"
#include "net/routing/rpl-lite/rpl-icmp6-malicious.h"
#include "sys/energest.h"
//#define LOG_MODULE "App"
//#define LOG_LEVEL LOG_LEVEL_INFO
#define SEND_INTERVAL		  (480 * CLOCK_SECOND) /*attack in 16min*/
//#define ATTACK_START          SEND_INTERVAL

/*---------------------------------------------------------------------------*/
PROCESS(udp_client_process, "UDP client");
PROCESS(selecting_process, "Selector");
PROCESS(energest_process, "Monitoring tool");
AUTOSTART_PROCESSES(&udp_client_process, &energest_process);
/*---------------------------------------------------------------------------*/
static inline unsigned long
to_seconds(uint64_t time)
{
  return (unsigned long)(time / ENERGEST_SECOND);
}

PROCESS_THREAD(udp_client_process, ev, data)
{
  static struct etimer periodic_timer;
  static bool first = true;
  PROCESS_BEGIN();

  /* Init of flooding node stats */
  init_select();
  etimer_set(&periodic_timer, SEND_INTERVAL);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    //We just want to send the RPL packet once
    if (first) {
        first = false;
        malicious_output(1);
    }
    else { //in the next timer expiration, start flood attack process & stop this timer
        etimer_stop(&periodic_timer);    
        process_start(&selecting_process, NULL);
    }
    /* Add some jitter */
    etimer_set(&periodic_timer, SEND_INTERVAL
      - CLOCK_SECOND + (random_rand() % (2 * CLOCK_SECOND)));
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(selecting_process, ev, data)
{
  static struct etimer timer;
  PROCESS_BEGIN();
  
  start_filtering(); //selecting mode on

  etimer_set(&timer, CLOCK_SECOND);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    if (selecting) {
        /* Launch attack - start after 16min of simulation*/
        printf("DATA packets dropped: %d\n", packets_dropped);
        printf ("ICMP packets dropped: %d, total: %d\n",icmp_dropped, icmp_total);
       // etimer_stop(&timer);
       etimer_reset_with_new_interval(&timer, 5*CLOCK_SECOND);
    }
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(energest_process, ev, data)
{
  static struct etimer et;

  PROCESS_BEGIN();

  /* Setup a periodic timer that expires after 10 seconds. */
  etimer_set(&et, CLOCK_SECOND * 10);

  while(1) {
    /* Wait for the periodic timer to expire and then restart the timer. */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    etimer_reset(&et);

    energest_flush();

    printf("\nEnergest:\n");
    printf(" CPU          %4lus LPM      %4lus DEEP LPM %4lus  Total time %lus\n",
           to_seconds(energest_type_time(ENERGEST_TYPE_CPU)),
           to_seconds(energest_type_time(ENERGEST_TYPE_LPM)),
           to_seconds(energest_type_time(ENERGEST_TYPE_DEEP_LPM)),
           to_seconds(ENERGEST_GET_TOTAL_TIME()));
    printf(" Radio LISTEN %4lus TRANSMIT %4lus OFF      %4lus\n",
           to_seconds(energest_type_time(ENERGEST_TYPE_LISTEN)),
           to_seconds(energest_type_time(ENERGEST_TYPE_TRANSMIT)),
           to_seconds(ENERGEST_GET_TOTAL_TIME()
                      - energest_type_time(ENERGEST_TYPE_TRANSMIT)
- energest_type_time(ENERGEST_TYPE_LISTEN)));

  }

  PROCESS_END();
}
