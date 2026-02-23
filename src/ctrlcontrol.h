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

#pragma once

#include <gtkmm.h>

#include "moba/cs2writer.h"

class  CtrlControl final: public Gtk::Box {
public:
    explicit CtrlControl(CS2WriterPtr cs2writer);

    ~CtrlControl() override = default;

    void handleCanCommand(const CS2CanCommand &cmd) const;

private:
    CS2WriterPtr cs2writer;

    Box              m_HButtonBox{Gtk::Orientation::HORIZONTAL, 6};
    Box              m_HBox_Expander{Gtk::Orientation::HORIZONTAL, 6};
    Gtk::Button      m_Button_Ping{"Ping"};
    Gtk::Button      m_Button_Pong{"Pong"};
    Gtk::CheckButton m_Button_AutoRespond;

    void on_button_ping_clicked() const;
    void on_button_pong_clicked() const;

    void on_button_start_clicked() const;
    void on_button_stop_clicked() const;
};

