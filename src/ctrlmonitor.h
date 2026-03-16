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

class CtrlMonitor final: public Gtk::Box {
public:

    CtrlMonitor();

    ~CtrlMonitor() override = default;

    void addMessage(const std::string &caption, const std::string& message);

private:
    struct MonitorEntry final: Gtk::TreeModel::ColumnRecord {
        MonitorEntry() {
            add(m_col_timestamp);
            add(m_col_caption);
            add(m_col_message);
        }

        Gtk::TreeModelColumn<std::string> m_col_timestamp;
        Gtk::TreeModelColumn<std::string> m_col_caption;
        Gtk::TreeModelColumn<std::string> m_col_message;
    };

    MonitorEntry m_ColumnsEntries;

    Glib::RefPtr<Gtk::ListStore> m_refTreeModel_Messages;

    Box                          m_HBox_ControlBoxIn{Gtk::Orientation::HORIZONTAL, 6};
    Box                          m_ButtonBox_CommandDump{Gtk::Orientation::HORIZONTAL, 6};

    Gtk::ScrolledWindow          m_ScrolledWindowIn;
    Gtk::TreeView                m_TreeView_Messages;

    Gtk::Button                  m_Button_ClearList{"Liste leeren"};

    void clearList();
};

