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
#include <moba-common/log.h>
#include <iostream>

#include <cstring>
#include <string>

#include "moba/cs2reader.h"
#include "moba/cs2writer.h"
#include "moba/cs2cancommand.h"
#include "moba/cs2utils.h"
#include "moba/printcancommand.h"
#include "moba/configreader.h"
#include "moba/configloklistreader.h"
#include "s88sniffer.h"

#include <map>
#include <functional>
#include <memory>

int main(int argc, char *argv[]) {

    CS2Writer cs2writer;
    CS2Reader cs2reader;

    cs2writer.connect("192.168.178.38");
    cs2reader.connect();

    //PrintCanCommand printer{};

    //auto loklist = std::make_shared<ConfigLoklistReader>();

    //ConfigReader configReader{};
    //configReader.addHandler(loklist);

    S88Sniffer sniffer;

//    cs2writer.send(getLokStat());
    //cs2writer.send(getLokList());
    //cs2writer.send(getMagList());
/*
    cs2writer.send(setSwitch(convertMMToLocId(6), true, true));
    usleep(50000);
    cs2writer.send(setSwitch(convertMMToLocId(6), true, false));
    sleep(2);
    cs2writer.send(setSwitch(convertMMToLocId(6), false, true));
    usleep(50000);
    cs2writer.send(setSwitch(convertMMToLocId(6), false, false));
    sleep(2);
    cs2writer.send(setSwitch(convertMMToLocId(6), true, true));
    usleep(50000);
    cs2writer.send(setSwitch(convertMMToLocId(6), true, false));
    sleep(2);
    cs2writer.send(setSwitch(convertMMToLocId(6), false, true));
    usleep(50000);
    cs2writer.send(setSwitch(convertMMToLocId(6), false, false));

 */


//    cs2writer.send(setSwitch(convertMMToLocId(7), true, true));
//    usleep(50000);
//    cs2writer.send(setSwitch(convertMMToLocId(7), true, false));
//    sleep(2);
//    cs2writer.send(setSwitch(convertMMToLocId(34), true, true));
//    usleep(50000);
//    cs2writer.send(setSwitch(convertMMToLocId(34), true, false));
//    sleep(2);
//    cs2writer.send(setSwitch(convertMMToLocId(35), true, true));
//    usleep(50000);
//    cs2writer.send(setSwitch(convertMMToLocId(35), true, false));

//    ConfigParser parser;

    cs2writer.send(setLocFunction(16390, 0, true));
//    cs2writer.send(setLocFunction(16390, 2, true));
//    sleep(7);
//    cs2writer.send(setLocSpeed(16390, 500));

    while(true) {
        CS2CanCommand data = cs2reader.read();

        sniffer.handleCanCommand(data);

        //configReader.handleCanCommand(data);

        /*
        if(loklist->locomotives.size()) {
            for(auto const &ent1 : loklist->locomotives) {
                std::cout << "name: " << ent1.second->name << std::endl;

                //for(auto const &ent2 : ent1.second) {

               // }
            }
        }

         */
       // printer.handleCanCommand(data);
    }
}

