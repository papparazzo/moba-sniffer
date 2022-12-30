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
#include <getopt.h>

#include <string>

#include <config.h>
#include "handler.h"
#include <map>
#include <functional>
#include <memory>

namespace {
    moba::AppData appData = {
        PACKAGE_NAME,
        moba::Version{PACKAGE_VERSION},
        __DATE__,
        __TIME__,
        "",
        0
    };

    struct CmdLineArguments {
        std::uint32_t localId;
    };
}

void printHelp() {
    std::cout << std::endl;
    std::cout << "-i, --localid   locId" << std::endl;
    std::cout << "-h, --help      shows this help" << std::endl;
    std::cout << "-v, --version   shows version-info" << std::endl;
}

bool parseArguments(int argc, char** argv, CmdLineArguments &args) {
    static struct option longOptions[] = {
        {"localid",   required_argument, 0,    'i'},
        {"help",      no_argument,       0,    'h'},
        {"version",   no_argument,       0,    'v'},


        {"data",      required_argument, 0,    'd'},
        {"action",    required_argument, 0,    'a'},
        {NULL,        0,                 NULL,  0 }
    };

    int optionIndex = 0;

    while (true) {
        int c = getopt_long(argc, argv, "i:hv", longOptions, &optionIndex);
        if(c == -1) {
            break;
        }

        switch (c) {
            case 'i':
                args.localId = std::stoul(optarg);
                break;

            case 'h':
                printHelp();
                return true;

            case 'v':
                moba::printAppData(appData);
                return true;


                /*
            case 'k':
             *
                args.key = atoi(optarg);
                break;

            case 'd':
                args.data = std::string(optarg);
                break;
             */

        }
    }
    return false;
}

int main(int argc, char** argv) {
    Handler handler;

    handler.printConfigList("lokstatus");

    //handler.printLoklist();

    CmdLineArguments args = {
        0
    };

    try {
        if(parseArguments(argc, argv, args)) {
            return EXIT_SUCCESS;
        }

    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    // return EXIT_SUCCESS;


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

//    cs2writer.send(setLocFunction(16390, 0, true));
//    cs2writer.send(setLocFunction(16390, 2, true));
//    sleep(7);
//    cs2writer.send(setLocSpeed(16390, 500));

}

