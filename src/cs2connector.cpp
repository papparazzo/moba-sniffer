/*
 *  Project:    moba-sniffer
 *
 *  Copyright (C) 2016 Stefan Paproth <pappi-@gmx.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/agpl.txt>.
 *
 */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <iomanip>
#include <bitset>

#define BUFLEN 512
#define PORT 15730



#include "cs2connector.h"

CS2Connector::CS2Connector() {

}

/**
     struct sockaddr_in si_me, si_other;
    int s;
    socklen_t slen = sizeof(si_other);
    char buf[BUFLEN];

    if((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        std::cerr << "socket" << std::endl;
        return 1;
    }

    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    if(::bind(s, (struct sockaddr*)&si_me, sizeof(si_me)) == -1) {
        std::cerr << "bind" << std::endl;
        return 1;
    }

    int recv_len;
    int i = 0;
    while(1) {
        //std::cerr << ++i << " Waiting for data..." << std::endl;
        memset(buf,'\0', BUFLEN);
        if((recv_len = ::recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1) {
            return 1;
        }

        std::cerr << std::uppercase;

        for(int i = 0; i < recv_len; ++i) {
            std::bitset<8> x(buf[i]);
            std::cerr << x << " ";
        }
        std::cerr << std::endl;

        for(int j = 0; j < recv_len; ++j) {
            std::cerr << std::setfill(' ') << std::setw(8) << std::hex << static_cast<unsigned int>(buf[j]) << " ";
        }
        std::cerr << std::nouppercase << std::dec << std::endl << std::endl;
        //std::cerr << "Received packet from " << inet_ntoa(si_other.sin_addr) << ":" << ntohs(si_other.sin_port) << std::endl;
        //std::cerr << "Data: " << buf << " len: " << recv_len << std::endl;
        //std::cerr << "---------------------"  << std::endl;
    }
    close(s);
    return 0;

 */

/*
cs2connector::cs2connector(const cs2connector& orig) {
}

cs2connector::~cs2connector() {
}
*/


