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

#include "commanddump.h"

#include "moba/cs2utils.h"

CommandDump::CommandDump(): Box{Gtk::Orientation::VERTICAL} {

    m_HPaned.set_expand(true);
    append(m_HPaned);

    initIncoming();
    initOutgoing();
}

void CommandDump::clearList() {
    m_refTreeModel_Commands->clear();
    m_ButtonBox_CommandDump.set_sensitive(false);
}

void CommandDump::addCommand(const CS2CanCommand &cmd) {
    Gtk::TreeModel::iterator iter = m_refTreeModel_Commands->append();
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

void CommandDump::initIncoming() {
    m_HPaned.set_end_child(m_InBox);

    m_InBox.append(m_ScrolledWindowIn);
    m_InBox.append(m_HBox_CheckRow);

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

    m_Button_ClearList.signal_clicked().connect(sigc::mem_fun(*this, &CommandDump::clearList));

    m_Button_AutoCheckLast.set_label("letzten Eintrag markieren");

    m_HBox_Expander.set_hexpand();

    m_HBox_CheckRow.append(m_HBox_Expander);
    m_HBox_CheckRow.append(m_Button_AutoCheckLast);
    m_HBox_CheckRow.append(m_ButtonBox_CommandDump);
}

void CommandDump::initOutgoing() {
    m_HPaned.set_start_child(m_ScrolledWindowOut);

    m_ScrolledWindowOut.set_child(m_TreeView_ActiveApps);
    m_ScrolledWindowOut.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindowOut.set_expand();

    m_refTreeModel_ActiveApps = Gtk::ListStore::create(m_Columns_ActiveApps);
    m_TreeView_ActiveApps.set_model(m_refTreeModel_ActiveApps);

    m_TreeView_ActiveApps.append_column("Id",           m_Columns_ActiveApps.m_col_id);
    m_TreeView_ActiveApps.append_column("Name",         m_Columns_ActiveApps.m_col_name);

    appendCommand(CanCommand::CMD_SYSTEM);
    appendCommand(CanCommand::CMD_LOCO_SPEED);
    appendCommand(CanCommand::CMD_LOCO_DIRECTION);
    appendCommand(CanCommand::CMD_LOCO_FUNCTION);
    appendCommand(CanCommand::CMD_SET_SWITCH);
    appendCommand(CanCommand::CMD_S88_POLLING);
    appendCommand(CanCommand::CMD_S88_EVENT);
    appendCommand(CanCommand::CMD_PING);
}

void CommandDump::appendCommand(CanCommand cmd) const {
    Gtk::TreeModel::Row row = *m_refTreeModel_ActiveApps->append();

    std::stringstream ss;
    ss << std::uppercase << std::hex << std::setfill('0')
       << std::setw(2) << static_cast<unsigned int>(cmd);

    row[m_Columns_ActiveApps.m_col_id  ] = ss.str();
    row[m_Columns_ActiveApps.m_col_name] = getCommandName(cmd);
}

void CommandDump::sendCanCommand(CanCommand cmd) {
    switch(cmd) {
        case CanCommand::CMD_SYSTEM:
        case CanCommand::CMD_LOCO_SPEED:
        case CanCommand::CMD_LOCO_DIRECTION:
        case CanCommand::CMD_LOCO_FUNCTION:
        case CanCommand::CMD_SET_SWITCH:
        case CanCommand::CMD_S88_POLLING:
        case CanCommand::CMD_S88_EVENT:
        case CanCommand::CMD_PING:
            break;
    }
}