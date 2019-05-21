#include "net/routing/rpl-lite/rpl-icmp6-malicious.h"
#define LOG_MODULE "RPL"
#define LOG_LEVEL LOG_LEVEL_INFO

/* Initialize RPL ICMPv6 Flooding message handler */
UIP_ICMP6_HANDLER(flood_handler, ICMP6_RPL, RPL_CODE_FLOOD, flood_input);

/* Init the flood handler */
void rpl_icmp6_flood_init(){
    uip_icmp6_register_input_handler(&flood_handler);
}

/* Initialize flood node stats & neighbors array */
void init_flood(){

    flood = true;
    flooding = false;
    init_neighbors_array();
    dis_sent_flood = 0;
}

/* Initialize selector node stats */
void init_select(){
    select = true;
    icmp_forwarded = icmp_dropped = 0;
    selecting = false;
}

/* Initiliaze the information of the neighbors array */
void init_neighbors_array(){
    uint8_t i;
    for(i=0; i < (uint8_t)( sizeof(neighbors) / sizeof(neighbors[0])); ++i){
        neighbors[i].malicious = neighbors[i].used = false;
    }
}

/* Main input fuction for RPL Flood ICMPv6 messages */
void flood_input(){
 /* Only necessary for flood attacker nodes*/
  if (!flood) {
    goto discard;
  }
  /* print who was the sender */
  char buf[21];
  uiplib_ipaddr_snprint(buf, sizeof(buf), &UIP_IP_BUF->srcipaddr);
  printf("Received malicious icmp6 from: %s\n", buf);
  
  unsigned char *buffer;
  char message[7];
  buffer = UIP_ICMP_PAYLOAD;
  memcpy(message,buffer,7);
  if(!strcmp(message,"floods") || !strcmp(message,"select")) { //message correct from flood node
    /* Indicate in the neighbors array that the sender is a malicious node */
    uint8_t i;
    for(i=0; i < (uint8_t)( sizeof(neighbors) / sizeof(neighbors[0])); ++i) {
        if (neighbors[i].used) {
            if (uip_ipaddr_cmp(&neighbors[i].ipaddr, &UIP_IP_BUF->srcipaddr)){
                neighbors[i].malicious = true;
                goto discard;
            }
        }
    }
  }
  else printf("Unknown message received - avoided\n"); //message incorrect
  goto discard;
  discard:
    uipbuf_clear(); //clear the buff to avoid possible errors
}

/* RPL ICMP6 Flood message output function. Send the RPL message 
 * 1st param: Destination IP address
 * 2nd param: Message Payload
 * 3rd param: Payload length
*/
void
rpl_icmp6_malicious_output(uip_ipaddr_t *dest, const void *data, uint16_t datalen)
{
  /* Make sure we're up-to-date before sending data out */
  rpl_dag_update_state();
  
  /* Unicast or multicast */
  dest = dest != NULL ? dest : &rpl_multicast_addr;
  
  /* Get the Payload */
  unsigned char *buffer;
  buffer = UIP_ICMP_PAYLOAD;
  memcpy(buffer, data, datalen);
  
  /* Print the destination IP address*/
  char buff[21];
  uiplib_ipaddr_snprint(buff, sizeof(buff), dest);
  printf("Sending a malicious message to: %s\n", buff);
  
  /* Send the RPL ICMPv6 message */
  uip_icmp6_send(dest, ICMP6_RPL, RPL_CODE_FLOOD, datalen);

  /* clear the buff to avoid possible errors */
  uipbuf_clear();
}

/* Used to call the main Output function above. */
void malicious_output(uint8_t type){
    char message[7];
    if (type == 0) { //flooding node
        strcpy(message,"floods"); //message to be sent
    }
    else { //type = 1 --> selector node
        strcpy(message,"select"); //message to be sent
    }
    /* Send the message. 1st Param = NULL indicates multicast destination */
    rpl_icmp6_malicious_output(NULL, &message, sizeof(message));
}

/* Add the neighbors to the neighbors array */
void add_all_nodes(){
    if (flood) {
        uint8_t i;
        for(i=0; i < (uint8_t)( sizeof(neighbors) / sizeof(neighbors[0])); ++i) {
            /* IP address already stored*/
            if (neighbors[i].used && uip_ipaddr_cmp(&neighbors[i].ipaddr, &UIP_IP_BUF->srcipaddr)) return;
            /* IP address not stored - store it and set it as used */
            else if (!neighbors[i].used) {
                neighbors[i].ipaddr = UIP_IP_BUF->srcipaddr;
                neighbors[i].used = true;
                return;
            }   
        }
    }
}

/* Launch the Hello Flood attack */
void launch_flooding_attack(){
      uint8_t i;
      printf("ips: ");
      for(i=0; i < (uint8_t)( sizeof(neighbors) / sizeof(neighbors[0])); ++i) {
            if (neighbors[i].used) {
                char buff[21];
                uiplib_ipaddr_snprint(buff, sizeof(buff), &neighbors[i].ipaddr);
                printf("%s, ", buff);
            }
            else break;
       }
       printf("\n");
}
