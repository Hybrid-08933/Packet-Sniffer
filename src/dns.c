#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <arpa/inet.h>

#include "udp.h"
#include "dns.h"

void print_dns_header(uint8_t *buf) {
    struct dns_header *dns_hdr = GET_DNS_HEADER(buf);

    printf("\nDNS Header\n");
    printf("  |-ID                      : %u\n", ntohs(dns_hdr->id));
    printf("  |-Control Flags:\n");
    printf("   |-QR                     : %u\n", dns_hdr->qr);
    printf("   |-OP Code                : %u\n", dns_hdr->op_code);
    printf("   |-AA                     : %u\n", dns_hdr->aa);
    printf("   |-TC                     : %u\n", dns_hdr->tc);
    printf("   |-RD                     : %u\n", dns_hdr->rd);
    printf("   |-RA                     : %u\n", dns_hdr->ra);
    printf("   |-R Code                 : %u\n", dns_hdr->r_code);
    printf("  |-QD Count                : %u\n", ntohs(dns_hdr->qd_count));
    printf("  |-AN Count                : %u\n", ntohs(dns_hdr->an_count));
    printf("  |-NS Count                : %u\n", ntohs(dns_hdr->ns_count));
    printf("  |-AR Count                : %u\n", ntohs(dns_hdr->ar_count));
}

void process_dns_packet(uint8_t *buf) {
    struct dns_header *dns_hdr = GET_DNS_HEADER(buf);
    struct dns_question dns_q;
    dns_q.size = 0;

    if (dns_hdr->qd_count > 0) {
        dns_q.q_name = (uint8_t *) ((uint8_t *) dns_hdr + 12);
        uint8_t *dns_buf = dns_q.q_name;
        int num_of_words = 0;

        while (*dns_buf != 0) {
            num_of_words++;
            dns_q.size += *dns_buf + 1;
            dns_buf = dns_buf + *dns_buf + 1;
        }
        dns_q.size += 1;

        uint8_t *domain_buf = malloc(dns_q.size - 1);
        dns_buf = dns_q.q_name;
        int i = 0;
        int j = 0;
        while (i < num_of_words) {
            for (int i = 0; i < *(dns_buf); i++) {
                snprintf(domain_buf + j, 2, "%c", *(dns_buf + i + 1));
                j++;
            }
            snprintf(domain_buf + j, 2, ".");
            dns_buf = dns_buf + *dns_buf + 1;
            i++;
            j++;
        }

        domain_buf[dns_q.size - 2] = '\0';
        dns_q.domain = domain_buf;

        memcpy(((uint8_t *) &dns_q) + sizeof(uint8_t *), dns_buf + 1, sizeof(uint16_t) * 2);
        //dns_q.q_type =  ntohs(*((uint16_t *) (dns_buf + 1)));
        //dns_q.q_class = ntohs(*((uint16_t *) (dns_buf + 3)));
        dns_q.size += sizeof(uint16_t) * 2;
    }

    printf("\nDNS Question\n");
    printf("  |-Question Type  : %u\n", ntohs(dns_q.q_type));
    printf("  |-Question Class : %u\n", ntohs(dns_q.q_class));
    printf("  |-Length:        : %u\n", dns_q.size);
    printf("  |-Domain:        : %s\n", dns_q.domain);
}
