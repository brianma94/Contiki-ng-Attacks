#include "contiki.h"
#include "random.h"
#include "net/netstack.h"
#include "net/routing/rpl-lite/rpl-timers.h"
#include "net/routing/rpl-lite/rpl-icmp6-ids.h"
#include "sys/energest.h"
//#define LOG_MODULE "Node"
//#define LOG_LEVEL LOG_LEVEL_INFO
#define SEND_INTERVAL		  (20 * CLOCK_SECOND)
#define REFRESH_INTERVAL	  (60 * CLOCK_SECOND)
/*---------------------------------------------------------------------------*/
PROCESS(ids_detector_process, "IDS detector");
PROCESS(energest_process, "Monitoring tool");
AUTOSTART_PROCESSES(&ids_detector_process/*, &energest_process*/);
/*---------------------------------------------------------------------------*/
static inline unsigned long
to_seconds(uint64_t time)
{
  return (unsigned long)(time / ENERGEST_SECOND);
}

PROCESS_THREAD(ids_detector_process, ev, data)
{
  static struct etimer periodic_timer;
  static struct etimer refresh_timer;
  PROCESS_BEGIN();
  
  /* Init of IDS detector node stats */
  init_detector();
  
  etimer_set(&periodic_timer, SEND_INTERVAL);
  etimer_set(&refresh_timer,REFRESH_INTERVAL);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    etimer_reset(&periodic_timer);
    
    uip_ipaddr_t root_ip;
    if (rpl_dag_get_root_ipaddr(&root_ip)) {
      printf("Checking stats...\n");
      check_malicious();
      if(etimer_expired(&refresh_timer)) {
	etimer_reset(&refresh_timer);
	printf("Refreshing stats...\n");
	reset_neighbors_stats();
	
      }
    }
    
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(energest_process, ev, data)
{
  static struct etimer et;

  PROCESS_BEGIN();

  // Setup a periodic timer that expires after 10 seconds. 
  etimer_set(&et, CLOCK_SECOND * 10);

  while(1) {
    // Wait for the periodic timer to expire and then restart the timer. 
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
