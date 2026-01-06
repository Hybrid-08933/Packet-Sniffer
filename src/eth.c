#include <stdio.h>

#include <arpa/inet.h>
#include <net/ethernet.h>

#include "eth.h"

uint8_t *ethernet_ntoa(const struct ether_addr *addr, uint8_t *buf) {
    snprintf((char *) buf, 18, "%02X:%02X:%02X:%02X:%02X:%02X",
        addr->ether_addr_octet[0], addr->ether_addr_octet[1],
        addr->ether_addr_octet[2], addr->ether_addr_octet[3],
        addr->ether_addr_octet[4], addr->ether_addr_octet[5]);

    return buf;
}

uint8_t *ethernet_proto_ntop(const uint16_t ether_type, uint8_t *buf) {
    switch (ether_type) {
        case ETHERTYPE_PUP:         snprintf((char *) buf, 20, "Xerox PUP");
                                    return buf;
        case ETHERTYPE_SPRITE:      snprintf((char *) buf, 20, "Sprite");
                                    return buf;
        case ETHERTYPE_IP:          snprintf((char *) buf, 20, "IPv4");
                                    return buf;
        case ETHERTYPE_ARP:         snprintf((char *) buf, 20, "Address Resolution");
                                    return buf;
        case ETHERTYPE_REVARP:      snprintf((char *) buf, 20, "Reverse ARP");
                                    return buf;
        case ETHERTYPE_AT:          snprintf((char *) buf, 20, "AppleTalk Protocol");
                                    return buf;
        case ETHERTYPE_AARP:        snprintf((char *) buf, 20, "AppleTalk ARP");
                                    return buf;
        case ETHERTYPE_VLAN:        snprintf((char *) buf, 20, "802.1Q VLAN tagging");
                                    return buf;
        case ETHERTYPE_IPX:         snprintf((char *) buf, 20, "IPX");
                                    return buf;
        case ETHERTYPE_IPV6:        snprintf((char *) buf, 20, "IPv6");
                                    return buf;
        case ETHERTYPE_LOOPBACK:    snprintf((char *) buf, 20, "LOOPBACK");
                                    return buf;
        default:                    snprintf((char *) buf, 20, "Error");
                                    return buf;
    }
}

void print_eth_header(uint8_t *buf) {
    struct ether_header *eth_hdr = (struct ether_header *) buf;
    uint8_t addr_buf[20];

    printf("\nEthernet Header\n");
    printf("  |-Source Address          : %s\n", ethernet_ntoa((struct ether_addr *) eth_hdr->ether_shost, addr_buf));
    printf("  |-Destination Address     : %s\n", ethernet_ntoa((struct ether_addr *) eth_hdr->ether_dhost, addr_buf));
    printf("  |-Protocol:               : %s\n", ethernet_proto_ntop(ntohs(eth_hdr->ether_type), buf));
}
