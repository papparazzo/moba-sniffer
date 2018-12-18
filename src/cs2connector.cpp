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
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include "cs2connector.h"

CS2Connector::CS2Connector() : fd_read(-1), fd_write(-1) {
}

CS2Connector::~CS2Connector() {
    if(fd_read != -1) {
        ::close(fd_read);
    }
    if(fd_write != -1) {
        ::close(fd_write);
    }
}

void CS2Connector::connect(const std::string &host) {
    struct sockaddr_in s_addr_read;

    if((fd_read = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        throw CS2ConnectorException("socket-creation for reading failed");
    }

    ::memset((char *) &s_addr_read, 0, sizeof(s_addr_read));
    s_addr_read.sin_family = AF_INET;
    s_addr_read.sin_port = htons(PORT_READ);
    s_addr_read.sin_addr.s_addr = htonl(INADDR_ANY);

    if(::bind(fd_read, (struct sockaddr*)&s_addr_read, sizeof(s_addr_read)) == -1) {
        throw CS2ConnectorException("binding failed");
    }

    if((fd_write = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        throw CS2ConnectorException("socket-creation for writing failed");
    }

    ::memset((char *) &s_addr_write, 0, sizeof(s_addr_write));
    s_addr_write.sin_family = AF_INET;
    s_addr_write.sin_port = htons(PORT_WRITE);

    if(::inet_aton(host.c_str() , &s_addr_write.sin_addr) == 0) {
        throw CS2ConnectorException("inet_aton failed");
    }
}

void CS2Connector::sendData(const RawData &data) {
    if(::sendto(fd_write, (void*)&data, sizeof(data), 0, (struct sockaddr *)&s_addr_write, sizeof(s_addr_write)) == -1) {
        throw CS2ConnectorException("sending failed");
    }
}

CS2Connector::RawData CS2Connector::recieveData() {
    struct sockaddr_in s_addr_other;
    socklen_t slen = sizeof(s_addr_other);

    RawData raw;
    int recv_len;
    memset((void*)&raw, '\0', sizeof(raw));

    if((recv_len = ::recvfrom(fd_read, (void*)&raw, sizeof(raw), 0, (struct sockaddr *) &s_addr_other, &slen)) == -1) {
        throw CS2ConnectorException("::recvfrom returned -1");
    }

    return raw;
}