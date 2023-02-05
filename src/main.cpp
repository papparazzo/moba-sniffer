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
#include <map>
#include <functional>
#include <memory>
#include <libgen.h>

#include "handler.h"

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
        std::uint32_t function;
        std::uint16_t speed;
    };
}

void printHelp(const std::string &applName) {
    std::cout << applName << " [s88|dump|loklist|lokstatus|lokomotive|function_on|function_off|speed]" << std::endl;
    std::cout << std::endl;
    std::cout << "-i, --localid   locId" << std::endl;
    std::cout << "-s, --speed     speed" << std::endl;
    std::cout << "-f, --function  function" << std::endl;
    std::cout << "-h, --help      shows this help" << std::endl;
    std::cout << "-v, --version   shows version-info" << std::endl;
}

bool parseArguments(int argc, char** argv, CmdLineArguments &args) {
    if(argc < 2) {
        printHelp(basename(argv[0]));
        return true;
    }

    static struct option longOptions[] = {
        {"localid",   required_argument, 0,    'i'},
        {"speed",     required_argument, 0,    's'},
        {"function",  required_argument, 0,    'f'},
        {"help",      no_argument,       0,    'h'},
        {"version",   no_argument,       0,    'v'},
        {NULL,        0,                 NULL,  0 }
    };

    int optionIndex = 0;

    while (true) {
        int c = getopt_long(argc, argv, "s:f:i:hv", longOptions, &optionIndex);
        if(c == -1) {
            break;
        }

        switch(c) {
            case 'i':
                args.localId = std::stoul(optarg);
                break;

            case 'h':
                printHelp(basename(argv[0]) );
                return true;

            case 'v':
                moba::printAppData(appData);
                return true;

            case 'f':
                args.function = std::stoul(optarg);
                break;

            case 's':
                args.speed = std::stoul(optarg);
                break;
        }
    }
    return false;
}

int main(int argc, char** argv) {
    CmdLineArguments args = {
        0
    };

    if(parseArguments(argc, argv, args)) {
        return EXIT_SUCCESS;
    }

    std::string action{argv[1]};

    Handler handler;

    try {
        if(action == "s88") {
            handler.printFeedBackAction();
        } else if(action == "dump") {
            handler.printCanCommands();
        } else if(action == "loklist") {
            handler.printLoklist();
        } else if(action == "lokstatus") {
            handler.printConfigList("lokstatus");
        } else if(action == "lokomotive") {
            handler.printConfigList("lokomotive");
        } else if(action == "function_on") {
            handler.setFunction(args.localId, args.function, true);
        } else if(action == "function_off") {
            handler.setFunction(args.localId, args.function, false);
        } else if(action == "speed") {
            handler.setSpeed(args.localId, args.speed);
        } else {
            std::cout << "unknown command <" << action << "> given!" << std::endl;
        }
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

