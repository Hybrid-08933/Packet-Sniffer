#ifndef UDP_H
#define UDP_H

#include <stdint.h>

#include <net/ethernet.h>

#include "ip.h"

#define GET_UDP_HEADER(buf) ((struct udp_header *) (buf + sizeof(struct ether_header) + (((struct ip_header *) (buf + (sizeof(struct ether_header))))->ihl * 4)))

struct udp_header {
    uint16_t src_port;
    uint16_t dest_port;
    uint16_t total_length;
    uint16_t check;
} __attribute__((packed));

void print_udp_header(uint8_t *buf);

#endif
