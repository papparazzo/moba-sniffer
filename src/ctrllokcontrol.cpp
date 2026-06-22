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

#include "moba/cs2utils.h"

CtrlLokControl::CtrlLokControl(CS2WriterPtr cs2writer):
    Box{Gtk::Orientation::VERTICAL, 6},
    cs2writer{std::move(cs2writer)},
    m_HBox_DropDown(Gtk::Orientation::HORIZONTAL, 10),
    m_adjustment( Gtk::Adjustment::create(0.0, 0.0, 1000.0, 1.0, 10.0, 10.0) ),
    m_Scrollbar(m_adjustment),
    m_Button_Switch_Direction("Fahrtrichtungswechsel"),
    m_Button_Halt("Lok halt")
{
/*
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

    append(m_Button_Halt);
    m_Button_Halt.set_margin(10);

    append(m_ScrolledWindow);
    m_ScrolledWindow.set_child(m_ColumnView);

    // Only show the scrollbars when they are necessary:
    m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    m_ScrolledWindow.set_expand();

    append(m_VBox_ExpanderIn);
    m_VBox_ExpanderIn.set_vexpand(true);


/*
    // Create the List model:
    m_ListStore = Gio::ListStore<ModelColumns>::create();
    m_ListStore->append(ModelColumns::create(1, "Frontlicht", true));
    m_ListStore->append(ModelColumns::create(2, "Pantograph", false));
    m_ListStore->append(ModelColumns::create(3, "Sound", false));

    // Set list model and selection model.
    auto selection_model = Gtk::SingleSelection::create(m_ListStore);
    selection_model->set_autoselect(false);
    selection_model->set_can_unselect(true);
    m_ColumnView.set_model(selection_model);
    m_ColumnView.add_css_class("data-table"); // high density table

    // Make the columns reorderable.
    // This is not necessary, but it's nice to show the feature.
    m_ColumnView.set_reorderable(true);


    // Add the ColumnView's columns:

    // Id column
    auto factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this, &CtrlLokControl::on_setup_label), Gtk::Align::END));
    factory->signal_bind().connect(sigc::mem_fun(*this, &CtrlLokControl::on_bind_id));
    auto column = Gtk::ColumnViewColumn::create("#", factory);
    m_ColumnView.append_column(column);

    // Name column
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this, &CtrlLokControl::on_setup_label), Gtk::Align::START));
    factory->signal_bind().connect(sigc::mem_fun(*this, &CtrlLokControl::on_bind_name));
    column = Gtk::ColumnViewColumn::create("Funktion", factory);
    m_ColumnView.append_column(column);

    // Percentage column
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::mem_fun(*this, &CtrlLokControl::on_setup_checkbox));
    factory->signal_bind().connect(sigc::mem_fun(*this, &CtrlLokControl::on_bind_active));
    column = Gtk::ColumnViewColumn::create("an / aus", factory);
    m_ColumnView.append_column(column);
    */
}

void CtrlLokControl::on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item, Gtk::Align halign) {
    list_item->set_child(*Gtk::make_managed<Gtk::Label>("", halign));
}

void CtrlLokControl::on_setup_checkbox(const Glib::RefPtr<Gtk::ListItem>& list_item) {
    list_item->set_child(*Gtk::make_managed<Gtk::CheckButton>());
}

void CtrlLokControl::on_bind_id(const Glib::RefPtr<Gtk::ListItem>& list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if(!col) {
        return;
    }

    auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
    if(!label) {
        return;
    }

    label->set_text(Glib::ustring::format(col->m_col_id));
}

void CtrlLokControl::on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if(!col) {
        return;
    }

    auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
    if(!label) {
        return;
    }

    label->set_text(col->m_col_name);
}

void CtrlLokControl::on_bind_active(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto progressbar = dynamic_cast<Gtk::CheckButton*>(list_item->get_child());
  if (!progressbar)
    return;
  progressbar->set_active(col->m_col_active );
}

void CtrlLokControl::on_halt_click() {
    cs2writer->send(setLocoHalt(currentLocalId));
}

void CtrlLokControl::on_switch_direction_click() {
    cs2writer->send(setLocDirection(currentLocalId, 3));
}



