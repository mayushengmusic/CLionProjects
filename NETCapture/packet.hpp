//
// Created by jaken on 16-12-18.
//

#ifndef NETCAPTURE_PACKET_HPP
#define NETCAPTURE_PACKET_HPP
struct packet{
    char type[8];
    char srcip[32];
    char desip[32];
    char comment[2048];
    int size = 0;
    struct packet * next;
};

#endif //NETCAPTURE_PACKET_HPP
