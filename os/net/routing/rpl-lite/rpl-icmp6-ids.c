#include "net/routing/rpl-lite/rpl-icmp6-ids.h"
#define LOG_MODULE "RPL"
#define LOG_LEVEL LOG_LEVEL_INFO
#define DIO_THRESHOLD 10
/* Initialize RPL ICMPv6 Flooding message handler */
UIP_ICMP6_HANDLER(ids_handler, ICMP6_RPL, RPL_CODE_IDS, ids_input);
UIP_ICMP6_HANDLER(detector_handler, ICMP6_RPL, RPL_CODE_DETECTOR, detector_input);

/* Init the flood handler */
void rpl_icmp6_ids_init(){
    uip_icmp6_register_input_handler(&ids_handler);
}

/* Init the flood handler */
void rpl_icmp6_detector_init(){
    uip_icmp6_register_input_handler(&detector_handler);
}
void init_ids(){
    ids = true;
    init_ids_nodes_array();
    reset_ids_nodes_stats();
}

void init_detector(){
    detector = true;
    init_neighbors();
    reset_neighbors_stats();
    //init detect
}

/* Initiliaze the information of the neighbors array */
void init_ids_nodes_array(){
    uint8_t i;
    for(i=0; i < (uint8_t)( sizeof(ids_nodes_ip) / sizeof(ids_nodes_ip[0])); ++i){
        ids_nodes_ip[i].used = false;
    }
}

void reset_ids_nodes_stats(){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(ids_nodes_ip) / sizeof(ids_nodes_ip[0])); ++i){
    ids_nodes_ip[i].dio_counter = 0;
  }
}

void check_malicious(){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(neighbors_ip) / sizeof(neighbors_ip[0])); ++i){
    if (neighbors_ip[i].used && neighbors_ip[i].dio_counter > DIO_THRESHOLD) {
      /*ids_message message;
      strcpy(message.message,"warn_DIO");
      uip_ipaddr_copy(&message.ipaddr,&neighbors_ip[i].ipaddr);*/
      char buf[21];
      uiplib_ipaddr_snprint(buf, sizeof(buf), &neighbors_ip[i].ipaddr);
      printf("Detected attacker %s with count %u\n",buf,neighbors_ip[i].dio_counter);
      uip_ipaddr_t root_ip;
      rpl_dag_get_root_ipaddr(&root_ip);
      //rpl_icmp6_ids_output(&root_ip,&message,sizeof(message));
      rpl_icmp6_ids_output(&root_ip,&neighbors_ip[i].ipaddr,16);
    }
  }
}

/* Initiliaze the information of the neighbors array */
void init_neighbors(){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(neighbors_ip) / sizeof(neighbors_ip[0])); ++i){
      neighbors_ip[i].used = false;
  }
}

void reset_neighbors_stats(){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(neighbors_ip) / sizeof(neighbors_ip[0])); ++i){
    neighbors_ip[i].dio_counter = 0; 
  }
}

void ids_input(){
 /* Only necessary for flood attacker nodes*/
  if (!ids) {
    goto discard;
  }
  
  /* print who was the sender */
  char buf[21];
  uiplib_ipaddr_snprint(buf, sizeof(buf), &UIP_IP_BUF->srcipaddr);
  printf("Received ids_message from: %s\n", buf);
  uip_ipaddr_t target;
  //int j = 0;
  unsigned char *buffer;
  //char message[9];
  buffer = UIP_ICMP_PAYLOAD;
  //memcpy(message,buffer,9);
  //j += 9;
  //if(!strcmp(message,"DETECTOR")) { //message correct from flood node
//    uint8_t i;
    /* Check if we already know this detector */
    /*for(i=0; i < (uint8_t)( sizeof(ids_detectors_ip) / sizeof(ids_detectors_ip[0])) && ids_detectors_ip[i].used; ++i) {
      if (compare_address(&UIP_IP_BUF->srcipaddr,&ids_detectors_ip[i].ipaddr)) {
	goto discard;
      }
    }*/
    /* It is a new detector, we add it to the detectors array */
   // add_detector(&UIP_IP_BUF->srcipaddr,i);
    //goto discard;
 // }
  //else{
    memcpy(&target, buffer, 16);
    create_alarm(&target,&UIP_IP_BUF->srcipaddr);
    goto discard;
  //}
  //goto discard;
  discard:
    uipbuf_clear(); //clear the buff to avoid possible errors
}


