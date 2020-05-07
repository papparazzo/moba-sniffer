/*
 *  Project:    moba-lib-cs2interace
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

#include "shared.h"
#include "moba/cs2utils.h"

#include <string>
#include <iostream>

void printCanCommand(const CS2CanCommand &raw) {
    printf(
        "%02X %02X - %02X %02X - %02X - %02X %02X %02X %02X - %02X %02X %02X %02X\n",
        static_cast<unsigned int>(raw.header[0]),
        static_cast<unsigned int>(raw.header[1]),
        static_cast<unsigned int>(raw.hash[0]),
        static_cast<unsigned int>(raw.hash[1]),
        static_cast<unsigned int>(raw.len),
        static_cast<unsigned int>(raw.data[0]),
        static_cast<unsigned int>(raw.data[1]),
        static_cast<unsigned int>(raw.data[2]),
        static_cast<unsigned int>(raw.data[3]),
        static_cast<unsigned int>(raw.data[4]),
        static_cast<unsigned int>(raw.data[5]),
        static_cast<unsigned int>(raw.data[6]),
        static_cast<unsigned int>(raw.data[7])
    );

    bool response = false;

    if(raw.header[1] & 0x01) {
        response = true;
    }

    uint8_t head = raw.header[1] & ~0x01;

    std::cerr << (response ? "[R] " : "[ ] ") << getCommmandAsString(head);

    if(head == CMD_SYSTEM) {
        std::cerr << " - " << getSystemSubCommandAsString(raw.data[0]);
    }

    std::cerr << std::endl;
    std::cerr << "---------------------------------------------------------------";
    std::cerr << std::endl;
}
