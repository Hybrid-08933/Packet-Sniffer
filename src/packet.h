#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

void process_packet(uint8_t *buf, ssize_t size);
void print_raw_data(uint8_t *buf, uint8_t PROTO, ssize_t size);

#endif
