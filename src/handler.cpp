/*
 *  Project:    moba-sniffer
 *
 *  Copyright (C) 2022 Stefan Paproth <pappi-@gmx.de>
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

#include "handler.h"

#include "moba/cs2cancommand.h"
#include "moba/cs2utils.h"
#include "moba/printcancommand.h"
#include "moba/configreader.h"
#include "moba/configloklistreader.h"
#include "moba/configdumpreader.h"
#include "s88sniffer.h"

#include <iostream>

Handler::Handler() {
    cs2writer.connect("192.168.178.38");
    cs2reader.connect();
}

Handler::~Handler() {
}

void Handler::printConfigList(const std::string &name) {

    //"lokstatus"

    auto dump = std::make_shared<ConfigDumpReader>(name);

    ConfigReader configReader{};
    configReader.addHandler(dump);

    cs2writer.send(getLokStat());
    cs2writer.send(getMagList());
    cs2writer.send(getLokList());

    while(true) {
        configReader.handleCanCommand(cs2reader.read());
    }
}

void Handler::printLoklist() {
    auto loklist = std::make_shared<ConfigLoklistReader>();

    ConfigReader configReader{};
    configReader.addHandler(loklist);

    cs2writer.send(getLokList());

    while(true) {
        configReader.handleCanCommand(cs2reader.read());

        if(loklist->locomotives.size()) {
            for(auto const &ent1 : loklist->locomotives) {
                std::cout << "uid: " << ent1.first << ", name: " << ent1.second->name << std::endl;

                //for(auto const &ent2 : ent1.second) {

               // }
            }
            return;
        }
    }
}

void Handler::printCanCommands() {
    PrintCanCommand printer{};

    while(true) {
        printer.handleCanCommand(cs2reader.read());
    }
}

void Handler::printFeedBackAction() {
    S88Sniffer sniffer{};

    while(true) {
        sniffer.handleCanCommand(cs2reader.read());
    }
}