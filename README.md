# Packet Parser using Raw Sockets (C)

## Overview

This project is a **network packet parser written in C** that captures packets using **raw sockets on Linux** and manually parses protocol headers to display human-readable information.

The program demonstrates low-level networking concepts by decoding packets across multiple layers of the network stack, similar in spirit to tools like `tcpdump` or `Wireshark`, but implemented from scratch for learning purposes.

---

## Features

* Captures live network traffic using **raw sockets**
* Parses and displays:

  * **Ethernet (Layer 2)**
  * **IPv4 (Layer 3)**
  * **TCP (Layer 4)**
  * **UDP (Layer 4)**
  * **DNS (Layer 7)**
* Correctly handles **variable-length headers** (IP & TCP options)
* Displays:

  * Source and destination MAC/IP addresses
  * Ports, sequence & acknowledgment numbers
  * TCP flags (ACK, PSH, SYN, etc.)
  * Header lengths, checksums, TTL, window size
  * Raw payload data (hex + ASCII view)
* Output format inspired by existing packet analyzers for readability

---

## Sample Output

```
***********************TCP Packet*************************

Ethernet Header
  |-Source Address          : B8:F7:75:7C:90:2A
  |-Destination Address     : 78:8C:B5:60:18:D7
  |-Protocol:               : IPv4

IP Header
  |-IP Version              : 4
  |-Header Length           : 5 DWORDS or 20 Bytes
  |-Type Of Service         : 0
  |-Total Length            : 95
  |-Identification          : 1187
  |-Control Flags:
   |-DF:                    : 0
   |-MF:                    : 0
  |-Fragment Offset         : 16384
  |-Time To Live            : 64
  |-Protocol                : 6
  |-Header Checksum         : 28850
  |-Source Address          : 192.168.0.190
  |-Destination Address     : 35.186.224.35

TCP Header
  |-Source Port             : 33678
  |-Destination Port        : 443
  |-Sequence Number         : 4094196284
  |-Acknowledgment Number   : 1102413739
  |-Header Length           : 8 DWORDS or 32 Bytes
  |-Control Bits:
   |-URG                    : 0
   |-ACK                    : 1
   |-PSH                    : 1
   |-RST                    : 0
   |-SYN                    : 0
   |-FIN                    : 0
  |-Window                  : 1480
  |-Checksum                : 50581
  |-Urgent Pointer          : 0

Data Payload
    17 03 03 00 26 F0 C1 66 7F B2 AE 79 72 BD 19 83           ....&..f...yr...
    CF 32 26 B5 F8 02 BB 74 53 75 00 7E C2 99 0D 19           .2&....tSu.~....
    5A AF 43 E6 EB E8 4B FE 71 E2 AD                          Z.C...K.q..

##########################################################
```

---

## Supported Protocols

| Layer | Protocols          |
| ----: | ------------------ |
|    L2 | Ethernet           |
|    L3 | IPv4               |
|    L4 | TCP, UDP           |
|    L7 | DNS (over UDP/TCP) |

---

## System Requirements

* Linux (raw sockets require kernel support)
* GCC / Clang compiler
* Root privileges (for raw socket access)

---

## Compilation & Usage

```bash
make
sudo ./build/sniffer
```

> **Note:** Root access is required to create raw sockets.

---

## Design Notes

* Header fields are parsed manually into C structures
* Packet offsets are calculated dynamically using header length fields
* DNS parsing includes question section decoding and basic record handling
* Output format is inspired by existing packet analyzers, while parsing logic is original

---

## Limitations

* IPv6 not currently supported
* Fragmented IP packets are detected but not reassembled
* Encrypted application payloads (e.g., HTTPS) are shown as raw data

---

## Learning Outcomes

Through this project, I gained hands-on experience with:

* Linux networking and raw sockets
* OSI/TCP-IP networking layers
* Binary data parsing and memory safety
* Real-world protocol structures

---

## Future Improvements

* IPv6 support
* TCP stream reassembly
* Additional application protocols (HTTP, TLS handshake parsing)
* Packet filtering and command-line options

---

## Disclaimer

This tool is intended **for educational purposes only** and should be used responsibly on networks you own or have permission to analyze.
