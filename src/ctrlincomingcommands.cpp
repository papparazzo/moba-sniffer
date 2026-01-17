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

#include "ctrlincomingcommands.h"

#include "moba/cs2utils.h"

CtrlIncomingCommands::CtrlIncomingCommands(): Box{Gtk::Orientation::VERTICAL, 6} {

    append(m_ScrolledWindowIn);
    append(m_HBox_ControlBoxIn);

    m_ScrolledWindowIn.set_child(m_TreeView_Commands);
    m_ScrolledWindowIn.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindowIn.set_expand();

    m_refTreeModel_Commands = Gtk::ListStore::create(m_Columns_Commands);
    m_TreeView_Commands.set_model(m_refTreeModel_Commands);

    m_TreeView_Commands.append_column("Befehl",       m_Columns_Commands.m_col_command);
    m_TreeView_Commands.append_column("Subbefehl",    m_Columns_Commands.m_col_subcommand);
    m_TreeView_Commands.append_column("Response",     m_Columns_Commands.m_col_response);
    m_TreeView_Commands.append_column("Unformatiert", m_Columns_Commands.m_col_raw);

    m_ButtonBox_CommandDump.append(m_Button_ClearList);
    m_ButtonBox_CommandDump.set_halign(Gtk::Align::END);
    m_ButtonBox_CommandDump.set_sensitive(false);

    m_Button_ClearList.signal_clicked().connect(sigc::mem_fun(*this, &CtrlIncomingCommands::clearList));

    m_Button_AutoCheckLast.set_label("letzten Eintrag markieren");

    m_HBox_ExpanderIn.set_hexpand();

    m_HBox_ControlBoxIn.append(m_HBox_ExpanderIn);
    m_HBox_ControlBoxIn.append(m_Button_AutoCheckLast);
    m_HBox_ControlBoxIn.append(m_ButtonBox_CommandDump);

}

void CtrlIncomingCommands::clearList() {
    m_refTreeModel_Commands->clear();
    m_ButtonBox_CommandDump.set_sensitive(false);
}

void CtrlIncomingCommands::addCommand(const CS2CanCommand &cmd) {
    const auto iter = m_refTreeModel_Commands->append();
    Gtk::TreeModel::Row row = *iter;
    row[m_Columns_Commands.m_col_response  ] = cmd.header[1] & 0x01;
    row[m_Columns_Commands.m_col_command   ] = getCommandName(cmd.getCanCommand());
    row[m_Columns_Commands.m_col_subcommand] = cmd.isSystemCommand() ? getSystemSubCommandName(cmd.getSystemSubCommand()) : "";
    row[m_Columns_Commands.m_col_raw       ] = cmd.getAsString();

    m_ButtonBox_CommandDump.set_sensitive(true);

    if(m_Button_AutoCheckLast.get_active()) {
        const Glib::RefPtr<Gtk::TreeSelection> selection = m_TreeView_Commands.get_selection();
        selection->select(iter);
    }
}
