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
#pragma once

#include <boost/noncopyable.hpp>
#include <string>
#include <exception>
#include <netinet/in.h>
#include <sys/socket.h>

#include <cstdint>

#include "shared.h"

class CS2ConnectorException : public std::exception {

    public:
        virtual ~CS2ConnectorException() throw() {
        }

        CS2ConnectorException(const std::string &what) {
            what__ = what;
        }

        virtual const char* what() const throw() {
            return what__.c_str();
        }

    private:
        std::string what__;
};

class CS2Connector : private boost::noncopyable {
    public:
        CS2Connector();
        virtual ~CS2Connector();

        void connect(const std::string &host);
        CS2CanCommand recieveData();
        void sendData(const CS2CanCommand &data);

        std::string getCommmandAsString(int cmd);
        std::string getSystemSubCommand(int subCmd);

    protected:
        static const int PORT_READ   = 15730;
        static const int PORT_WRITE  = 15731;
        static const int BUFFER_SIZE = 512;

        static const int MSG_HANDLER_TIME_OUT_USEC = 0;

        int fd_read;
        int fd_write;
        struct sockaddr_in s_addr_write;
};
