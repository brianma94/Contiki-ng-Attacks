#include "contiki.h"
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include "sys/energest.h"
#include "net/routing/rpl-lite/rpl-icmp6-ids.h"
#include "sys/log.h"
#include "random.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

#define WITH_SERVER_REPLY  1
#define UDP_CLIENT_PORT	8765
#define UDP_SERVER_PORT	5678
#define SEND_INTERVAL		  (5*60 * CLOCK_SECOND)
#define REFRESH_INTERVAL	  (60 * CLOCK_SECOND)
#define HEARTBEAT_INTERVAL       (5*60 * CLOCK_SECOND)
static struct simple_udp_connection udp_conn;

PROCESS(ids_process, "IDS");
PROCESS(energest_process, "Monitoring tool");
AUTOSTART_PROCESSES(&ids_process,&energest_process);
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
  LOG_INFO("Received reply '%.*s' from ", datalen, (char *) data);
  LOG_INFO_6ADDR(sender_addr);
  LOG_INFO_("\n");
  add_hb((uip_ipaddr_t *)sender_addr);
#if WITH_SERVER_REPLY
  /* send back the same string to the client as an echo reply */
  //LOG_INFO("Sending response.\n");
  //simple_udp_sendto(&udp_conn, data, datalen, sender_addr);
#endif /* WITH_SERVER_REPLY */
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(ids_process, ev, data)
{
  static struct etimer periodic_timer;
  static char str[32];
  
  PROCESS_BEGIN();
  /* Initialize DAG root */
  NETSTACK_ROUTING.root_start();

  /* Initialize UDP connection */
  simple_udp_register(&udp_conn, UDP_SERVER_PORT, NULL,
                      UDP_CLIENT_PORT, udp_rx_callback);
  /* Init IDS stadistics */
  init_ids();
  
  etimer_set(&periodic_timer, SEND_INTERVAL);
  while(1) {
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic_timer));
    /* 'hello' <-- Heartbeat UDP Request Payload */
    snprintf(str, sizeof(str), "hello");
    /* Send HB Request to all the nodes */
    uint8_t i;
    for(i=0; i < (uint8_t)( sizeof(ids_nodes_ip) / sizeof(ids_nodes_ip[0])) && ids_nodes_ip[i].used; ++i){
      /* Check Counter first */
      manage_heartbeat(&ids_nodes_ip[i].ipaddr,ids_nodes_ip[i].hb_sent);
      /* Send message */
      simple_udp_sendto(&udp_conn, str, strlen(str), &ids_nodes_ip[i].ipaddr);
      LOG_INFO("Sending request to ");
      LOG_INFO_6ADDR(&ids_nodes_ip[i].ipaddr);
      LOG_INFO_("\n");
      /* Increase counter */
      ++ids_nodes_ip[i].hb_sent;
    }
    etimer_reset_with_new_interval(&periodic_timer, 20*CLOCK_SECOND);
  }

  PROCESS_END();
}
PROCESS_THREAD(energest_process, ev, data)
{
  static struct etimer et;

  PROCESS_BEGIN();

  // Setup a periodic timer that expires after 10 seconds. 
  etimer_set(&et, CLOCK_SECOND * 10);
  //etimer_set(&et, CLOCK_SECOND * 60*15);

  while(1) {
    // Wait for the periodic timer to expire and then restart the timer. 
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
