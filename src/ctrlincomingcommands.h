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

    void handleCanCommand(const CS2CanCommand &cmd);

private:
    class CommandsColumns final: public Glib::Object {
    public:
        unsigned int m_col_id;
        Glib::ustring m_col_commandName;
        bool m_col_active;

        static Glib::RefPtr<CommandsColumns> create(
            const unsigned int col_id,
            const Glib::ustring& m_col_commandName,
            const bool col_active
        ) {
            return Glib::make_refptr_for_instance<CommandsColumns>(new CommandsColumns(col_id, m_col_commandName, col_active));
        }

    protected:
        CommandsColumns(const unsigned int col_id, Glib::ustring  m_col_commandName, const bool col_active)
        : m_col_id(col_id), m_col_commandName(std::move(m_col_commandName)), m_col_active(col_active)
        {}
    }; // CommandsColumns

    Glib::RefPtr<Gio::ListStore<CommandsColumns>> m_ListStore;

    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::ColumnView m_ColumnView;

   // Box m_HBox_DropDown;

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

    Gtk::CheckButton             m_Button_ShowPing;

    void clearList();
    bool acceptCommand(const CS2CanCommand &cmd) const;
};

