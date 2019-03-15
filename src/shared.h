/*
 *  Project:    moba-sniffer
 *
 *  Copyright (C) 2019 Stefan Paproth <pappi-@gmx.de>
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

#include <cstdint>
#include <string>

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
    SYS_SUB_CMD_SYSTEM_HALT                        = 0x02,
    SYS_SUB_CMD_LOCO_EMERGENCY_STOP                = 0x03,
    SYS_SUB_CMD_LOCO_CYCLE_STOP                    = 0x04,
//    SYS_SUB_CMD_Lok Datenprotokoll                 = 0x05,
    SYS_SUB_CMD_CIRCUIT_TIME_ATTACHMENTS_DECODER   = 0x06,
    SYS_SUB_CMD_FAST_READ_MFX                      = 0x07,
//    SYS_SUB_CMD_Gleisprotokoll frei schalten       = 0x08,
//    SYS_SUB_CMD_System MFX Neuanmeldezähler setzen = 0x09,
    SYS_SUB_CMD_SYSTEM_OVERLAOD                    = 0x0A,
    SYS_SUB_CMD_SYSTEM_STATUS                      = 0x0B,
    SYS_SUB_CMD_SYSTEM_IDENTIFIER                  = 0x0C,
    SYS_SUB_CMD_MFX_SEEK                           = 0x30,
    SYS_SUB_CMD_SYSTEM_RESET                       = 0x80,
};

struct CS2CanCommand {
    CS2CanCommand(
        CanCommand cmd = CanCommand::CMD_SYSTEM, std::uint8_t length = 0x00, std::uint32_t uident = 0x000000,
        std::uint8_t data0 = 0x00, std::uint8_t data1 = 0x00, std::uint8_t data2 = 0x00, std::uint8_t data3 = 0x00
    ) {
        header[0] = 0x00;
        header[1] = static_cast<std::uint8_t>(cmd);

        hash[0] = 0x03;
        hash[1] = 0x00;
        len = length;

        uid[0] = (uident >> 24) & 0xFF;;
        uid[1] = (uident >> 16) & 0xFF;;
        uid[2] = (uident >> 8) & 0xFF;;
        uid[3] = uident & 0xFF;

        data[0] = data0;
        data[1] = data1;
        data[2] = data2;
        data[3] = data3;
    }

    std::uint8_t header[2];
    std::uint8_t hash[2];
    std::uint8_t len;
    std::uint8_t uid[4];
    std::uint8_t data[4];
};

std::string getCommmandAsString(int cmd);
std::string getSystemSubCommand(int subCmd);

void printCanCommand(const CS2CanCommand &raw);

inline CS2CanCommand setLocSpeed(std::uint32_t locId, std::uint16_t speed) {
    std::uint8_t low  = speed & 0xFF;
    std::uint8_t high = (speed >> 8) & 0xFF;
    return std::move(CS2CanCommand(CanCommand::CMD_LOCO_SPEED, 6, locId, low, high));
}
