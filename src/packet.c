#include <stdio.h>
#include <stdint.h>

#include <net/ethernet.h>
#include <netinet/in.h>

#include "eth.h"
#include "ip.h"
#include "tcp.h"
#include "udp.h"
#include "dns.h"
#include "packet.h"

void process_packet(uint8_t *buf, ssize_t size) {
    struct ip_header *ip_hdr = GET_IP_HEADER(buf);

    switch (ip_hdr->protocol) {
        case IPPROTO_TCP:
            printf("***********************TCP Packet*************************\n");
            print_eth_header(buf);
            print_ip_header(buf);
            print_tcp_header(buf);
            print_raw_data(buf, IPPROTO_TCP, size);
            printf("##########################################################\n");
            break;
        case IPPROTO_UDP:
            printf("***********************UDP Packet*************************\n");
            print_eth_header(buf);
            print_ip_header(buf);
            print_udp_header(buf);
            //if (GET_UDP_HEADER(buf)->src_port == 53 || GET_UDP_HEADER(buf)->dest_port == 53) {
                print_dns_header(buf);
                process_dns_packet(buf);
            //} else {
                print_raw_data(buf, IPPROTO_UDP, size);
            //}*/
            printf("##########################################################\n");
        default:
            break;
    }
}

void print_raw_data(uint8_t *buf, const uint8_t PROTO, ssize_t size) {
    uint8_t payload_len, *payload;
    switch (PROTO) {
        case IPPROTO_TCP:
            payload_len = size - sizeof(struct ether_header) - (GET_IP_HEADER(buf)->ihl * 4) - (GET_TCP_HEADER(buf)->data_off * 4);
            payload = buf + sizeof(struct ether_header) + (GET_IP_HEADER(buf)->ihl * 4) + (GET_TCP_HEADER(buf)->data_off * 4);
            break;
        case IPPROTO_UDP:
            payload_len = size - sizeof(struct ether_header) - (GET_IP_HEADER(buf)->ihl * 4) - 8;
            payload = buf + sizeof(struct ether_header) + (GET_IP_HEADER(buf)->ihl * 4) + 8;
            break;
        default:
            return;
    }
    if (payload_len <= 0) {
        printf("\n");
        return;
    }

    printf("\nData Payload\n    ");
    
    for (int i = 0; i < (payload_len - (payload_len % 16)); i++) {
       printf("%02X ", payload[i]);

       if (i % 16 == 15) {
           printf("          ");

           for (int j = i - 15; j <= i; j++) {
               if (payload[j] >= 33 && payload[j] <= 126) {
                   printf("%c", payload[j]);
               } else {
                   printf(".");
               }

           }

           printf("\n    ");
       }
    }

   if (payload_len % 16 != 0) {
       for (int i = payload_len - (payload_len % 16); i < payload_len; i++) {
           printf("%02X ", payload[i]);
       }

       for (int i = payload_len % 16; i < 16; i++) {
           printf("   ");
       }

        printf("          ");

        for (int i = payload_len - (payload_len % 16); i < payload_len; i++) {
            if (payload[i] >= 33 && payload[i] <= 126) {
                printf("%c", payload[i]);
            } else {
                printf(".");
            }
        }

        printf("\n");
   }

   printf("\n");
}
