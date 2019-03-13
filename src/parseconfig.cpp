/*
 *  Project:    moba-sniffer
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

#include "parseconfig.h"
#include "shared.h"
#include "configdata.h"

ParseConfig::~ParseConfig() {
}

void ParseConfig::appendCanData(const CS2CanCommand &cmd) {
    if(cmd.len == 8) {
        configData.insert(cmd.uid, 4);
        configData.insert(cmd.data, 4);
        return;
    }

    if(cmd.len == 6) {
        std::uint32_t length = 0;

        for (size_t i = 0; i < 4; ++i) {
            length |= (cmd.uid[0] << i);
        }

    }

}