#ifndef RPL_ICMP6_MALICIOUS_H_
#define RPL_ICMP6_MALICIOUS_H_

#include "net/routing/rpl-lite/rpl.h"
#include "net/routing/rpl-lite/rpl-const.h"
#include "net/routing/rpl-lite/rpl-icmp6.h"
#include "net/routing/rpl-lite/rpl-timers.h"
#include "net/ipv6/uip-icmp6.h"
#include "net/ipv6/uiplib.h"
#include "net/ipv6/uip.h"
#include "sys/log.h"


bool flood, flooding, select, selecting;
enum rpl_message_length{
  DIO_length = 116,
  DIS_length = 46,
  DAO_length = 98,
  DAO_ACK_length = 56,
  FLOOD_length = 51,
  IDS_length = 68
};
typedef struct neighbor_address {
  uip_ipaddr_t ipaddr;
  bool malicious;
  bool used;
} neighbor_address;
typedef struct pair{
  uint8_t message;
  uint8_t length;
} pair;

neighbor_address neighbors[16];
pair pairs[6];

long int dio_sent_flood;
int icmp_sent;
int icmp_dropped;
int packets_dropped;

void init_pair_array();
void init_rpl_length_array();
void init_neighbors_array();
void rpl_icmp6_flood_init();
void init_flood();
void init_select();
void flood_input();
void rpl_icmp6_malicious_output(uip_ipaddr_t *dest, const void *data, uint16_t datalen);
void malicious_output(uint8_t type);
void add_all_nodes();
void launch_flooding_attack();
bool check_malicious_ip(uip_ipaddr_t *ip);
bool compare_ip_address(uip_ipaddr_t *ip1, uip_ipaddr_t *ip2);
void start_filtering();
void start_flooding();
#endif
