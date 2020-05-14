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
#include "moba/printcancommand.h"
#include "moba/configparser.h"

int main(int argc, char *argv[]) {
    moba::common::setCoreFileSizeToULimit();

    PrintCanCommand printer{{CanCommand::CMD_PING, CanCommand::CMD_MFX_BIND}};

    CS2Writer cs2writer;
    CS2Reader cs2reader;

    cs2writer.connect("192.168.178.38");
    cs2reader.connect();

    //printCanCommand(getLokStat());
    //cs2writer.send(getLokStat());
    //cs2writer.send(getMagList());

    cs2writer.send(setSwitch(convertMMToLocId(6), true, true));
    usleep(50000);
    cs2writer.send(setSwitch(convertMMToLocId(6), true, false));
    sleep(2);
    cs2writer.send(setSwitch(convertMMToLocId(7), true, true));
    usleep(50000);
    cs2writer.send(setSwitch(convertMMToLocId(7), true, false));
    sleep(2);
    cs2writer.send(setSwitch(convertMMToLocId(34), true, true));
    usleep(50000);
    cs2writer.send(setSwitch(convertMMToLocId(34), true, false));
    sleep(2);
    cs2writer.send(setSwitch(convertMMToLocId(35), true, true));
    usleep(50000);
    cs2writer.send(setSwitch(convertMMToLocId(35), true, false));

    ConfigParser parser;

//    cs2writer.send(setLocFunction(16390, 0, true));
//    cs2writer.send(setLocFunction(16390, 2, true));
//    sleep(7);
//    cs2writer.send(setLocSpeed(16390, 500));


    while(true) {
        CS2CanCommand data = cs2reader.read();

        if(data.header[1] == static_cast<std::uint8_t>(CanCommand::CMD_SET_SWITCH | 0x01)) {
            printer.handleCanCommand(data);
        }


        parser.handleCanCommand(data);

        if(data.header[1] == static_cast<std::uint8_t>(CanCommand::CMD_S88_EVENT | 0x01)) {
            if(data.getWordAt2() == 8) {
                cs2writer.send(setLocSpeed(16390, 0));
                sleep(5);
                cs2writer.send(setLocFunction(16390, 0, false));
                cs2writer.send(setLocFunction(16390, 2, false));
            }



            //cs2.sendData(setLocSpeed(16402, 0));
            std::cout <<
                "addr " << data.getWordAt0() << " " <<
                "contact " << data.getWordAt2() << " " <<
                "active " << static_cast<bool>(data.data[4]) << " " <<
                "active " << static_cast<bool>(data.data[5]) << " " <<
                "time " << data.getWordAt6() << std::endl;

            continue;
        }
    }
}

