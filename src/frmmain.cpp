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

#include <utility>
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

FrmMain::FrmMain(CS2WriterPtr cs2writer, const CS2ReaderPtr &cs2reader): cs2writer{std::move(cs2writer)}, cs2reader{cs2reader} {
    set_icon_name(PACKAGE_NAME);
    set_title(PACKAGE_NAME);

    const sigc::slot<bool()> my_slot1 = sigc::bind(sigc::mem_fun(*this, &FrmMain::on_timeout), 1);
    sigc::connection conn1 = Glib::signal_timeout().connect(my_slot1, 25); // 25 ms

    const sigc::slot<bool()> my_slot2 = sigc::bind(sigc::mem_fun(*this, &FrmMain::on_timeout_status), 1);
    sigc::connection conn2 = Glib::signal_timeout().connect(my_slot2, 850, Glib::PRIORITY_DEFAULT_IDLE); // 850 ms

    m_VBox.set_margin(6);
    set_child(m_VBox);

    m_HPaned.set_expand(true);
    m_VBox.append(m_HPaned);

    m_HPaned.set_start_child(m_Notebook);
    m_HPaned.set_end_child(incoming_commands);

    //m_Notebook.append_page(command_dump, "Command-Logger");
    m_Notebook.append_page(feedback_checker, "Rückmeldungen");

    m_VBox.append(m_HBox_Status);

    m_HBox_Status.set_margin(6);

    m_HBox_Status.append(m_Label_Connectivity_HW);
    m_Label_Connectivity_HW.set_justify(Gtk::Justification::LEFT);
    m_Label_Connectivity_HW.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>");

    m_HBox_Status.append(m_Label_Connectivity_SW);
    m_Label_Connectivity_SW.set_justify(Gtk::Justification::LEFT);
    m_Label_Connectivity_SW.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>");

    m_HBox_Status.append(m_HButtonBox);

    m_HBox_Expander.set_hexpand();
    m_HButtonBox.append(m_HBox_Expander);

    // about-dialog
    m_HButtonBox.append(m_Button_About);
    m_Button_About.signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_button_about_clicked));

    m_HButtonBox.append(m_Button_Emergency);
    m_Button_Emergency.signal_clicked().connect(sigc::mem_fun(*this, &FrmMain::on_button_emergency_clicked));

    m_Button_Emergency.set_sensitive(false);

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





/*

void FrmBase::handleHardwareState(const SystemHardwareStateChanged &data) {
    if(data.hardwareState == SystemHardwareStateChanged::HardwareState::INCIDENT) {
        m_Label_Connectivity_HW.set_tooltip_markup("<b>Status Hardware:</b> Softwarefehler oder Nothalt");
        m_Label_Connectivity_SW.set_tooltip_markup("<b>Status Software:</b> Softwarefehler oder Nothalt");
        systemState = SystemState::INCIDENT;
        m_Button_Emergency.set_label("Freigabe");
        m_Button_Emergency.set_sensitive(true);
        setSystemState(systemState);
        return;
    }
    if(data.hardwareState == SystemHardwareStateChanged::HardwareState::NO_CONNECTION) {
        m_Label_Connectivity_HW.set_tooltip_markup("<b>Status Hardware:</b> Verbindung zur Hardware unterbrochen");
        m_Label_Connectivity_SW.set_tooltip_markup("<b>Status Software:</b> Verbindung zur Hardware unterbrochen");
        systemState = SystemState::NO_CONNECTION;
        m_Button_Emergency.set_sensitive(false);
        setSystemState(systemState);
        return;
    }
    m_Button_Emergency.set_label("Nothalt");
    if(data.hardwareState == SystemHardwareStateChanged::HardwareState::STANDBY) {
        m_Label_Connectivity_HW.set_tooltip_markup("<b>Status Hardware:</b> Energiesparmodus (Anlage stromlos)");
        m_Label_Connectivity_SW.set_tooltip_markup("<b>Status Software:</b> Energiesparmodus");
        systemState = SystemState::STANDBY;
        m_Button_Emergency.set_sensitive(false);
    }
    if(data.hardwareState == SystemHardwareStateChanged::HardwareState::MANUAL) {
        m_Label_Connectivity_HW.set_tooltip_markup("<b>Status Hardware:</b> manuell");
        m_Label_Connectivity_SW.set_tooltip_markup("<b>Status Software:</b> nicht bereit für Automatikmodus");
        systemState = SystemState::MANUAL;
        m_Button_Emergency.set_sensitive(true);
    }
    if(data.hardwareState == SystemHardwareStateChanged::HardwareState::READY) {
        m_Label_Connectivity_HW.set_tooltip_markup("<b>Status Hardware:</b> manuell");
        m_Label_Connectivity_SW.set_tooltip_markup("<b>Status Software:</b> bereit für Automatikmodus");
        systemState = SystemState::READY;
        m_Button_Emergency.set_sensitive(true);
    }
    if(data.hardwareState == SystemHardwareStateChanged::HardwareState::AUTOMATIC) {
        m_Label_Connectivity_HW.set_tooltip_markup("<b>Status Hardware:</b> automatisch");
        m_Label_Connectivity_SW.set_tooltip_markup("<b>Status Software:</b> automatisch");
        systemState = SystemState::AUTOMATIC;
        m_Button_Emergency.set_sensitive(true);
    }
    if(data.hardwareState == SystemHardwareStateChanged::HardwareState::SHUTDOWN) {
        m_Label_Connectivity_HW.set_tooltip_markup("<b>Status Hardware:</b> Anlage stromlos");
        m_Label_Connectivity_SW.set_tooltip_markup("<b>Status Software:</b> Anlage wird heruntergefahren...");
        systemState = SystemState::SHUTDOWN;
        m_Button_Emergency.set_sensitive(false);
    }
    setSystemState(systemState);
}
*/

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
                incoming_commands.addCommand(data);
                cs2writer->send(setEmergencyStop());
            }

        } catch(const std::exception &e) {
/*
            cs2writer->send(setEmergencyStop());
            endpoint->sendMsg(
                SystemTriggerEmergencyStop{
                    SystemTriggerEmergencyStop::EmergencyTriggerReason::SOFTWARE_ERROR,
                    "exception <" + std::string(e.what()) + "> occurred while reading CAN bus. Emergency stop set."
                }
            );
            endpoint->sendMsg(MessagingSendNotification{NotificationData{
                NotificationLevel::ERROR,
                NotificationType::EXCEPTION,
                "JsonWriter Exception",
                e.what(),
                "JsonWriter::operator()()"
            }});
            monitor->printException("JsonWriter::operator()()", e.what());
            */
        }



    /*
    static bool connected = false;

    try {
        if(!connected) {
            msgEndpoint->connect();
            systemState = SystemState::INCIDENT;
            m_Label_Connectivity_HW.set_tooltip_markup("<b>Status Hardware:</b> Keine Verbindung zur Hardware");
            m_Label_Connectivity_SW.set_tooltip_markup("<b>Status Software:</b> Keine Verbindung zur Hardware");
            initialSend();
            setSensitive(true);

            connected = true;
            return true;
        }
        registry.handleMsg(msgEndpoint->receiveMsg());
    } catch(std::exception &e) {
        if(connected) {
            m_Button_Emergency.set_sensitive(false);
            systemState = SystemState::INITIALIZING;
            m_Label_Connectivity_HW.set_tooltip_markup("<b>Status Hardware:</b> Keine Verbindung zum Server");
            m_Label_Connectivity_SW.set_tooltip_markup("<b>Status Software:</b> Keine Verbindung zum Server");

          //  m_InfoBar.set_message_type(Gtk::MessageType::ERROR);
            m_Label_InfoBarMessage.set_markup(getDisplayMessage("msg-handler exception", e.what()));
            m_InfoBar.set_visible(true);
            setSensitive(false);
            connected = false;
        }
    }
    */
    return true;
}

