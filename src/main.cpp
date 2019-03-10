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

#include "cs2connector.h"
#include <moba/helper.h>
#include <iostream>

#include <cstring>
#include "shared.h"

inline CS2CanCommand getLoklist() {
    // Komplette Lokliste -> "loks"
    CS2CanCommand cmd;
    unsigned char data[] = {0x00, 0x40, 0x03, 0x00, 0x08, 0x6C, 0x6F, 0x6B, 0x73, 0x00, 0x00, 0x00, 0x00};
    memcpy((void*)&cmd, data, 13);
    return std::move(cmd);
}

inline CS2CanCommand getLokStat() {
    // Aktueller Zustand der Loks -> "lokstat"
    CS2CanCommand cmd;
    unsigned char data[] = {0x00, 0x40, 0x03, 0x00, 0x08, 0x6C, 0x6F, 0x6B, 0x73, 0x74, 0x61, 0x74, 0x00};
    memcpy((void*)&cmd, data, 13);
    return std::move(cmd);
}

int main(int argc, char *argv[]) {
    moba::setCoreFileSizeToULimit();

    CS2Connector cs2;

    cs2.connect("192.168.178.38");

    printCanCommand(getLokStat());
    cs2.sendData(getLokStat());

    while(true) {
        CS2CanCommand data = cs2.recieveData();
        printCanCommand(data);

        if(data.header[1] == static_cast<uint8_t>(CanCommand::CMD_S88_EVENT | 0x01)) {
            cs2.sendData(setLocSpeed(16402, 0));

            std::uint16_t time = (data.data[2] << 8) | data.data[3];

            std::uint16_t addr = (data.uid[0] << 8) | data.uid[1];
            std::uint16_t contact = (data.uid[2] << 8) | data.uid[3];

            bool active = static_cast<bool>(data.data[1]);

            std::cout << "addr " << addr << " contact " << contact << " active " << active << " time " << time << std::endl;

            continue;
        }
    }
}


/**
 10.03.2019 01:01:10.601     helper.cpp:0074 Notice:  core file size set to unlimited.
00 40 - 03 00 - 08 - 6C 6F 6B 73 - 74 61 74 00
[ ] CMD_CONFIG_DATA_QUERY
---------------------------------------------------------------
00 41 - 07 0B - 08 - 6C 6F 6B 73 - 74 61 74 00
[R] CMD_CONFIG_DATA_QUERY
---------------------------------------------------------------
00 42 - 07 0B - 06 - 00 00 01 93 - 26 4F 74 00
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 00 00 18 71 - 78 9C ED 98
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - CF 4E 83 40 - 10 C6 EF 3C
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - C5 BE C0 36 - 33 B3 CB B2
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 1C B8 34 BD - 98 E8 C5 AB
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 31 A6 B1 A8 - A4 05 12 FE
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - D4 D7 77 1B - 63 E2 61 06
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 7B 28 55 90 - 13 C9 6F B2
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 64 BF EF 63 - 06 96 87 43
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - BD 6F BB 6D - D7 B7 8F D1
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 31 6F DA A2 - AE 22 B5 2A
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 8B AA 6E 32 - 1B 85 62 5D
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - D6 5D 71 CC - 03 AC B6 65
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 9E AD EF 95 - 22 24 85 10
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 6B 54 9B 75 - E0 2F 7D B5
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - EF C2 BA FC - B4 72 55 35
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 19 9C AE EF - 79 D3 65 C8
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 95 59 48 1C - 34 1C B4 1C
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 8C 39 E8 38 - 98 70 D0 73
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 30 65 37 0F - 2C E5 85 B2
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - A2 90 55 85 - AC 2C 8C 99
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 08 08 9D 02 - B0 FA 74 F7
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - A6 78 7E EB - FA EA 95 37
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 75 9A 41 0C - EC F8 AF 46
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 12 BA 02 10 - 15 78 A3 D9
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 5B 4D 33 88 - 29 D9 4F 0E
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 95 37 56 BB - B3 9A 62 86
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 09 0C 3D 5E - F8 43 7D BC
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 54 08 35 12 - 68 76 DB 4B
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 53 8C 6E 7F - 98 49 94 1A
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - ED 06 5E D4 - 8B EF 97 F7
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - DD 01 AA BB - 7C 57 D4 87
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - F2 BF 8E A3 - DF CD A0 BC
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - DD 98 B3 9C - 5F E6 CF 68
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 19 80 35 CA - 38 2B CF FE
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - AB 39 3E 10 - F2 6C BD 27
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 05 A9 D3 7E - 19 FC 57 34
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 9D 4C 38 97 - C5 9A 16 D3
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - AF 67 3A A1 - 57 14 83 86
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - F4 D3 F5 39 - 8E FC 09 1E
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 88 21 0E A7 - 61 34 1A 67
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 1A C9 64 82 - 08 5F A3 26
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - CC A5 C4 4F - E1 67 DD C0
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 3E A6 9F 44 - 42 16 80 34
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - AA 9B 6A D7 - B7 C5 25 1A
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 63 A0 BC B4 - 88 10 CC 77
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - FA 44 5F DC - 09 3C 11 B8
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 17 78 CA 73 - 02 81 A3 C0
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 49 E0 46 E0 - 56 E0 82 5E
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - 12 F4 92 A0 - 97 04 BD 24
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - E8 35 82 5E - 83 D1 07 4C
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------
00 42 - 07 0B - 08 - A6 68 C2 00 - 00 00 00 00
[ ] CMD_CONFIG_DATA_STREAM
---------------------------------------------------------------

RUN FINISHED; Terminated; real time: 3s; user: 0ms; system: 0ms


 */