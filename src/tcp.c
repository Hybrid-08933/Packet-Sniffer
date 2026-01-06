#include <stdio.h>
#include <arpa/inet.h>

#include "ip.h"
#include "tcp.h"

void print_tcp_header(uint8_t *buf) {
    struct ip_header *ip_hdr = GET_IP_HEADER(buf);
    struct tcp_header *tcp_hdr = GET_TCP_HEADER(buf);
    
    printf("\nTCP Header\n");
    printf("  |-Source Port             : %u\n", ntohs(tcp_hdr->src_port));
    printf("  |-Destination Port        : %u\n", ntohs(tcp_hdr->dest_port));
    printf("  |-Sequence Number         : %u\n", ntohl(tcp_hdr->seq_num));
    printf("  |-Acknowledgment Number   : %u\n", ntohl(tcp_hdr->ack_num));
    printf("  |-Header Length           : %u DWORDS or %u Bytes\n", tcp_hdr->data_off, tcp_hdr->data_off * 4);
    printf("  |-Control Bits:\n");
    printf("   |-URG                    : %u\n", tcp_hdr->urg);
    printf("   |-ACK                    : %u\n", tcp_hdr->ack);
    printf("   |-PSH                    : %u\n", tcp_hdr->psh);
    printf("   |-RST                    : %u\n", tcp_hdr->rst);
    printf("   |-SYN                    : %u\n", tcp_hdr->syn);
    printf("   |-FIN                    : %u\n", tcp_hdr->fin);
    printf("  |-Window                  : %u\n", ntohs(tcp_hdr->window));
    printf("  |-Checksum                : %u\n", ntohs(tcp_hdr->check));
    printf("  |-Urgent Pointer          : %u\n", ntohs(tcp_hdr->urg_ptr));
}
