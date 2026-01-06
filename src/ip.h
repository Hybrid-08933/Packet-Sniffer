#ifndef IP_H
#define IP_H

#include <stdint.h>

#include <endian.h>
#include <net/ethernet.h>

#define GET_IP_HEADER(buf) ((struct ip_header *) (buf + sizeof(struct ether_header)))

struct ip_header {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    uint8_t     ihl:4,
                version:4;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint8_t     version:4,
                ihl:4;
#endif
    uint8_t     tos;
    uint16_t    total_length;
    uint16_t    id;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    uint16_t    frag_off:13;
    uint16_t    mf:1;
    uint16_t    df:1;
    uint16_t    res:1;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint16_t    res:1;
    uint16_t    df:1;
    uint16_t    mf:1;
    uint16_t    frag_off:13;
#endif
    uint8_t     ttl;
    uint8_t     protocol;
    uint16_t    check;
    uint32_t    src_addr;
    uint32_t    dest_addr;
} __attribute__((packed));

void print_ip_header(uint8_t *buf);

#endif
