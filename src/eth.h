#ifndef ETH_H
#define ETH_H

#include <stdint.h>

#include <net/ethernet.h>

uint8_t *ethernet_ntoa(const struct ether_addr *addr, uint8_t *buf);
uint8_t *ethernet_proto_ntop(const uint16_t ether_type, uint8_t *buf);

void print_eth_header(uint8_t *buf);

#endif
