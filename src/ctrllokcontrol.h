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

#include "moba/cs2writer.h"

class CtrlLokControl final: public Gtk::Box {
public:
    explicit CtrlLokControl(CS2WriterPtr cs2writer);

    ~CtrlLokControl() override = default;

private:
    CS2WriterPtr cs2writer;

    class ModelColumns final: public Glib::Object {
    public:
        unsigned int m_col_id;
        Glib::ustring m_col_name;
        bool m_col_active;

        static Glib::RefPtr<ModelColumns> create(const unsigned int col_id, const Glib::ustring& col_name, bool col_active) {
            return Glib::make_refptr_for_instance<ModelColumns>(new ModelColumns(col_id, col_name, col_active));
        }

    protected:
        ModelColumns(const unsigned int col_id, const Glib::ustring& col_name, bool col_active)
        : m_col_id(col_id), m_col_name(col_name), m_col_active(col_active)
        {}
    }; // ModelColumns


    Box m_HBox_DropDown;
    Box m_VBox_ExpanderIn{Gtk::Orientation::VERTICAL, 6};

    Glib::RefPtr<Gtk::Adjustment> m_adjustment;

    Gtk::Scrollbar m_Scrollbar;

    Gtk::DropDown m_DropDown_Loco;
    Gtk::Button   m_Button_Switch_Direction;

    // Functions
    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::ColumnView m_ColumnView;
};


