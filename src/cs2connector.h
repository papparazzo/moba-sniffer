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
            CMD_LOCO_DISCOVERY                          = 0x02,
            CMD_MFX_BIND                                = 0x04,
            CMD_MFX_VERIFY                              = 0x06,
            CMD_LOCO_SPEED                              = 0x08,
            CMD_LOCO_DIRECTION                          = 0x0A,
            CMD_LOCO_FUNCTION                           = 0x0C,
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
            CMD_CONFIG_DATA_QUERY                       = 0x40,
            CMD_CONFIG_DATA_STREAM                      = 0x42,
            CMD_60128_CONNECT_6021_DATA_STREAM          = 0x44,
        };

        enum SystemSubCommand {
            SYS_SUB_CMD_SYSTEM_STOP                        = 0x00,
            SYS_SUB_CMD_SYSTEM_GO                          = 0x01,
            SYS_SUB_CMD_SSYSTEM_HALT                       = 0x02,
            SYS_SUB_CMD_LOCO_EMERGENCY_STOP                = 0x03,
            SYS_SUB_CMD_LOCO_CYCLE_STOP                    = 0x04,
//            SYS_SUB_CMD_Lok Datenprotokoll                 = 0x05,
            SYS_SUB_CMD_CIRCUIT_TIME_ATTACHMENTS_DECODER   = 0x06,
            SYS_SUB_CMD_FAST_READ_MFX                      = 0x07,
//            SYS_SUB_CMD_Gleisprotokoll frei schalten       = 0x08,
//            SYS_SUB_CMD_System MFX Neuanmeldezähler setzen = 0x09,
            SYS_SUB_CMD_SYSTEM_OVERLAOD                    = 0x0A,
            SYS_SUB_CMD_SYSTEM_STATUS                      = 0x0B,
            SYS_SUB_CMD_SYSTEM_IDENTIFIER                  = 0x0C,
            SYS_SUB_CMD_MFX_SEEK                           = 0x30,
            SYS_SUB_CMD_SYSTEM_RESET                       = 0x80,
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

        std::string getCommmandAsString(int cmd);
        std::string getSystemSubCommand(int subCmd);

    protected:
        static const int PORT_READ   = 15730;
        static const int PORT_WRITE  = 15731;
        static const int BUFFER_SIZE = 512;
        int fd_read;
        int fd_write;
};




