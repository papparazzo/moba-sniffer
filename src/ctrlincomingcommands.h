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

class CtrlIncomingCommands final: public Gtk::Box {
public:
    CtrlIncomingCommands();

    ~CtrlIncomingCommands() override = default;

    void addCommand(const CS2CanCommand &cmd);

private:
    struct CommandEntry final: Gtk::TreeModel::ColumnRecord {
        CommandEntry() {
            add(m_col_response);
            add(m_col_command);
            add(m_col_subcommand);
            add(m_col_raw);
        }

        Gtk::TreeModelColumn<bool> m_col_response;
        Gtk::TreeModelColumn<std::string> m_col_command;
        Gtk::TreeModelColumn<std::string> m_col_subcommand;
        Gtk::TreeModelColumn<std::string> m_col_raw;
    };

    CommandEntry m_Columns_Commands;

    Glib::RefPtr<Gtk::ListStore> m_refTreeModel_Commands;

    Box                          m_HBox_ControlBoxIn{Gtk::Orientation::HORIZONTAL, 6};
    Box                          m_HBox_ExpanderIn{Gtk::Orientation::HORIZONTAL, 6};
    Box                          m_ButtonBox_CommandDump{Gtk::Orientation::HORIZONTAL, 6};

    Gtk::ScrolledWindow          m_ScrolledWindowIn;
    Gtk::TreeView                m_TreeView_Commands;

    Gtk::Button                  m_Button_ClearList{"Liste leeren"};
    Gtk::CheckButton             m_Button_AutoCheckLast;

    void clearList();
};

