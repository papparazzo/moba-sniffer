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

#include "ctrlincomingcommands.h"
#include "feedbackchecker.h"
#include "moba/cs2reader.h"
#include "moba/cs2writer.h"

class FrmMain final: public Gtk::Window {

public:
    FrmMain(CS2WriterPtr cs2writer, const CS2ReaderPtr &cs2reader);

    ~FrmMain() override = default;

private:
    void initAboutDialog();

    void on_button_about_clicked();
    void on_button_emergency_clicked() const;
    void on_about_dialog_response(int response_id);
    bool on_timeout(int timer_number);
    bool on_timeout_status(int);

    // about
    Gtk::Button      m_Button_About{"About..."};
    Gtk::Button      m_Button_Emergency{"Nothalt"};
    Gtk::AboutDialog m_Dialog;

    // status label
    Gtk::Label       m_Label_Connectivity_HW{" \xe2\x96\x84"};
    Gtk::Label       m_Label_Connectivity_SW{" \xe2\x96\x84"};

    Gtk::Box         m_HBox_Expander{Gtk::Orientation::HORIZONTAL, 6};

    Gtk::Box             m_HButtonBox{Gtk::Orientation::HORIZONTAL, 6};
    Gtk::Box             m_VBox{Gtk::Orientation::VERTICAL, 6};
    Gtk::Box             m_HBox_Status{Gtk::Orientation::HORIZONTAL, 6};

    // main window
    Gtk::Paned           m_HPaned{Gtk::Orientation::HORIZONTAL};
    Gtk::Notebook        m_Notebook;

    // controls
    CtrlIncomingCommands incoming_commands;
    FeedbackChecker      feedback_checker;

    CS2WriterPtr cs2writer;
    CS2ReaderPtr cs2reader;
};

