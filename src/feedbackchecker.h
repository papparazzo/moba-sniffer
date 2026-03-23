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

#include "moba/cs2cancommand.h"
#include "moba/cs2writer.h"

class FeedbackChecker final: public Gtk::Box {
public:
    explicit FeedbackChecker(CS2WriterPtr cs2writer);
    ~FeedbackChecker() override = default;

    void handleCanCommand(const CS2CanCommand &cmd);

private:
    static constexpr unsigned int MAX_CONTACTS = 35;
    CS2WriterPtr cs2writer;

    void on_button_circuit(std::uint16_t module, std::uint16_t idx);
    void on_button_contact(std::uint16_t module, std::uint16_t idx, bool state);

    Gtk::ScrolledWindow        m_ScrolledWindow;
    Box                        m_VBox_LabelBox{Gtk::Orientation::VERTICAL, 6};

    std::array<Gtk::Label, MAX_CONTACTS> m_Label_S88_Description;
    std::array<Gtk::Label, MAX_CONTACTS> m_Label_S88_Contact;
    std::array<Gtk::Label, MAX_CONTACTS> m_Label_S88_Circuit;

    std::array<Box, MAX_CONTACTS>        m_VBox_LabelRow;

    std::array<bool, MAX_CONTACTS>       m_ContactState{};

    std::vector<Glib::RefPtr<Gtk::GestureClick>> m_clicks;
};
