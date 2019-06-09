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

typedef struct addresses {
  uip_ipaddr_t ipaddr;
  bool used;
  int dio_counter;
} addresses;

/*typedef struct ids_detector_address {
  uip_ipaddr_t ipaddr;
  bool used;
} ids_detector_address;

typedef struct ids_message{
  uip_ipaddr_t ipaddr;
  char message[9];
} ids_message;*/

addresses neighbors_ip[16];
addresses ids_nodes_ip[16];
//ids_detector_address ids_detectors_ip[10];

uint8_t dio_sent, dao_sent, dis_sent;
bool ids, detector;

void rpl_icmp6_ids_init();
void rpl_icmp6_detector_init();
void init_ids();
void init_detector();
void init_ids_nodes_array();
void reset_ids_nodes_stats();
void init_neighbors();
void reset_neighbors_stats();
void ids_input();
void detector_input();
void add_detector(uip_ipaddr_t *from, uint8_t pos);
void create_alarm(uip_ipaddr_t *malicious, uip_ipaddr_t *detector);
void add_node_and_update(uip_ipaddr_t *from, char type[3]);
void add_node_and_update_IDS(uip_ipaddr_t *from, char type[3]);
void check_malicious();
void add_attackers(uip_ipaddr_t *malicious);
void rpl_icmp6_ids_output(uip_ipaddr_t *dest,const void *data, uint16_t datalen);
bool compare_address(uip_ipaddr_t *ip1, uip_ipaddr_t *ip2);
#endif