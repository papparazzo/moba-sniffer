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

#include "frmmain.h"

#include "config.h"
#include "moba/cs2utils.h"

namespace {
    constexpr char license[] =
        "Project:    moba-sniffer\n"
        "\n"
        "Copyright (C) 2018 Stefan Paproth <pappi-@gmx.de>\n"
        "\n"
        "This program is free software: you can redistribute it and/or modify\n"
        "it under the terms of the GNU Affero General Public License as\n"
        "published by the Free Software Foundation, either version 3 of the\n"
        "License, or (at your option) any later version.\n"
        "\n"
        "This program is distributed in the hope that it will be useful,\n"
        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n"
        "GNU Affero General Public License for more details.\n"
        "\n"
        "You should have received a copy of the GNU Affero General Public License\n"
        "along with this program. If not, see <https://www.gnu.org/licenses/agpl.txt>.";

    void replace(std::string& str, const std::string& oldStr, const std::string& newStr) {
        std::string::size_type pos = 0u;
        while((pos = str.find(oldStr, pos)) != std::string::npos) {
            str.replace(pos, oldStr.length(), newStr);
            pos += newStr.length();
        }
    }
}

FrmMain::FrmMain(const CS2WriterPtr &cs2writer, const CS2ReaderPtr &cs2reader, OperationModus operation_modus):
feedback_checker{cs2writer}, ctrl_lokcontrol{cs2writer}, ctrl_control{cs2writer},
ctrl_config{cs2writer}, cs2writer{cs2writer}, cs2reader{cs2reader}, m_operation_modus{operation_modus} {
    set_icon_name(PACKAGE_NAME);
    set_title(PACKAGE_NAME);

    const sigc::slot<bool()> my_slot1 = sigc::bind(sigc::mem_fun(*this, &FrmMain::on_timeout), 1);
    sigc::connection conn1 = Glib::signal_timeout().connect(my_slot1, 25); // 25 ms

    m_VBox.set_margin(6);
    set_child(m_VBox);

    m_HPaned.set_expand(true);
    m_VBox.append(m_HPaned);

    m_HPaned.set_start_child(m_Notebook);
    m_HPaned.set_end_child(incoming_commands);

    // Setup notebook...
    m_Notebook.append_page(ctrl_control, "Steuerung");
    m_Notebook.append_page(feedback_checker, "Rückmeldungen");
    m_Notebook.append_page(ctrl_lokcontrol, "Lokomotiven");
    m_Notebook.append_page(ctrl_monitor, "Monitor");
    m_Notebook.append_page(ctrl_config, "Konfiguration");
    //m_Notebook.append_page(ctrl_lokcontrol, "Weichen");

    m_VBox.append(m_HBox_Status);

    m_HBox_Status.set_margin(6);

    m_HBox_Status.append(m_Label_Connectivity_Stop);
    m_Label_Connectivity_Stop.set_tooltip_markup("Ausgehende Verbindung");
    m_Label_Connectivity_Stop.set_justify(Gtk::Justification::LEFT);
    m_Label_Connectivity_Stop.set_markup("<span color=\"green\"> \xe2\x96\x84</span>");

    m_HBox_Status.append(m_Label_Connectivity_In);
    m_Label_Connectivity_In.set_tooltip_markup("Eingehende Verbindung");
    m_Label_Connectivity_In.set_justify(Gtk::Justification::LEFT);
    m_Label_Connectivity_In.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>");

    m_HBox_Status.append(m_HButtonBox);

    m_HBox_Expander.set_hexpand();
    m_HButtonBox.append(m_HBox_Expander);

    // about-dialog
    m_HButtonBox.append(m_Button_About);
    m_Button_About.signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_button_about_clicked));

    m_HButtonBox.append(m_Button_Emergency);
    m_Button_Emergency.signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_button_emergency_clicked));

    initAboutDialog();
}

void FrmMain::initAboutDialog() {
    m_Dialog.set_transient_for(*this);

    m_Dialog.set_program_name(PACKAGE_NAME);
    m_Dialog.set_version(PACKAGE_VERSION);
    m_Dialog.set_copyright("Stefan Paproth");
    m_Dialog.set_comments("Application for testing.");
    m_Dialog.set_license(license);

    m_Dialog.set_website("<pappi-@gmx.de>");
    m_Dialog.set_website_label("pappi-@gmx.de");

    // m_Dialog.set_logo(Gdk::Pixbuf::create_from_file("/usr/local/share/icons/hicolor/scalable/apps/" PACKAGE_NAME ".svg"));

    std::vector<Glib::ustring> list_authors;
    list_authors.emplace_back("Stefan Paproth");
    m_Dialog.set_authors(list_authors);

    m_Button_About.grab_focus();
}

////////////////////////////////////////////////////////////////////////////////
// <editor-fold defaultstate="collapsed" desc="call-back-methodes">
void FrmMain::on_about_dialog_response(int) {
    m_Dialog.hide();
}

bool FrmMain::on_timeout(int) {
    try {
        if(
            CS2CanCommand data;
            cs2reader->read(data)
        ) {
            flash_label();
            incoming_commands.handleCanCommand(data);
            ctrl_control.handleCanCommand(data);
            feedback_checker.handleCanCommand(data);
            ctrl_config.handleCanCommand(data);
        }
    } catch(const std::exception &e) {
        ctrl_monitor.addMessage("FrmMain::on_timeout(int)", e.what());
    }
    return true;
}

void FrmMain::on_button_about_clicked() {
    m_Dialog.show();
    m_Dialog.present();
}

void FrmMain::on_button_emergency_clicked() {
    if(m_Button_Emergency.get_label() == "Nothalt") {
        cs2writer->trySend(setEmergencyStop());
        emergency_stop();
    } else {
        cs2writer->trySend(setEmergencyStopClearing());
        emergency_release();
    }
}

void FrmMain::flash_label() {
    Gtk::Label &label = m_Label_Connectivity_In;
    if(m_Flash_Connectivity_In.connected()) {
        m_Flash_Connectivity_In.disconnect();
    }
    label.set_markup("<span color=\"red\"> \xe2\x96\x84</span>");
    Glib::signal_timeout().connect_once(
        [&label]() { label.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>"); },
        50
    );
}

bool FrmMain::on_timeout_status(int) {
    static bool on = false;

    on = !on;

    if(on) {
        m_Label_Connectivity_Stop.set_markup("<span color=\"red\"> \xe2\x96\x84</span>");
    } else {
        m_Label_Connectivity_Stop.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>");
    }

    return true;
}

void FrmMain::emergency_stop() {
    if(m_EmergencyStop) {
        return;
    }
    on_timeout_status(0);

    const sigc::slot<bool()> slot = sigc::bind(sigc::mem_fun(*this, &FrmMain::on_timeout_status), 1);
    m_StatusTimer = Glib::signal_timeout().connect(slot, 850, Glib::PRIORITY_DEFAULT_IDLE);
    m_EmergencyStop = true;
    m_Button_Emergency.set_label("Freigabe");
}

void FrmMain::emergency_release() {
    m_Label_Connectivity_Stop.set_markup("<span color=\"green\"> \xe2\x96\x84</span>");

    if(m_StatusTimer.connected()) {
        m_StatusTimer.disconnect();
    }
    m_EmergencyStop = false;
    m_Button_Emergency.set_label("Nothalt");
}


// </editor-fold>
