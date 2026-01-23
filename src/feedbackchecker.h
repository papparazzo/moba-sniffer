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

class FeedbackChecker : public Gtk::Box {
public:
    explicit FeedbackChecker(CS2WriterPtr cs2writer);
    ~FeedbackChecker() override = default;

private:
    CS2WriterPtr cs2writer;

    void handleCanCommand(const CS2CanCommand &cmd);

    void on_button_pressed(int index, int n_press, double x, double y);
    void on_button_released(int index, int n_press, double x, double y);

    Gtk::ScrolledWindow        m_ScrolledWindow;
    Box                        m_VBox_LabelBox{Gtk::Orientation::VERTICAL, 6};

    std::array<Gtk::Label, 35> m_Label_S88;
    std::vector<Glib::RefPtr<Gtk::GestureClick>> m_clicks;
};
