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
#include "feedbackchecker.h"

#include <iostream>

FeedbackChecker::FeedbackChecker() : Box{Gtk::Orientation::VERTICAL, 6} {
    auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data("label:hover { background-color: rgba(128, 128, 128, 0.1); }");

    append(m_ScrolledWindow);
    m_ScrolledWindow.set_child(m_VBox_LabelBox);

    // Only show the scrollbars when they are necessary:
    m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindow.set_expand();

    for(int idx = 0; idx < m_Label_S88.size(); ++idx) {
        auto & label = m_Label_S88[idx];
        label.set_can_target(true);

        auto click = Gtk::GestureClick::create();
        m_clicks.push_back(click);  // Speichere die Referenz BEVOR wir den Controller hinzufügen

        // Capture idx by value in lambda
        auto pressed_handler = [this, idx](int n_press, double x, double y) {
            this->on_button_pressed(idx, n_press, x, y);
        };

        auto released_handler = [this, idx](int n_press, double x, double y) {
            this->on_button_released(idx, n_press, x, y);
        };
        // Verbinde die Lambda-Handler
        m_clicks.back()->signal_pressed().connect(pressed_handler);
        m_clicks.back()->signal_released().connect(released_handler);

        // Füge den Controller dem Label hinzu
        label.add_controller(m_clicks.back());

        label.get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

        std::stringstream ss;
        ss << "Block:  R 2/1  S 1/2  <span font_weight=\"ultrabold\">"
           << "<span foreground=\"green\">XXXXXXXXX</span> "
           << "<span foreground=\"red\">[X]</span> "
           << "<span foreground=\"green\">XXXXXXXXX</span></span>";

        label.set_markup(ss.str());
        m_VBox_LabelBox.append(label);
    }
}


void FeedbackChecker::on_button_pressed(const int index, int n_press, double x, double y) {
    std::cout << "Label " << index << " wurde gedrückt! Position: x=" << x << ", y=" << y << std::endl;
}

void FeedbackChecker::on_button_released(const int index, int n_press, double x, double y) {
    std::cout << "Label " << index << " wurde losgelassen! Position: x=" << x << ", y=" << y << std::endl;
}




/*
FeedbackChecker::FeedbackChecker(): Box{Gtk::Orientation::VERTICAL, 6} {

   // m_Label_S88[0].signal_button_press_event().connect(sigc::mem_fun(*this, &FeedbackChecker::on_click));

    for(auto & i : m_Label_S88) {
        label.set_can_target(true);

        // Create a click gesture controller for the label
        auto click = Gtk::GestureClick::create();
        click->signal_pressed().connect(
            sigc::mem_fun(*this, &FeedbackChecker::on_label_clicked));
        label.add_controller(click);
        m_clicks.push_back(click);  // Store the controller



        std::stringstream ss;
        ss << "Block:  R 2/1  S 1/2  <span font_weight=\"ultrabold\"><span foreground=\"green\">XXXXXXXXX</span> <span foreground=\"red\">[X]</span> <span foreground=\"green\">XXXXXXXXX</span></span>";

        //i.set_markup("<span foreground=\"red\" size=\"x-large\">XXXXX</span> is <i>cool</i>!");
        i.set_markup(ss.str());
        append(i);
    }
}
*/

void FeedbackChecker::handleCanCommand(const CS2CanCommand &cmd) {
    //if(cmd.header[1] != static_cast<std::uint8_t>(CanCommand::CMD_S88_EVENT | 0x01)) {
        return;
   // }

    /*
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
*/
}
