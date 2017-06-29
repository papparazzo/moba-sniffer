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

#define GetCmd(a) (((a.Header[0] << 8 ) + a.Header[1]) & 0x01FF)
#define CMD_SYSTEM 0x0000
#define CMD_LOKDISCOVERY 0x0002
#define CMD_CDBGLEISREP 0x0202
#define CMD_MFX_BIND 0x0004
#define CMD_MFX_VERIFY 0x0006
#define CMD_LOK_SPEED 0x0008
#define CMD_LOK_DIR 0x000A
#define CMD_LOK_FUNCTION 0x000C
#define CMD_READ_CONFIG 0x000E
#define CMD_WRITE_CONFIG 0x0010
#define CMD_SET_SWITCH 0x0016
#define CMD_S88_POLLING 0x0020



CS2Connector::MsgData CS2Connector::recieveData() {
    struct sockaddr_in si_other;
    socklen_t slen = sizeof(si_other);


    typedef struct {
        unsigned char Header[2];
        unsigned char Hash[2];
        unsigned char Length;
        unsigned char UID[4];
        unsigned char Data[4];
    } TCan;

    TCan can;
    int recv_len;

    memset((void*)&can, '\0', sizeof(can));

    if((recv_len = ::recvfrom(socket, (void*)&can, sizeof(can), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
        throw CS2ConnectorException("recv from returned -1");
    }

    std::cerr << GetCmd(can) << std::endl;

    switch(GetCmd(can)) {

case CMD_SYSTEM       : std::cerr << "CMD_SYSTEM      " << std::endl;break;
case CMD_LOKDISCOVERY : std::cerr << "CMD_LOKDISCOVERY" << std::endl;break;
case CMD_CDBGLEISREP  : std::cerr << "CMD_CDBGLEISREP " << std::endl;break;
case CMD_MFX_BIND     : std::cerr << "CMD_MFX_BIND    " << std::endl;break;
case CMD_MFX_VERIFY   : std::cerr << "CMD_MFX_VERIFY  " << std::endl;break;
case CMD_LOK_SPEED    : std::cerr << "CMD_LOK_SPEED   " << std::endl;break;
case CMD_LOK_DIR      : std::cerr << "CMD_LOK_DIR     " << std::endl;break;
case CMD_LOK_FUNCTION : std::cerr << "CMD_LOK_FUNCTION" << std::endl;break;
case CMD_READ_CONFIG  : std::cerr << "CMD_READ_CONFIG " << std::endl;break;
case CMD_WRITE_CONFIG : std::cerr << "CMD_WRITE_CONFIG" << std::endl;break;
case CMD_SET_SWITCH   : std::cerr << "CMD_SET_SWITCH  " << std::endl;break;
case CMD_S88_POLLING  : std::cerr << "CMD_S88_POLLING " << std::endl;break;
}





    int i = 0;

    MsgData m;
/*



    std::cerr << std::uppercase;

    for(int i = 0; i < recv_len; ++i) {
        std::bitset<8> x(buf[i]);
        std::cerr << x << " ";
    }
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

#define CMD_SYSTEM 0x0000
#define CMD_LOKDISCOVERY 0x0002
#define CMD_CDBGLEISREP 0x0202
#define CMD_MFX_BIND 0x0004
#define CMD_MFX_VERIFY 0x0006
#define CMD_LOK_SPEED 0x0008
#define CMD_LOK_DIR 0x000A
#define CMD_LOK_FUNCTION 0x000C
#define CMD_READ_CONFIG 0x000E
#define CMD_WRITE_CONFIG 0x0010
#define CMD_SET_SWITCH 0x0016
#define CMD_S88_POLLING 0x0020


#define Clear(a) {memset(&a, 0, sizeof(a));};
#define SetCmd(a, b) {a.Header[0] = (b >> 8 ); a.Header[1] = (b & 0x00FF);}
#define GetCmd(a) (((a.Header[0] << 8 ) + a.Header[1]) & 0x01FF)
#define GetHash(a) ((a.Hash[0] << 8 ) + a.Hash[1])
#define Hash(a) {a.Hash[0] = 0x03; a.Hash[1] = 0x00;}


Clear(CanTx);
SetCmd(CanTx, CMD_SYSTEM);
Hash(CanTx);
CanTx.Length = 5;
CanTx.Data[0] = 0x00; // Sub Cmd Stop

error = SendBytes(CanTx);
 */