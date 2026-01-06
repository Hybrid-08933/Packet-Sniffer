#ifndef DNS_H
#define DNS_H

#include <stdint.h>

#include "udp.h"

#define GET_DNS_HEADER(buf) (struct dns_header *) (((uint8_t *) GET_UDP_HEADER(buf)) + 8)

struct dns_header {
    uint16_t id;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    uint16_t rd:1;
    uint16_t tc:1;
    uint16_t aa:1;
    uint16_t op_code:4;
    uint16_t qr:1;
    uint16_t r_code:4;
    uint16_t res:3;
    uint16_t ra:1;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint16_t qr:1;
    uint16_t op_code:4;
    uint16_t aa:1;
    uint16_t tc:1;
    uint16_t rd:1;
    uint16_t ra:1;
    uint16_t res:3;
    uint16_t r_code:4;
#endif
    uint16_t qd_count;
    uint16_t an_count;
    uint16_t ns_count;
    uint16_t ar_count;
} __attribute__((packed));

struct dns_question {
    uint8_t *q_name;
    uint16_t q_type;
    uint16_t q_class;
    uint8_t size;
    uint8_t *domain;
} __attribute__((packed));

struct dns_packet {
} __attribute__((packed));

void print_dns_header(uint8_t *buf);

void process_dns_packet(uint8_t *buf);

#endif
