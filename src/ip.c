#include <stdio.h>

#include <arpa/inet.h>

#include "ip.h"

void print_ip_header(uint8_t *buf) {
    struct ip_header *ip_hdr = GET_IP_HEADER(buf);
    char addr_buf[INET_ADDRSTRLEN];

    printf("\nIP Header\n");
    printf("  |-IP Version              : %u\n", ip_hdr->version);
    printf("  |-Header Length           : %u DWORDS or %u Bytes\n", ip_hdr->ihl, ip_hdr->ihl * 4);
    printf("  |-Type Of Service         : %u\n", ip_hdr->tos);
    printf("  |-Total Length            : %u\n", ntohs(ip_hdr->total_length));
    printf("  |-Identification          : %u\n", ntohs(ip_hdr->id));
    printf("  |-Control Flags:\n");
    printf("   |-DF:                    : %u\n", ip_hdr->df);
    printf("   |-MF:                    : %u\n", ip_hdr->mf);
    printf("  |-Fragment Offset         : %u\n", ntohs(ip_hdr->frag_off));
    printf("  |-Time To Live            : %u\n", ip_hdr->ttl);
    printf("  |-Protocol                : %u\n", ip_hdr->protocol);
    printf("  |-Header Checksum         : %u\n", ntohs(ip_hdr->check));
    printf("  |-Source Address          : %s\n", inet_ntop(AF_INET, &(ip_hdr->src_addr), addr_buf, (socklen_t) INET_ADDRSTRLEN));
    printf("  |-Destination Address     : %s\n", inet_ntop(AF_INET, &(ip_hdr->dest_addr), addr_buf, (socklen_t) INET_ADDRSTRLEN));
}
