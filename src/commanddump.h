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

class CommandDump final: public Gtk::Box {
public:
    CommandDump();
    ~CommandDump() noexcept override = default;

    void clearList();
    void addCommand(const CS2CanCommand &cmd);

private:
    Gtk::Paned                   m_HPaned{Gtk::Orientation::HORIZONTAL};

    // Out-Box
    struct ModelColumnsActiveApps final : Gtk::TreeModel::ColumnRecord {
        ModelColumnsActiveApps() {
            add(m_col_id);
            add(m_col_name);
        }

        Gtk::TreeModelColumn<Glib::ustring>  m_col_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    };

    ModelColumnsActiveApps m_Columns_ActiveApps;

    Glib::RefPtr<Gtk::ListStore> m_refTreeModel_ActiveApps;

    Gtk::Box                     m_OutBox{Gtk::Orientation::VERTICAL, 6};

    Gtk::ScrolledWindow          m_ScrolledWindowOut;
    Gtk::TreeView                m_TreeView_ActiveApps;

    // In-Box
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

    Gtk::Box                     m_InBox{Gtk::Orientation::VERTICAL, 6};

    Gtk::ScrolledWindow          m_ScrolledWindowIn;
    Gtk::TreeView                m_TreeView_Commands;

    Gtk::Box                     m_HBox_Expander{Gtk::Orientation::HORIZONTAL, 6};

    Gtk::Box                     m_ButtonBox_CommandDump{Gtk::Orientation::HORIZONTAL, 6};
    Gtk::Button                  m_Button_ClearList{"Liste leeren"};

    Gtk::Box                     m_HBox_CheckRow{Gtk::Orientation::HORIZONTAL, 6};
    Gtk::CheckButton             m_Button_AutoCheckLast;

    void initIncoming();
    void initOutgoing();

    void appendCommand(CanCommand cmd) const;
    void sendCanCommand(CanCommand cmd);
};
