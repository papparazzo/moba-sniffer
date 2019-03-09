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

#include "cs2connector.h"
#include <moba/helper.h>
#include <iostream>

#include <cstring>
#include "shared.h"

int main(int argc, char *argv[]) {
    moba::setCoreFileSizeToULimit();

    CS2Connector cs2;

    cs2.connect("192.168.178.38");


    CS2CanCommand raw{CanCommand::CMD_LOCO_SPEED, 6, 16402};

    printCanCommand(raw);
    cs2.sendData(raw);

    while(1) {
        CS2CanCommand raw = cs2.recieveData();
        printCanCommand(raw);
    }
}
