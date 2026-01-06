#include <stdio.h>
#include <stdint.h>

#include <arpa/inet.h>

#include "udp.h"

void print_udp_header(uint8_t *buf) {
    struct udp_header *udp_hdr = GET_UDP_HEADER(buf);

    printf("\nUDP Header\n");
    printf("  |-Source Port             : %u\n", ntohs(udp_hdr->src_port));
    printf("  |-Destination Port        : %u\n", ntohs(udp_hdr->dest_port));
    printf("  |-Total Length            : %u\n", ntohs(udp_hdr->total_length));
    printf("  |-Checksum                : %u\n", ntohs(udp_hdr->check));
}
