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

void Handler::printConfigList(ConfigListType type) {
    std::string name;
    switch(type) {
        case LOKLIST:
            name = "lokomotive";
            cs2writer.send(getLokList());
            break;

        case LOKSTATUS:
            name = "lokstatus";
            cs2writer.send(getLokStat());
            break;

        case MAGLIST:
            name = "magnetartikel";
            cs2writer.send(getMagList());
            break;

        case MAGSTATUS:
            name = "magnetartikel";
            cs2writer.send(getMagStat());
            break;
    }

    auto dump = std::make_shared<ConfigDumpReader>(name);

    ConfigReader configReader{};
    configReader.addHandler(dump);

    while(configReader.handleCanCommand(cs2reader.read()) != ConfigReader::HANDLED_AND_FINISHED)
        ;
}

void Handler::printLoklist() {
    auto loklist = std::make_shared<ConfigLoklistReader>();

    ConfigReader configReader{};
    configReader.addHandler(loklist);

    cs2writer.send(getLokList());

    while(true) {
        configReader.handleCanCommand(cs2reader.read());

        if(loklist->locomotives.empty()) {
            continue;
        }
        for(auto const &ent1 : loklist->locomotives) {
            std::cout << "uid: " << ent1.first << ", name: " << ent1.second->name << std::endl;

            //for(auto const &ent2 : ent1.second) {

           // }
        }
        return;
    }
}

[[noreturn]]
void Handler::printCanCommands(const std::set<CanCommand> &allowedCommands) {

    PrintCanCommand printer{allowedCommands};

    while(true) {
        printer.handleCanCommand(cs2reader.read());
    }
}

[[noreturn]]
void Handler::printFeedBackAction() {
    S88Sniffer sniffer{};

    while(true) {
        sniffer.handleCanCommand(cs2reader.read());
    }
}

void Handler::setFunction(std::uint32_t localId, std::uint8_t function, bool on) {
    std::cout << "localid " << localId << " function " << function << " on " << on << std::endl;
    cs2writer.send(setLocFunction(localId, function, on));
}

void Handler::setSpeed(std::uint32_t localId, std::uint16_t speed) {
    cs2writer.send(setLocSpeed(localId, speed));
}

void Handler::setSwitch(std::uint8_t addr, bool r) {
    cs2writer.send(::setSwitch(convertMMToLocId(addr), r, true));
    usleep(50000);
    cs2writer.send(::setSwitch(convertMMToLocId(addr), r, false));
}