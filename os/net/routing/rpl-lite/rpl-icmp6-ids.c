#include "net/routing/rpl-lite/rpl-icmp6-ids.h"
#define LOG_MODULE "RPL"
#define LOG_LEVEL LOG_LEVEL_INFO

/* Initialize RPL ICMPv6 Flooding message handler */
UIP_ICMP6_HANDLER(ids_handler, ICMP6_RPL, RPL_CODE_IDS, ids_input);

/* Init the IDS handler */
void rpl_icmp6_ids_init(){
    uip_icmp6_register_input_handler(&ids_handler);
}

/* Init IDS stats */
void init_ids(){
    ids = true;
    init_ids_nodes_array();
    reset_ids_nodes_stats();
}

/* Init IDS detector stats */
void init_detector(){
    detector = true;
    init_neighbors();
    reset_neighbors_stats();
}

/* Initiliaze the information of the neighbors array */
void init_ids_nodes_array(){
    uint8_t i;
    for(i=0; i < (uint8_t)( sizeof(ids_nodes_ip) / sizeof(ids_nodes_ip[0])); ++i){
        ids_nodes_ip[i].used = false;
	ids_nodes_ip[i].hb_sent = 0;
    }
}

/* Reset DIO counter */
void reset_ids_nodes_stats(){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(ids_nodes_ip) / sizeof(ids_nodes_ip[0])); ++i){
    ids_nodes_ip[i].dio_counter = 0;
  }
}

/* Initiliaze the information of the neighbors array */
void init_neighbors(){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(ids_nodes_ip) / sizeof(ids_nodes_ip[0])); ++i){
      ids_nodes_ip[i].used = false;
  }
}

/* Reset the DIO counter of all the nodes */
void reset_neighbors_stats(){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(ids_nodes_ip) / sizeof(ids_nodes_ip[0])); ++i){
    ids_nodes_ip[i].dio_counter = 0; 
  }
}

/* Add HB reply from the node with IP ip */
void add_hb(uip_ipaddr_t * ip){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(ids_nodes_ip) / sizeof(ids_nodes_ip[0])); ++i){
    if (ids_nodes_ip[i].used && compare_address(ip,&ids_nodes_ip[i].ipaddr)) {
      ids_nodes_ip[i].hb_sent = 0;
      return;
    }
  }
}

/*
 * Check HB counter and trigger alarm
 * 1st param: Node IP to check
 * 2nd param: Counter of the node
 */
void manage_heartbeat(uip_ipaddr_t *ip, uint8_t count){
  if (count > HEARTBEAT_MAX){
    char buf[21];
    uiplib_ipaddr_snprint(buf, sizeof(buf), ip);
    printf("Node with ip %s is not reachable. Possible Grayhole or Blackhole attack.\n",buf);
    add_hb(ip);
  }
}

/* Check the DIO counter of every node */
void check_malicious(){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(ids_nodes_ip) / sizeof(ids_nodes_ip[0])); ++i){
    if (ids_nodes_ip[i].used && ids_nodes_ip[i].dio_counter > DIO_THRESHOLD) {
      char buf[21];
      uiplib_ipaddr_snprint(buf, sizeof(buf), &ids_nodes_ip[i].ipaddr);
      printf("Detected attacker %s with count %u\n",buf,ids_nodes_ip[i].dio_counter);
      /* Reset counter */
      ids_nodes_ip[i].dio_counter = 0;
      /* Send alarm message to root with the IP of the attacker */
      uip_ipaddr_t root_ip;
      rpl_dag_get_root_ipaddr(&root_ip);
      rpl_icmp6_ids_output(&root_ip,&ids_nodes_ip[i].ipaddr,16);
    }
  }
}

/*Main ids input function - Receive messages from detectors */
void ids_input(){
 /* Only necessary for the IDS*/
  if (!ids) {
    goto discard;
  }
  
  /* print who was the sender */
  char buf[21];
  uiplib_ipaddr_snprint(buf, sizeof(buf), &UIP_IP_BUF->srcipaddr);
  printf("Received ids_message from: %s\n", buf);
  /*Get the IP of the attacker */
  uip_ipaddr_t target;
  unsigned char *buffer;
  buffer = UIP_ICMP_PAYLOAD;
  memcpy(&target, buffer, 16);
  /* Trigger alarm */
  create_alarm(&target,&UIP_IP_BUF->srcipaddr);
  goto discard;

  discard:
    uipbuf_clear(); //clear the buff to avoid possible errors
}

/*
 * Send message from IDS detector to IDS
 * 1st param: Destination: root IP
 * 2nd param: Payload
 * 3rd param: size of payload
 */
void rpl_icmp6_ids_output(uip_ipaddr_t *dest, const void *data, uint16_t datalen){
  rpl_dag_update_state();
  /* Put the payload in the buffer */
  unsigned char *buffer;
  buffer = UIP_ICMP_PAYLOAD;
  const uip_ipaddr_t *message;
  message = (uip_ipaddr_t *) data;
  memcpy(buffer, message, 16);
  /* Log message */
  char buff[21];
  uiplib_ipaddr_snprint(buff, sizeof(buff), dest);
  printf("Sending a detector message to: %s\n", buff);
  
  /* Send the RPL ICMPv6 message */
  uip_icmp6_send(dest, ICMP6_RPL, RPL_CODE_IDS, datalen);
  
  /* clear the buff to avoid possible errors */
  uipbuf_clear();
}
/*
 * Alarm triggered when IDS receives the message alarm from detector
 * 1st param: Attacker IP
 * 2nd param: IDS detector responsible for the alarm
 */
void create_alarm(uip_ipaddr_t *malicious, uip_ipaddr_t *detector){
  char buffer[21];
  char buf[21];
  uiplib_ipaddr_snprint(buffer, sizeof(buffer), malicious);
  uiplib_ipaddr_snprint(buf, sizeof(buf), detector);
  printf("Received DIO alarm from: %s, detected by %s\n", buffer, buf);
}

/*
 * Discovery task - Get the IP of all the nodes
 */
void add_node_and_update(uip_ipaddr_t *from, char type[3]){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(ids_nodes_ip) / sizeof(ids_nodes_ip[0])); ++i) {
    if(ids_nodes_ip[i].used && compare_address(from,&ids_nodes_ip[i].ipaddr)) {
      if(!strcmp((char *) type,"DIO") && detector) ++ids_nodes_ip[i].dio_counter;
      return;
    }
    else if(!ids_nodes_ip[i].used){
      ids_nodes_ip[i].used = true;
      uip_ipaddr_copy(&ids_nodes_ip[i].ipaddr,from);
      if(!strcmp((char *) type,"DIO") && detector) ++ids_nodes_ip[i].dio_counter;
      return;
    }
  }
}

/* Compare the ip addresses without prefix - without local vs global addresses
 * 1st param: IP 1 to compare
 * 2nd param: IP 2 to compare
 */
bool compare_address(uip_ipaddr_t *ip1, uip_ipaddr_t *ip2) {
  uint8_t i;
  for(i=2;i<8;++i){
    if ((ip1)->u16[i] != (ip2)->u16[i]) return false;
  }
  return true;
}