#include "net/routing/rpl-lite/rpl-icmp6-malicious.h"
#define LOG_MODULE "RPL"
#define LOG_LEVEL LOG_LEVEL_INFO

MEMB(malicious_list_memory, struct malicious_address, 16);
MEMB(legitimate_list_memory, struct legitimate_address, 16);
UIP_ICMP6_HANDLER(flood_handler, ICMP6_RPL, RPL_CODE_FLOOD, flood_input);

void rpl_icmp6_flood_init(){
    uip_icmp6_register_input_handler(&flood_handler);
}

void init_flood(){

    flood = true;
    memb_init(&malicious_list_memory);
    list_init(malicious_nodes_list);
    memb_init(&legitimate_list_memory);
    list_init(legitimate_nodes_list);
    dis_sent_flood = 0;
}

void init_selector(){
    selector = true;
    icmp_forwarded = icmp_dropped = 0;
}

void flood_input(void){
 /* Only necessary for flood attacker nodes*/
  if (!flood) {
    goto discard;
  }

  uip_ipaddr_t source;
  uip_ipaddr_copy(&source, &UIP_IP_BUF->srcipaddr);
  
  char buf[21];
  uiplib_ipaddr_snprint(buf, sizeof(buf), &source);
  printf("Received malicious icmp6 from: %s\n", buf);
  
  unsigned char *buffer;
  char message[10];
  buffer = UIP_ICMP_PAYLOAD;
  memcpy(message,buffer,10);
  if(!strcmp(message,"malicious")) {
      struct malicious_address *i;
      for(i = list_head(malicious_nodes_list); i != NULL; i = list_item_next(i)) {
        if (uip_ipaddr_cmp(&source,&i->ipaddr)) goto discard; // IP address is already in the list, nothing to do
      }
      /* IP address is not in the list yet */
      i = memb_alloc(&malicious_list_memory);
      uip_ipaddr_copy(&i->ipaddr, &source);
      list_add(malicious_nodes_list, i);
  }
  else printf("Unknown message received - avoided\n");
  goto discard;
  discard:
    uipbuf_clear();
}

void
rpl_icmp6_malicious_output(uip_ipaddr_t *dest, const void *data, uint16_t datalen)
{

    /* Make sure we're up-to-date before sending data out */
  rpl_dag_update_state();
    uipbuf_clear();
  dest = dest != NULL ? dest : &rpl_multicast_addr;
  unsigned char *buffer;
  buffer = UIP_ICMP_PAYLOAD;
  memcpy(buffer, data, datalen);
  
  char buff[21];
  uiplib_ipaddr_snprint(buff, sizeof(buff), dest);
  printf("sending a malicious message to: %s\n", buff);
  uip_icmp6_send(dest, ICMP6_RPL, RPL_CODE_FLOOD, datalen);
  uipbuf_clear();

}

void malicious_output(){
    char message[10];
    strcpy(message,"malicious");
    rpl_icmp6_malicious_output(NULL, &message, sizeof(message));
}
