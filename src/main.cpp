/*
 *  Project:    moba-sniffer
 *
 *  Copyright (C) 2016 Stefan Paproth <pappi-@gmx.de>
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

#include "cs2connector.h"
#include <moba/helper.h>
#include <iostream>

#include <cstring>

        enum CanCommand {
            CMD_SYSTEM                                  = 0x00,
            CMD_LOCO_DISCOVERY                          = 0x02,
            CMD_MFX_BIND                                = 0x04,
            CMD_MFX_VERIFY                              = 0x06,
            CMD_LOCO_SPEED                              = 0x08,
            CMD_LOCO_DIRECTION                          = 0x0A,
            CMD_LOCO_FUNCTION                           = 0x0C,
            CMD_READ_CONFIG                             = 0x0E,
            CMD_WRITE_CONFIG                            = 0x10,
            CMD_SET_SWITCH                              = 0x16,
            CMD_ATTACHMENTS_CONFIG                      = 0x18,
            CMD_S88_POLLING                             = 0x20,
            CMD_S88_EVENT                               = 0x22,
            CMD_SX1_EVENT                               = 0x24,
            CMD_PING                                    = 0x30,
            CMD_UPDATE_OFFER                            = 0x32,
            CMD_READ_CONFIG_DATA                        = 0x34,
            CMD_BOOTLOADER_CAN                          = 0x36,
            CMD_BOOTLOADER_TRACK                        = 0x38,
            CMD_STATUS_DATA_CONFIGURATION               = 0x3A,
            CMD_CONFIG_DATA_QUERY                       = 0x40,
            CMD_CONFIG_DATA_STREAM                      = 0x42,
            CMD_60128_CONNECT_6021_DATA_STREAM          = 0x44,
        };

        enum SystemSubCommand {
            SYS_SUB_CMD_SYSTEM_STOP                        = 0x00,
            SYS_SUB_CMD_SYSTEM_GO                          = 0x01,
            SYS_SUB_CMD_SYSTEM_HALT                        = 0x02,
            SYS_SUB_CMD_LOCO_EMERGENCY_STOP                = 0x03,
            SYS_SUB_CMD_LOCO_CYCLE_STOP                    = 0x04,
//            SYS_SUB_CMD_Lok Datenprotokoll                 = 0x05,
            SYS_SUB_CMD_CIRCUIT_TIME_ATTACHMENTS_DECODER   = 0x06,
            SYS_SUB_CMD_FAST_READ_MFX                      = 0x07,
//            SYS_SUB_CMD_Gleisprotokoll frei schalten       = 0x08,
//            SYS_SUB_CMD_System MFX Neuanmeldezähler setzen = 0x09,
            SYS_SUB_CMD_SYSTEM_OVERLAOD                    = 0x0A,
            SYS_SUB_CMD_SYSTEM_STATUS                      = 0x0B,
            SYS_SUB_CMD_SYSTEM_IDENTIFIER                  = 0x0C,
            SYS_SUB_CMD_MFX_SEEK                           = 0x30,
            SYS_SUB_CMD_SYSTEM_RESET                       = 0x80,
        };


std::string getCommmandAsString(int cmd) {
    switch(cmd) {
        case CMD_SYSTEM:
            return "CMD_SYSTEM";

        case CMD_LOCO_DISCOVERY:
            return "CMD_LOCO_DISCOVERY";

        case CMD_MFX_BIND:
            return "CMD_MFX_BIND";

        case CMD_MFX_VERIFY:
            return "CMD_MFX_VERIFY";

        case CMD_LOCO_SPEED:
            return "CMD_LOCO_SPEED";

        case CMD_LOCO_DIRECTION:
            return "CMD_LOCO_DIRECTION";

        case CMD_LOCO_FUNCTION:
            return "CMD_LOCO_FUNCTION";

        case CMD_READ_CONFIG:
            return "CMD_READ_CONFIG";

        case CMD_WRITE_CONFIG:
            return "CMD_WRITE_CONFIG";

        case CMD_SET_SWITCH:
            return "CMD_SET_SWITCH";

        case CMD_ATTACHMENTS_CONFIG:
            return "CMD_ATTACHMENTS_CONFIG";

        case CMD_S88_POLLING:
            return "CMD_S88_POLLING";

        case CMD_S88_EVENT:
            return "CMD_S88_EVENT";

        case CMD_SX1_EVENT:
            return "CMD_SX1_EVENT";

        case CMD_PING:
            return "CMD_PING";

        case CMD_UPDATE_OFFER:
            return "CMD_UPDATE_OFFER";

        case CMD_READ_CONFIG_DATA:
            return "CMD_READ_CONFIG_DATA";

        case CMD_BOOTLOADER_CAN:
            return "CMD_BOOTLOADER_CAN";

        case CMD_BOOTLOADER_TRACK:
            return "CMD_BOOTLOADER_TRACK";

        case CMD_STATUS_DATA_CONFIGURATION:
            return "CMD_STATUS_DATA_CONFIGURATION";

        case CMD_CONFIG_DATA_QUERY:
            return "CMD_CONFIG_DATA_QUERY";

        case CMD_CONFIG_DATA_STREAM:
            return "CMD_CONFIG_DATA_STREAM";

        case CMD_60128_CONNECT_6021_DATA_STREAM:
            return "CMD_60128_CONNECT_6021_DATA_STREAM";

        default:
            return "UNBEKANNT";
    }
}

std::string getSystemSubCommand(int subCmd) {
    switch(subCmd) {
        case SYS_SUB_CMD_SYSTEM_STOP:
            return "SYS_SUB_CMD_SYSTEM_STOP";

        case SYS_SUB_CMD_SYSTEM_GO:
            return "SYS_SUB_CMD_SYSTEM_GO";

        case SYS_SUB_CMD_SYSTEM_HALT:
            return "SYS_SUB_CMD_SSYSTEM_HALT";

        case SYS_SUB_CMD_LOCO_EMERGENCY_STOP:
            return "SYS_SUB_CMD_LOCO_EMERGENCY_STOP";

        case SYS_SUB_CMD_LOCO_CYCLE_STOP:
            return "SYS_SUB_CMD_LOCO_CYCLE_STOP";

        //case         SYS_SUB_CMD_Lok Datenprotokoll
        case SYS_SUB_CMD_CIRCUIT_TIME_ATTACHMENTS_DECODER:
            return "SYS_SUB_CMD_CIRCUIT_TIME_ATTACHMENTS_DECODER";

        case SYS_SUB_CMD_FAST_READ_MFX:
            return "SYS_SUB_CMD_FAST_READ_MFX";

        //case         SYS_SUB_CMD_Gleisprotokoll frei schalten
        //case         SYS_SUB_CMD_System MFX Neuanmeldezähler s

        case SYS_SUB_CMD_SYSTEM_OVERLAOD:
            return "SYS_SUB_CMD_SYSTEM_OVERLAOD";

        case SYS_SUB_CMD_SYSTEM_STATUS:
            return "SYS_SUB_CMD_SYSTEM_STATUS";

        case SYS_SUB_CMD_SYSTEM_IDENTIFIER:
            return "SYS_SUB_CMD_SYSTEM_IDENTIFIER";

        case SYS_SUB_CMD_MFX_SEEK:
            return "SYS_SUB_CMD_MFX_SEEK";

        case SYS_SUB_CMD_SYSTEM_RESET:
            return "SYS_SUB_CMD_SYSTEM_RESET";

        default:
            return "UNBEKANNT";
    }
}


int main(int argc, char *argv[]) {
    moba::setCoreFileSizeToULimit();

    CS2Connector cs2;

    cs2.connect("192.168.178.38");



    CS2Connector::RawData raw;
    memset((void*)&raw, '\0', sizeof(raw));

    raw.hash[0] = 0x03;
    raw.hash[1] = 0x00;

    raw.header[0] = 0x00;
    raw.header[1] = 0x30;


    raw.length = 0;
    //raw.data[0] = 0x00; // Sub Cmd Stop

    cs2.sendData(raw);

    while(1) {
        CS2Connector::RawData raw = cs2.recieveData();

        printf(
            "%02X %02X - %02X %02X - %02X - %02X %02X %02X %02X - %02X %02X %02X %02X\n",
            static_cast<unsigned int>(raw.header[0]),
            static_cast<unsigned int>(raw.header[1]),
            static_cast<unsigned int>(raw.hash[0]),
            static_cast<unsigned int>(raw.hash[1]),
            static_cast<unsigned int>(raw.length),
            static_cast<unsigned int>(raw.uid[0]),
            static_cast<unsigned int>(raw.uid[1]),
            static_cast<unsigned int>(raw.uid[2]),
            static_cast<unsigned int>(raw.uid[3]),
            static_cast<unsigned int>(raw.data[0]),
            static_cast<unsigned int>(raw.data[1]),
            static_cast<unsigned int>(raw.data[2]),
            static_cast<unsigned int>(raw.data[3])
        );

        bool response = false;

        if(raw.header[1] & 0x01) {
            response = true;
        }
        raw.header[1] &= ~0x01;

        std::cerr << (response ? "[R] " : "[ ] ") << getCommmandAsString(raw.header[1]);

        if(raw.header[1] == CMD_SYSTEM) {
            std::cerr << " - " << getSystemSubCommand(raw.data[0]);
        }

        std::cerr << std::endl;
        std::cerr << "---------------------------------------------------------------";
        std::cerr << std::endl;
    }
}




/*
#include <iostream>

#include <gtkmm/application.h>



#include "frmmain.h"
#include "config.h"


    auto app = Gtk::Application::create(argc, argv, "org.moba.sniffer");

    FrmMain frmMain;
    frmMain.set_title("CS2 Sniffer");
    frmMain.set_border_width(10);
    frmMain.set_default_size(400, 200);

    return app->run(frmMain);
}

 */