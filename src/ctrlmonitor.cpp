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

#include "ctrlmonitor.h"
#include <moba-common/loggerprefix.h>

CtrlMonitor::CtrlMonitor(): Box{Gtk::Orientation::VERTICAL, 6} {

    append(m_ScrolledWindowIn);
    append(m_HBox_ControlBoxIn);

    m_ScrolledWindowIn.set_child(m_TreeView_Messages);
    m_ScrolledWindowIn.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindowIn.set_expand();

    m_refTreeModel_Messages = Gtk::ListStore::create(m_ColumnsEntries);
    m_TreeView_Messages.set_model(m_refTreeModel_Messages);

    m_TreeView_Messages.append_column("Zeitpunkt", m_ColumnsEntries.m_col_timestamp);
    m_TreeView_Messages.append_column("Title", m_ColumnsEntries.m_col_caption);
    m_TreeView_Messages.append_column("Ereignis",  m_ColumnsEntries.m_col_message);

    m_ButtonBox_CommandDump.append(m_Button_ClearList);
    m_ButtonBox_CommandDump.set_halign(Gtk::Align::END);
    m_ButtonBox_CommandDump.set_sensitive(false);

    m_Button_ClearList.signal_clicked().connect(sigc::mem_fun(*this, &CtrlMonitor::clearList));

    m_HBox_ControlBoxIn.append(m_ButtonBox_CommandDump);

}

void CtrlMonitor::clearList() {
    m_refTreeModel_Messages->clear();
    m_ButtonBox_CommandDump.set_sensitive(false);
}

void CtrlMonitor::addMessage(const std::string &caption, const std::string &message) {

    const auto iter = m_refTreeModel_Messages->prepend();
    Gtk::TreeModel::Row row = *iter;
    row[m_ColumnsEntries.m_col_caption  ] = caption;
    row[m_ColumnsEntries.m_col_message  ] = message;
    row[m_ColumnsEntries.m_col_timestamp] = moba::getTimeStamp();

    m_ButtonBox_CommandDump.set_sensitive(true);
}


