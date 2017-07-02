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


#include "cs2connector.h"

CS2Connector::CS2Connector() : socket(-1) {

}

CS2Connector::~CS2Connector() {
    ::close(socket);
}

void CS2Connector::connect() {
    struct sockaddr_in s_addr;

    if((socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        throw CS2ConnectorException("socket-creation failed");
    }

    memset((char *) &s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(::bind(socket, (struct sockaddr*)&s_addr, sizeof(s_addr)) == -1) {
        throw CS2ConnectorException("binding failed");
    }
}

void CS2Connector::sendData(const MsgData& data) {

}

CS2Connector::MsgData CS2Connector::recieveData() {
    struct sockaddr_in si_other;
    socklen_t slen = sizeof(si_other);

    RawCanData raw;
    int recv_len;
    memset((void*)&raw, '\0', sizeof(can));

    if((recv_len = ::recvfrom(socket, (void*)&raw, sizeof(raw), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
        throw CS2ConnectorException("recv from returned -1");
    }
    MsgData mi;



    std::cerr << (int)can.Header[1] << std::endl;


    std::cerr << std::uppercase;
    std::bitset<8> x(can.Header[0]);
    std::cerr << x << " ";

    std::bitset<8> y(can.Header[1]);
    std::cerr << y << " ";

    std::bitset<8> z(can.Hash[0]);
    std::cerr << z << " ";

    std::bitset<8> a(can.Hash[1]);
    std::cerr << a << " ";

    std::bitset<8> b(can.Length);
    std::cerr << b << " - ";

    std::bitset<8> t(can.Data[0]);
    std::cerr << t << " ";


    std::cerr << std::endl;

    std::cerr << std::setfill(' ') << std::setw(8) << std::hex << static_cast<unsigned int>(can.Header[0]) << " ";
    std::cerr << std::setfill(' ') << std::setw(8) << std::hex << static_cast<unsigned int>(can.Header[1]) << " ";

    std::cerr << std::setfill(' ') << std::setw(8) << std::hex << static_cast<unsigned int>(can.Hash[0]) << " ";
    std::cerr << std::setfill(' ') << std::setw(8) << std::hex << static_cast<unsigned int>(can.Hash[1]) << " ";

    std::cerr << std::setfill(' ') << std::setw(8) << std::hex << static_cast<unsigned int>(can.Length) << " - ";

    for(int j = 0; j < 4; ++j) {
        std::cerr << std::setfill(' ') << std::hex << static_cast<unsigned int>(can.UID[j]) << " ";
    }


    for(int j = 0; j < 4; ++j) {
        std::cerr << std::setfill(' ') << std::hex << static_cast<unsigned int>(can.Data[j]) << " ";
    }


    std::cerr << std::endl;
    std::cerr << "---------------------------------------------------------------";
    std::cerr << std::endl;





    int i = 0;

    MsgData m;
/*





    std::cerr << std::endl;

    for(int j = 0; j < recv_len; ++j) {
        std::cerr << std::setfill(' ') << std::setw(8) << std::hex << static_cast<unsigned int>(buf[j]) << " ";
    }
    std::cerr << std::nouppercase << std::dec << std::endl << std::endl;*/
    //std::cerr << "Received packet from " << inet_ntoa(si_other.sin_addr) << ":" << ntohs(si_other.sin_port) << std::endl;
    //std::cerr << "Data: " << buf << " len: " << recv_len << std::endl;
    //std::cerr << "---------------------"  << std::endl;
    return m;
}





/*
CS2Connector::MsgData CS2Connector::recieveData() {
    struct sockaddr_in si_other;
    socklen_t slen = sizeof(si_other);


    char buf[BUFFER_SIZE];
    int recv_len;
    int i = 0;

    MsgData m;


    //std::cerr << ++i << " Waiting for data..." << std::endl;
    memset(buf,'\0', BUFFER_SIZE);
    if((recv_len = ::recvfrom(socket, buf, BUFFER_SIZE, 0, (struct sockaddr *) &si_other, &slen)) == -1) {
        throw CS2ConnectorException("recvfrom returned -1");
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
    return m;
}

 * /






#define ANSWERBIT 0x01



#define Clear(a) {memset(&a, 0, sizeof(a));};
#define SetCmd(a, b) {a.Header[0] = (b >> 8 ); a.Header[1] = (b & 0x00FF);}
#define GetHash(a) ((a.Hash[0] << 8 ) + a.Hash[1])
#define Hash(a) {a.Hash[0] = 0x03; a.Hash[1] = 0x00;}


Clear(CanTx);
SetCmd(CanTx, CMD_SYSTEM);
Hash(CanTx);
CanTx.Length = 5;
CanTx.Data[0] = 0x00; // Sub Cmd Stop

error = SendBytes(CanTx);
 */