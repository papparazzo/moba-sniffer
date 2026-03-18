/*
 *  Project:    moba-sniffer
 *
 *  Copyright (C) 2026 Stefan Paproth <pappi-@gmx.de>
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

#include "ctrlconfig.h"

#include "moba/configwriter.h"

CtrlConfig::CtrlConfig(CS2WriterPtr cs2writer):  Box{Gtk::Orientation::VERTICAL, 6}, configWriter{std::move(cs2writer)} {
    //Add the TreeView, inside a ScrolledWindow, with the button underneath:
    m_ScrolledWindow.set_child(m_TextView);

    //Only show the scrollbars when they are necessary:
    m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindow.set_expand();

    append(m_ScrolledWindow);

    m_refTextBuffer = Gtk::TextBuffer::create();
    m_refTextBuffer->set_text(R"([lokomotive]
version
.major=0
.minor=4
session
.id=24
lokomotive
.uid=0xc002
.name=Dcc-2
.vorname=Dcc-2
.adresse=0x3e8
.typ=dcc
.sid=0xcdcd
.mfxuid=0xffffffff
.icon=
.symbol=0
.av=30
.bv=30
.volume=2
.progmask=0x2
.velocity=0
.richtung=0
.tachomax=350
.vmax=255
.vmin=1
.xprot=3
.mfxtyp=205
.funktionen
..nr=0
..typ=1
..dauer=0
..wert=0
.inTraktion=0xffffffff)");

    m_TextView.set_buffer(m_refTextBuffer);
}

void CtrlConfig::handleCanCommand(const CS2CanCommand &cmd) const {
    if(cmd.header[1] != static_cast<uint8_t>(CanCommand::CMD_CONFIG_DATA_QUERY)) {
        return;
    }

    configWriter.handleData(m_refTextBuffer->get_text().raw());
}