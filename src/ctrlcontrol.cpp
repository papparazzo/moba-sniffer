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

#include "ctrlcontrol.h"

#include "moba/cs2utils.h"

CtrlControl::CtrlControl(CS2WriterPtr cs2writer):  Box{Gtk::Orientation::VERTICAL, 6}, cs2writer {std::move(cs2writer)} {
    append(m_HButtonBox);
    m_HButtonBox.append(m_Button_Ping);
    m_HButtonBox.append(m_Button_Pong);
    m_HButtonBox.set_margin(10);

    m_Button_AutoRespond.set_label("autom. antworten");
    m_Button_AutoRespond.set_active(true);
    m_Button_AutoRespond.set_margin(10);

    append(m_Button_AutoRespond);
    m_HBox_Expander.set_hexpand(true);
    append(m_HBox_Expander);
    
    m_Button_Ping.signal_clicked().connect(sigc::mem_fun(*this, &CtrlControl::on_button_ping_clicked));
    m_Button_Pong.signal_clicked().connect(sigc::mem_fun(*this, &CtrlControl::on_button_pong_clicked));
}

void CtrlControl::on_button_ping_clicked() const {
    cs2writer->trySend(ping());
}

void CtrlControl::on_button_pong_clicked() const {
    cs2writer->trySend(pong());
}

void CtrlControl::handleCanCommand(const CS2CanCommand &cmd) const {
    if(cmd.header[1] != static_cast<uint8_t>(CanCommand::CMD_PING) || !m_Button_AutoRespond.get_active()) {
        return;
    }
    cs2writer->trySend(pong());
}