bool FrmMain::on_timeout_status(int) {
/*
    static bool on = false;

    on = !on;
    switch(systemState) {
        case SystemState::INITIALIZING:
            m_Label_Connectivity_SW.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>");
            m_Label_Connectivity_HW.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>");
            break;

        case SystemState::NO_CONNECTION:
            if(on) {
                m_Label_Connectivity_HW.set_markup("<span color=\"red\"> \xe2\x96\x84</span>");
            } else {
                m_Label_Connectivity_HW.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>");
            }
            m_Label_Connectivity_SW.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>");
            break;

        case SystemState::INCIDENT:
            if(on) {
                m_Label_Connectivity_SW.set_markup("<span color=\"red\"> \xe2\x96\x84</span>");
            } else {
                m_Label_Connectivity_SW.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>");
            }
            m_Label_Connectivity_HW.set_markup("<span color=\"gold\"> \xe2\x96\x84</span>");
            break;

        case SystemState::STANDBY:
            m_Label_Connectivity_SW.set_markup("<span color=\"gold\"> \xe2\x96\x84</span>");
            m_Label_Connectivity_HW.set_markup("<span color=\"gold\"> \xe2\x96\x84</span>");
            break;

        case SystemState::MANUAL:
            m_Label_Connectivity_HW.set_markup("<span color=\"green\"> \xe2\x96\x84</span>");
            m_Label_Connectivity_SW.set_markup("<span color=\"green\"> \xe2\x96\x84</span>");
            break;

        case SystemState::READY:
            m_Label_Connectivity_HW.set_markup("<span color=\"green\"> \xe2\x96\x84</span>");
            if(on) {
                m_Label_Connectivity_SW.set_markup("<span color=\"green\"> \xe2\x96\x84</span>");
            } else {
                m_Label_Connectivity_SW.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>");
            }
            break;

        case SystemState::AUTOMATIC:
            if(on) {
                m_Label_Connectivity_SW.set_markup("<span color=\"green\"> \xe2\x96\x84</span>");
                m_Label_Connectivity_HW.set_markup("<span color=\"green\"> \xe2\x96\x84</span>");
            } else {
                m_Label_Connectivity_SW.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>");
                m_Label_Connectivity_HW.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>");
            }
            break;

        case SystemState::SHUTDOWN:
            m_Label_Connectivity_HW.set_markup("<span color=\"gold\"> \xe2\x96\x84</span>");
            if(on) {
                m_Label_Connectivity_SW.set_markup("<span color=\"gold\"> \xe2\x96\x84</span>");
            } else {
                m_Label_Connectivity_SW.set_markup("<span color=\"gray\"> \xe2\x96\x84</span>");
            }
            break;

        default:
            break;
    }
    */
    return true;
}

void FrmMain::on_button_about_clicked() {
    m_Dialog.show();
    m_Dialog.present();
}

void FrmMain::on_button_emergency_clicked() const {
    if(m_Button_Emergency.get_label() == "Nothalt") {
    //    msgEndpoint->sendMsg(SystemTriggerEmergencyStop{});
    } else {
    //    msgEndpoint->sendMsg(SystemReleaseEmergencyStop{});
    }
}

// </editor-fold>
