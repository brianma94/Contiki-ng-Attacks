#include "contiki.h"
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "net/routing/rpl-lite/rpl-icmp6-ids.h"
#include "sys/log.h"
#include "random.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

#define WITH_SERVER_REPLY  1
#define UDP_CLIENT_PORT	8765
#define UDP_SERVER_PORT	5678
#define SEND_INTERVAL		  (20 * CLOCK_SECOND)
#define REFRESH_INTERVAL	  (60 * CLOCK_SECOND)
#define HEARTBEAT_INTERVAL       (2*60 * CLOCK_SECOND)
static struct simple_udp_connection udp_conn;

PROCESS(ids_process, "IDS");
PROCESS(heartbeat_process, "HeartBeat protocol");
AUTOSTART_PROCESSES(&ids_process,&heartbeat_process);
/*---------------------------------------------------------------------------*/
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
  LOG_INFO_("\n");
#if WITH_SERVER_REPLY
  /* send back the same string to the client as an echo reply */
  LOG_INFO("Sending response.\n");
  simple_udp_sendto(&udp_conn, data, datalen, sender_addr);
#endif /* WITH_SERVER_REPLY */
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(ids_process, ev, data)
{
  static struct etimer periodic_timer;
  static struct etimer refresh_timer;
  PROCESS_BEGIN();
  etimer_set(&refresh_timer,REFRESH_INTERVAL);
  /* Initialize DAG root */
  NETSTACK_ROUTING.root_start();

  /* Initialize UDP connection */
  simple_udp_register(&udp_conn, UDP_SERVER_PORT, NULL,
                      UDP_CLIENT_PORT, udp_rx_callback);
  init_ids();
  etimer_set(&periodic_timer, SEND_INTERVAL);
  etimer_set(&refresh_timer,REFRESH_INTERVAL);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    etimer_reset(&periodic_timer);
      printf("Checking flood stats...\n");
      check_malicious_ids();
      if(etimer_expired(&refresh_timer)) {
	etimer_reset(&refresh_timer);
	printf("Refreshing flood stats...\n");
	reset_neighbors_stats();
      }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(heartbeat_process, ev, data)
{

  static struct etimer hb_timer;
  PROCESS_BEGIN();
  etimer_set(&hb_timer,HEARTBEAT_INTERVAL);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&hb_timer));
    /* Check for GrayHole or BlackHole attack, update HeartBeat counters and send ECHO REQUEST packet */
    manage_heartbeat();
    etimer_reset_with_new_interval(&hb_timer, 20*CLOCK_SECOND);
  }
  PROCESS_END();
}