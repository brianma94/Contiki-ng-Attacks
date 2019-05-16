#ifndef RPL_ICMP6_MALICIOUS_H_
#define RPL_ICMP6_MALICIOUS_H_

#include "lib/list.h"
#include "lib/memb.h"
#include "net/routing/rpl-lite/rpl.h"
#include "net/routing/rpl-lite/rpl-const.h"
#include "net/ipv6/uip-icmp6.h"
#include "net/ipv6/uiplib.h"
#include "sys/log.h"

bool flood;
bool selector;
list_t malicious_nodes_list;
list_t legitimate_nodes_list;
typedef struct malicious_address {
  struct malicious_address *next;
  uip_ipaddr_t ipaddr;
} malicious_address;

typedef struct legitimate_address {
  struct legitimate_address *next;
  uip_ipaddr_t ipaddr;
} legitimate_address;

int dis_sent_flood;
int icmp_forwarded;
int icmp_dropped;

void rpl_icmp6_flood_init();
void init_flood();
void init_selector();
void flood_input(void);
void rpl_icmp6_malicious_output(uip_ipaddr_t *dest, const void *data, uint16_t datalen);
void malicious_output();
#endif
