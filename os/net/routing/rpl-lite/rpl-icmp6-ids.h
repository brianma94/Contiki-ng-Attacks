#ifndef RPL_ICMP6_IDS_H_
#define RPL_ICMP6_IDS_H_
#include "net/routing/rpl-lite/rpl.h"
#include "net/routing/rpl-lite/rpl-const.h"
#include "net/routing/rpl-lite/rpl-icmp6.h"
#include "net/routing/rpl-lite/rpl-timers.h"
#include "net/ipv6/uip-icmp6.h"
#include "net/ipv6/uiplib.h"
#include "net/ipv6/uip.h"
#include "sys/log.h"
#define DIO_THRESHOLD 15
#define HEARTBEAT_MAX 6
typedef struct addresses_ids{
  uip_ipaddr_t ipaddr;
  bool used;
  int dio_counter;
  uint8_t hb_sent;
  bool hb;
}addresses_ids;

addresses_ids ids_nodes_ip[16];

uint8_t dio_sent, dao_sent, dis_sent;
bool ids, detector;

void rpl_icmp6_ids_init();

void init_ids();
void init_detector();
void init_ids_nodes_array();
void reset_ids_nodes_stats();
void init_neighbors();
void reset_neighbors_stats();
void ids_input();
void create_alarm(uip_ipaddr_t *malicious, uip_ipaddr_t *detector);
void add_node_and_update(uip_ipaddr_t *from, char type[3]);
void check_malicious();
void add_attackers(uip_ipaddr_t *malicious);
void rpl_icmp6_ids_output(uip_ipaddr_t *dest,const void *data, uint16_t datalen);
bool compare_address(uip_ipaddr_t *ip1, uip_ipaddr_t *ip2);
void add_hb(uip_ipaddr_t *ip);
void manage_heartbeat(uip_ipaddr_t *ip, uint8_t count);
#endif