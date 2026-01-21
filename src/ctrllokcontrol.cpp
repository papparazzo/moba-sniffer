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

#include "ctrllokcontrol.h"

namespace
{
struct PositionTypeStruct
{
  Gtk::PositionType position;
  Glib::ustring text;
};

const std::array positionTypes =
{
  PositionTypeStruct{Gtk::PositionType::TOP,    "Top"},
  PositionTypeStruct{Gtk::PositionType::BOTTOM, "Bottom"},
  PositionTypeStruct{Gtk::PositionType::LEFT,   "Left"},
  PositionTypeStruct{Gtk::PositionType::RIGHT,  "Right"}
};

}

CtrlLokControl::CtrlLokControl(CS2WriterPtr cs2writer):
    Box{Gtk::Orientation::VERTICAL, 6},
    cs2writer{std::move(cs2writer)},
    m_HBox_DropDown(Gtk::Orientation::HORIZONTAL, 10),
    m_adjustment( Gtk::Adjustment::create(0.0, 0.0, 1000.0, 1.0, 10.0, 10.0) ),
    m_Scrollbar(m_adjustment),
    m_Button_Switch_Direction("Fahrtrichtungswechsel")
{
    set_expand(true);

    append(m_HBox_DropDown);
    m_HBox_DropDown.append(*Gtk::make_managed<Gtk::Label>("Lok:", 0));
    m_HBox_DropDown.append(m_DropDown_Loco);
    m_HBox_DropDown.set_margin(10);

    //Create the StringList:
    auto string_list = Gtk::StringList::create({});
    m_DropDown_Loco.set_model(string_list);
    m_DropDown_Loco.set_selected(0);

    string_list->append("Eine Lok");

    append(m_Scrollbar);
    m_Scrollbar.set_margin(10);

    append(m_Button_Switch_Direction);
    m_Button_Switch_Direction.set_margin(10);

    append(m_ScrolledWindow);
    m_ScrolledWindow.set_child(m_ColumnView);

    // Only show the scrollbars when they are necessary:
    m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindow.set_expand();

    append(m_VBox_ExpanderIn);
    m_VBox_ExpanderIn.set_vexpand(true);
}


