#ifndef TCP_H
#define TCP_H

#include <stdint.h>

#include <endian.h>
#include <net/ethernet.h>

#include "ip.h"

#define GET_TCP_HEADER(buf) ((struct tcp_header *) (buf + sizeof(struct ether_header) + (((struct ip_header *) (buf + (sizeof(struct ether_header))))->ihl * 4)))

struct tcp_header {
    uint16_t src_port;
    uint16_t dest_port;
    uint32_t seq_num;
    uint32_t ack_num;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	uint16_t res1:4;
	uint16_t data_off:4;
	uint16_t fin:1;
	uint16_t syn:1;
	uint16_t rst:1;
	uint16_t psh:1;
	uint16_t ack:1;
	uint16_t urg:1;
	uint16_t res2:2;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	uint16_t data_off:4;
	uint16_t res1:4;
	uint16_t res2:2;
	uint16_t urg:1;
	uint16_t ack:1;
	uint16_t psh:1;
	uint16_t rst:1;
	uint16_t syn:1;
	uint16_t fin:1;
#endif
    uint16_t window;
    uint16_t check;
    uint16_t urg_ptr;
} __attribute__((packed));

void print_tcp_header(uint8_t *buf);

#endif
