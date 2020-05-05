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

#include <moba-common/helper.h>
#include <iostream>

#include <cstring>

#include "moba/cs2reader.h"
#include "moba/cs2writer.h"
#include "moba/cs2cancommand.h"
#include "moba/cs2utils.h"
#include "shared.h"

int main(int argc, char *argv[]) {
    moba::common::setCoreFileSizeToULimit();

    CS2Writer cs2writer;
    CS2Reader cs2reader;

    cs2writer.connect("192.168.178.38");
    cs2reader.connect();

    printCanCommand(getLokStat());
    cs2writer.send(getLokStat());

    while(true) {
        CS2CanCommand data = cs2reader.read();
        printCanCommand(data);

        if(data.header[1] == static_cast<uint8_t>(CanCommand::CMD_S88_EVENT | 0x01)) {
            //cs2.sendData(setLocSpeed(16402, 0));

            std::uint16_t time = (data.data[2] << 8) | data.data[3];

            std::uint16_t addr = (data.uid[0] << 8) | data.uid[1];
            std::uint16_t contact = (data.uid[2] << 8) | data.uid[3];

            bool active = static_cast<bool>(data.data[1]);

            std::cout << "addr " << addr << " contact " << contact << " active " << active << " time " << time << std::endl;

            continue;
        }
    }
}

