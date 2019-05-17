#ifndef RPL_ICMP6_MALICIOUS_H_
#define RPL_ICMP6_MALICIOUS_H_

#include "net/routing/rpl-lite/rpl.h"
#include "net/routing/rpl-lite/rpl-const.h"
#include "net/ipv6/uip-icmp6.h"
#include "net/ipv6/uiplib.h"
#include "net/ipv6/uip.h"
#include "sys/log.h"

bool flood, flooding, selector, selecting;
typedef struct neighbor_address {
  uip_ipaddr_t ipaddr;
  bool malicious;
  bool used;
} neighbor_address;

neighbor_address neighbors[16];
int dis_sent_flood;
int icmp_forwarded;
int icmp_dropped;

void init_neighbors_array();
void rpl_icmp6_flood_init();
void init_flood();
void init_selector();
void flood_input();
void rpl_icmp6_malicious_output(uip_ipaddr_t *dest, const void *data, uint16_t datalen);
void malicious_output();
void add_all_nodes();
void launch_flooding_attack();
#endif
