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
#include <memory>
#include <libgen.h>

#include <gtkmm/application.h>

#include "moba/cs2reader.h"
#include "moba/cs2writer.h"

#include "frmmain.h"

namespace {
    moba::AppData appData = {
        PACKAGE_NAME,
        moba::Version{PACKAGE_VERSION},
        __DATE__,
        __TIME__,
        "",
        0
    };
}

struct CS2ContactData {
    std::string host;
    int portIn;
    int portOut;
};

void printHelp(const std::string &appName, CS2ContactData &cs2ContactData) {
    std::cout << appName << std::endl;
    std::cout << std::endl;
    std::cout << "-h, --help          shows this help" << std::endl;
    std::cout << "-v, --version       shows version-info" << std::endl;
    std::cout << "-c, --cs2-host      host of the CentralStation (default: " << cs2ContactData.host << ")" << std::endl;
    std::cout << "-i, --cs2-port-in   port of the CentralStation for incoming messages (default: " << cs2ContactData.portIn << ")" << std::endl;
    std::cout << "-o, --cs2-port-out  port of the CentralStation for outgoing messages (default: " << cs2ContactData.portOut << ")" << std::endl;
}

bool parseArguments(const int argc, char *argv[], const moba::AppData &appData, CS2ContactData &cs2ContactData) {
    static option longOptions[] = {
        {"cs2-host",     required_argument, nullptr, 'c'},
        {"cs2-port-in",  required_argument, nullptr, 'i'},
        {"cs2-port-out", required_argument, nullptr, 'o'},
        {"help",         no_argument,       nullptr, 'h'},
        {"version",      no_argument,       nullptr, 'v'},
        {nullptr,        0,                 nullptr, 0 }
    };

    int optionIndex = 0;

    while(true) {
        const int c = getopt_long(argc, argv, "hv", longOptions, &optionIndex);
        if(c == -1) {
            break;
        }

        switch(c) {
            case 'h':
                printHelp(basename(argv[0]), cs2ContactData);
                return true;

            case 'v':
                moba::printAppData(appData);
                return true;

            case 'c':
                cs2ContactData.host = optarg;
                break;

            case 'i':
                cs2ContactData.portIn = std::stoi(optarg);
                break;

            case 'o':
                cs2ContactData.portOut = std::stoi(optarg);
                break;

            default:
                std::cerr << "Try '" << basename(argv[0]) << " --help' for more information." << std::endl;
                exit(2);
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    CS2ContactData cs2ContactData = {
        "127.0.0.1",
        CS2Reader::DEFAULT_PORT,
        CS2Writer::DEFAULT_PORT
    };

    if(parseArguments(argc, argv, appData, cs2ContactData)) {
        return EXIT_SUCCESS;
    }

    const auto cs2WriterPtr = std::make_shared<CS2Writer>(cs2ContactData.host, cs2ContactData.portIn);
    const auto cs2ReaderPtr = std::make_shared<CS2Reader>(cs2ContactData.host, cs2ContactData.portOut, false);

    auto app = Gtk::Application::create("org.moba.sniffer");
    return app->make_window_and_run<FrmMain>(--argc, argv, cs2WriterPtr, cs2ReaderPtr);
}