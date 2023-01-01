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

#pragma once

#include "moba/cs2reader.h"
#include "moba/cs2writer.h"

class Handler {
public:
    Handler();
    virtual ~Handler();

    void printLoklist();
    void printCanCommands();
    void printFeedBackAction();
    void printConfigList(const std::string &name);

    void setFunction(std::uint32_t localId, std::uint8_t function, bool on);
    void setSpeed(std::uint32_t localId, std::uint16_t speed);

private:
    CS2Writer cs2writer;
    CS2Reader cs2reader;
};

