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
        enum CanCommand {
            CMD_SYSTEM                                  = 0x00,
            CMD_LOK_DISCOVERY                           = 0x02,
            CMD_MFX_BIND                                = 0x04,
            CMD_MFX_VERIFY                              = 0x06,
            CMD_LOK_SPEED                               = 0x08,
            CMD_LOK_DIRECTION                           = 0x0A,
            CMD_LOK_FUNCTION                            = 0x0C,
            CMD_READ_CONFIG                             = 0x0E,
            CMD_WRITE_CONFIG                            = 0x10,
            CMD_SET_SWITCH                              = 0x16,
            CMD_ATTACHMENTS_CONFIG                      = 0x18,
            CMD_S88_POLLING                             = 0x20,
            CMD_S88_EVENT                               = 0x22,
            CMD_SX1_EVENT                               = 0x24,
            CMD_PING                                    = 0x30,
            CMD_UPDATE_OFFER                            = 0x32,
            CMD_READ_CONFIG_DATA                        = 0x34,
            CMD_BOOTLOADER_CAN                          = 0x36,
            CMD_BOOTLOADER_TRACK                        = 0x38,
            CMD_STATUS_DATA_CONFIGURATION               = 0x3A,
            CMD_CONFIG_DATA_Query                       = 0x40,
            CMD_CONFIG_DATA_STREAM                      = 0x42,
            CMD_60128_CONNECT_6021_DATA_STREAM          = 0x44,
        };

        struct RawCanData {
            unsigned char header[2];
            unsigned char hash[2];
            unsigned char length;
            unsigned char uid[4];
            unsigned char data[4];
        };

        struct MsgData {
            char prio;       // 2 + 2 Bits
            CanCommand cmd;        // 1 Byte
            bool response;   // 1 Bit
            char hash[2];    // 2 Bytes
            char dlc;        // 4 Bit
            char data[8];
        };

        CS2Connector();
        virtual ~CS2Connector();

        void connect();
        MsgData recieveData();
        void sendData(const MsgData &data);

        std::string getCommmandAsString(CanCommand cmd);

    protected:
        static const int PORT        = 15730;
        static const int BUFFER_SIZE = 512;
        int socket;
};




