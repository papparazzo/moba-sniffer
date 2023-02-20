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

#include "s88sniffer.h"
#include <ncurses.h>

S88Sniffer::S88Sniffer() {
    initscr();
    noecho();

    if(!has_colors()) {
        return;
    }

    start_color();
    init_pair(1, COLOR_RED,     COLOR_BLACK);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
}

S88Sniffer::~S88Sniffer() {
    endwin();
}


S88Sniffer::HandlerReturn S88Sniffer::handleCanCommand(const CS2CanCommand &cmd) {
    if(cmd.header[1] != static_cast<std::uint8_t>(CanCommand::CMD_S88_EVENT | 0x01)) {
        return S88Sniffer::NOT_HANDLED;
    }

    attrset(COLOR_PAIR(0));

    if(cmd.getWordAt2() % 2) {
        mvprintw(getRow(cmd.getWordAt2()), 0, "                        ]");
        mvprintw(getRow(cmd.getWordAt2()), 0, "Block:  R %d/%d [%d", cmd.getWordAt0(), cmd.getWordAt2(), cmd.getWordAt6());
    } else {
        mvprintw(getRow(cmd.getWordAt2()), 26, "                 ]");
        mvprintw(getRow(cmd.getWordAt2()), 26, " S %d/%d [%d", cmd.getWordAt0(), cmd.getWordAt2(), cmd.getWordAt6());
    }

    if(cmd.data[4]) {
        attrset(COLOR_PAIR(2)); // green
    } else {
        attrset(COLOR_PAIR(1)); // red
    }

    if(cmd.getWordAt2() % 2) {
        mvprintw(getRow(cmd.getWordAt2()), 45, "XXXXXXXXX");
        mvprintw(getRow(cmd.getWordAt2()), 59, "XXXXXXXXX");
    } else {
        mvprintw(getRow(cmd.getWordAt2()), 55, "[X]");
    }


    for(int i = 1; i < 35; ++i) {
        mvprintw(i, 85, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    }

    refresh();
    return S88Sniffer::HANDLED_AND_FINISHED;
}

int S88Sniffer::getRow(std::uint16_t contact) {
    if(contact > 1000) {
        contact -= 1000;
        contact += 16;
    }

    if(contact % 2) {
        contact++;
    }
    return contact / 2;
}
