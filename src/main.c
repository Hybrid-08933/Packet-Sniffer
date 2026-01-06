#include <stdint.h>             // stuff
#include <stdio.h>              // printf, perror, more
#include <stdlib.h>             // exit, malloc, free
#include <string.h>             // memset
#include <unistd.h>             // close
#include <errno.h>              // errno
#include <arpa/inet.h>          // htons, ntohs, inet_pton, inet_ntop

#include <sys/types.h>          // stuff
#include <sys/socket.h>         // socket, setsockopt, recvfrom
#include <net/ethernet.h>       // struct ether_addr, ETH_P_ALL
#include <netpacket/packet.h>   // struct sockaddr_ll
#include <netinet/in.h>         // IPPROTO_*

#include "packet.h"

#define RX_BUF_SIZE 9216

int main(void) {
    int raw_sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    uint8_t buf[RX_BUF_SIZE];
    int i = 0;

    if (raw_sock < 0) {
        perror("Socket Error");
    }

    {
        int val = 128 * 1024 * 1024;
        setsockopt(raw_sock, SOL_SOCKET, SO_RCVBUF, &val, sizeof(val));
    }

    while (i < 10) {
        memset(buf, 0, RX_BUF_SIZE);

        ssize_t data_len = recvfrom(raw_sock, buf, sizeof(buf), 0, NULL, NULL);
        if (data_len < 0) {
            perror("Recvfrom");
            break;
        }

        process_packet(buf, data_len);
        
        i++;
    }

    exit(EXIT_SUCCESS);
}
