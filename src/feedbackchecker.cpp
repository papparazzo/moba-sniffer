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
#include <utility>
#include <format>

#include "moba/cs2utils.h"

FeedbackChecker::FeedbackChecker(CS2WriterPtr cs2writer) : Box{Gtk::Orientation::VERTICAL, 6}, cs2writer{std::move(cs2writer)} {
    const auto css_provider = Gtk::CssProvider::create();
    css_provider->load_from_data("label:hover { background-color: rgba(128, 128, 128, 0.1); }");

    append(m_ScrolledWindow);
    m_ScrolledWindow.set_child(m_VBox_LabelBox);

    // Only show the scrollbars when they are necessary:
    m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindow.set_expand();

    int module = 1;

    for(int idx = 0; idx < MAX_CONTACTS; ++idx) {
        auto &labelrow = m_VBox_LabelRow[idx];
        labelrow.set_orientation(Gtk::Orientation::HORIZONTAL);
        labelrow.set_spacing(6);

        m_VBox_LabelBox.append(labelrow);

        auto &labelDesc = m_Label_S88_Description[idx];
        labelrow.append(labelDesc);

        labelDesc.set_markup(std::format("Block:  R {:02}/{:02}  S {:02}/{:02} ", module, idx * 2, module, idx * 2 + 1));

        auto &labelCircuit = m_Label_S88_Circuit[idx];
        labelCircuit.set_can_target(true);

        m_clicks.push_back(Gtk::GestureClick::create());

        m_clicks.back()->signal_pressed().connect([this, module, idx](const int, const double, const double) {
            this->on_button_circuit(module, idx);
        });

        labelCircuit.add_controller(m_clicks.back());
        labelCircuit.get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

        labelCircuit.set_markup("<span foreground=\"green\">XXXXXXXXX</span>");
        labelrow.append(labelCircuit);

        auto &labelContact = m_Label_S88_Contact[idx];
        labelContact.set_can_target(true);

        m_clicks.push_back(Gtk::GestureClick::create());

        m_clicks.back()->signal_pressed().connect([this, module, idx](const int, const double, const double) {
            this->on_button_contact(module, idx, true);
        });
        m_clicks.back()->signal_released().connect([this, module, idx](const int, const double, const double) {
            this->on_button_contact(module, idx, false);
        });

        labelContact.add_controller(m_clicks.back());
        labelContact.get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

        labelContact.set_markup("<span foreground=\"green\">[X]</span>");
        labelrow.append(labelContact);
    }
}

void FeedbackChecker::on_button_circuit(const std::uint16_t module, const std::uint16_t idx) {
    const bool state = !m_ContactState[idx];
    m_ContactState[idx] = state;
    
    if (state) {
        m_Label_S88_Circuit[idx].set_markup("<span foreground=\"red\">XXXXXXXXX</span>");
    } else {
        m_Label_S88_Circuit[idx].set_markup("<span foreground=\"green\">XXXXXXXXX</span>");
    }
    cs2writer->trySend(setFeedback(module, idx * 2, !state, state));
}

void FeedbackChecker::on_button_contact(const std::uint16_t module, const std::uint16_t idx, const bool state) {
    if (state) {
        m_Label_S88_Contact[idx].set_markup("<span foreground=\"red\">[X]</span>");
    } else {
        m_Label_S88_Contact[idx].set_markup("<span foreground=\"green\">[X]</span>");
    }
    cs2writer->trySend(setFeedback(module, idx * 2 + 1, !state, state));
}

void FeedbackChecker::handleCanCommand(const CS2CanCommand &cmd) {
    std::cout << cmd.getAsString() << std::endl;

    if(cmd.header[1] != static_cast<std::uint8_t>(CanCommand::CMD_S88_EVENT | 0x01)) {
        return;
    }

    std::string color;

    if(cmd.data[4]) {
        color = "green";
    } else {
        color = "red";
    }

    const int idx = cmd.getWordAt2() / 2;

    if(cmd.getWordAt2() % 2) {
        m_Label_S88_Contact[idx].set_markup(std::format("<span foreground=\"{}\">[X]</span>", color));
    } else {
        m_Label_S88_Circuit[idx].set_markup(std::format("<span foreground=\"{}\">XXXXXXXXX</span>", color));
    }
}