void detector_input(){
 /* Only necessary for flood attacker nodes*/
  if (!detector) {
    goto discard;
  }
  /* print who was the sender */
  /*char buf[21];
  uiplib_ipaddr_snprint(buf, sizeof(buf), &UIP_IP_BUF->srcipaddr);
  printf("Received ids_message from: %s\n", buf);
  uip_ipaddr_t target;
  unsigned char *buffer;
  char message[4];
  buffer = UIP_ICMP_PAYLOAD;
  memcpy(message,buffer,4);
  if(!strcmp(message,"GET")) { //message correct from flood node
      chardata = check_stats();
      if(check_stats() != -1){
	  uip_ipaddr_t root_ip;
          rpl_dag_get_root_ipaddr(&root_ip);
	  char data[size+1];
	  rpl_icmp6_ids_output(&root_ip, &message, sizeof(message));
      }
  }  */
  discard:
    uipbuf_clear(); //clear the buff to avoid possible errors
}

void rpl_icmp6_ids_output(uip_ipaddr_t *dest, const void *data, uint16_t datalen){
  rpl_dag_update_state();
  
  unsigned char *buffer;
  buffer = UIP_ICMP_PAYLOAD;
  const uip_ipaddr_t *message;
  message = (uip_ipaddr_t *) data;
  //memcpy(buffer, &message->message, 9);
  memcpy(buffer, message, 16);
  char buff[21];
  uiplib_ipaddr_snprint(buff, sizeof(buff), dest);
  printf("Sending a detector message to: %s\n", buff);
  
  /* Send the RPL ICMPv6 message */
  uip_icmp6_send(dest, ICMP6_RPL, RPL_CODE_IDS, datalen);
  /* clear the buff to avoid possible errors */
  uipbuf_clear();
}
void add_detector(uip_ipaddr_t *from, uint8_t pos){
  /* uip_ipaddr_copy(&ids_detectors_ip[pos].ipaddr,from);
   ids_detectors_ip[pos].used = true;*/
}

void create_alarm(uip_ipaddr_t *malicious, uip_ipaddr_t *detector){
  char buffer[21];
  char buf[21];
  uiplib_ipaddr_snprint(buffer, sizeof(buffer), malicious);
  uiplib_ipaddr_snprint(buf, sizeof(buf), detector);
  printf("Received DIO alarm from: %s, detected by %s\n", buffer, buf);
}

void add_node_and_update(uip_ipaddr_t *from, char type[3]){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(neighbors_ip) / sizeof(neighbors_ip[0])); ++i) {
    if(neighbors_ip[i].used && compare_address(from,&neighbors_ip[i].ipaddr)) {
      if(!strcmp((char *) type,"DIO")) ++neighbors_ip[i].dio_counter;
      return;
    }
    else if(!neighbors_ip[i].used){
      neighbors_ip[i].used = true;
      uip_ipaddr_copy(&neighbors_ip[i].ipaddr,from);
      if(!strcmp((char *) type,"DIO")) ++neighbors_ip[i].dio_counter;
      return;
    }
  }
}

void add_node_and_update_IDS(uip_ipaddr_t *from, char type[3]){
  uint8_t i;
  for(i=0; i < (uint8_t)( sizeof(ids_nodes_ip) / sizeof(ids_nodes_ip[0])); ++i) {
    if(ids_nodes_ip[i].used && compare_address(from,&ids_nodes_ip[i].ipaddr)) {
      if(!strcmp((char *) type,"DIO")) ++ids_nodes_ip[i].dio_counter;
      return;
    }
    else if (!ids_nodes_ip[i].used){
      ids_nodes_ip[i].used = true;
      uip_ipaddr_copy(&ids_nodes_ip[i].ipaddr,from);
      if(!strcmp((char *) type,"DIO")) ++ids_nodes_ip[i].dio_counter;
      return;
    }
  }
}
/* Compare the ip addresses without prefix - without local vs global addresses */
bool compare_address(uip_ipaddr_t *ip1, uip_ipaddr_t *ip2) {
  uint8_t i;
  for(i=2;i<8;++i){
    if ((ip1)->u16[i] != (ip2)->u16[i]) return false;
  }
  return true;
}