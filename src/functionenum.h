/*
 *  Project:    moba-lib-msghandling
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
 *  along with this program. If not, see <https://www.gnu.org/licenses/agpl.txt>.
 *
 */

#pragma once
#include <string>

enum class Function {
    NONE                        = 0,   // keine Funktion
    HEADLIGHTS                  = 1,   // Stirnbeleuchtung
    INTERIOR_LIGHT              = 2,   // Innenbeleuchtung
    EXTERIOR_LIGHT              = 3,   // Rücklicht
    LONG_DISTANCE_LIGHTS        = 4,   // Fernlicht
    SOUND                       = 5,   // Geräusch nicht näher spezifiziert
    PANTO                       = 6,   // Pantograf
    SMOKE_UNIT                  = 7,   // Rauchgenerator
    SWITCHING_RANGE_ON          = 8,   // Rangiergang
    TELEX                       = 9,   // Telex-Kupplung beidseitig
    HORN                        = 10,  // Horn
    CONDUCTOR_WHISTLE           = 11,  // Schaffnerpfiff
    WHISTLE_LONG                = 12,  // Lockpfeife lang
    BELL                        = 13,  // Glocke
    ABV_OFF                     = 18,  // ABV aus
    AIR_PUMP                    = 19,  // Luftpumpe
    BRAKE_SQUEALING             = 20,  // Bremsen quietschen (aus)
    GRATE_SHAKING               = 21,  // Schüttelrost, wie 36
    GENERATOR                   = 22,  // Generator
    OPERATING_SOUNDS            = 23,  // Betriebsgeräusch
    SHOVELING_COAL              = 26,  // Kohle schaufeln, wie 31
    DOORS_CLOSING               = 28,  // Türen schließen, wie 156
    BLOWERS                     = 29,  // Lüfter
    SHOVELING_COAL_2            = 31,  // Brennergeräusche, wie 26
    CEILING_LIGHT               = 32,  // Deckenlicht
    TABLE_LIGHT_2               = 34,  // Tischlicht 2
    GRATE_SHAKING_2             = 36,  // Schüttelrost, wie 21
    RAIL_JOINTS                 = 37,  // Schienenstoß
    REAR_LIGHT                  = 41,  // Führerstand hinten
    FRONT_LIGHT                 = 42,  // Führerstand vorne
    COUPLING_UNCOUPLING_SOUND   = 43,  // An-/Abkuppelgeräusch, wie 171
    SPEECH_OUTPUT               = 45,  // Umgebungsgeräusch: Bahnhof
    CAB_LIGHT                   = 48,  // Führerstandsbeleuchtung
    INJECTOR                    = 49,  // Injektor
    REAR_TELEX                  = 82,  // Telex-Kupplung hinten
    FRONT_TELEX                 = 83,  // Telex-Kupplung vorne
    REAR_PANTO                  = 84,  // Pantograf hinten
    FRONT_PANTO                 = 85,  // Pantograf vorne
    RUNNING_GEAR_LIGHT          = 90,  // Triebwerksbeleuchtung
    PANTO_SOUND_UP_DOWN         = 101, // Pantograf-Geräusch (hoch/nieder)
    STATION_ANNOUNCEMENT        = 107, // Bahnhofsdurchsage, wie 153
    FEED_WATER_PUMP             = 111, // Wasserpumpe
    COMPRESSED_AIR              = 116, // Luftpresser
    // = 133,// Überdruckventil kein eigens Piktogramm!
    RELAY_STEPS                 = 133, // Schaltstufen kein eigens Piktogramm!
    // = 137,// Kupplungswalzer
    HORN_SHORT                  = 138, // Rangierhorn kurz
    WHISTLE_SHORT               = 140, // Rangierpfiff kurz
    STATION_ANNOUNCEMENT_2      = 153, // Bahnhofsdurchsage, wie 107
    DOORS_CLOSING_2             = 156, // Türenschließen, wie 28
    COUPLING_UNCOUPLING_SOUND_2 = 171, // An-/Abkuppelngeräusch, wie 43
    BUFFERS_STRIKING            = 172, // Pufferstoß
    SPEECH_OUTPUT_2             = 173, // Sprachausgabe
    CYLINDER_STEAM              = 219, // Zylinder / Dampf
    COMPRESSED_AIR_2            = 220, // Pressluft ablassen
    RADIO_DIALOG                = 231, // Funkgespräch
    PLATFORM_ANNOUNCEMENT       = 232, // Bahnsteigdurchsage
    CAB_CONVERSATION            = 235, // Führerstandsgespräch
    SANDING                     = 236, // Sanden
};

inline std::string controllableFunctionEnumToString(const Function s) {
    switch(s) {
        case Function::NONE:
            return "NONE";

        case Function::HEADLIGHTS:
            return "HEADLIGHTS";

        case Function::INTERIOR_LIGHT:
            return "INTERIOR_LIGHT";

        case Function::EXTERIOR_LIGHT:
            return "EXTERIOR_LIGHT";

        case Function::LONG_DISTANCE_LIGHTS:
            return "LONG_DISTANCE_LIGHTS";

        case Function::SOUND:
            return "SOUND";

        case Function::PANTO:
            return "PANTO";

        case Function::SMOKE_UNIT:
            return "SMOKE_UNIT";

        case Function::SWITCHING_RANGE_ON:
            return "SWITCHING_RANGE_ON";

        case Function::TELEX:
            return "TELEX";

        case Function::HORN:
            return "HORN";

        case Function::CONDUCTOR_WHISTLE:
            return "CONDUCTOR_WHISTLE";

        case Function::WHISTLE_LONG:
            return "WHISTLE_LONG";

        case Function::BELL:
            return "BELL";

        case Function::ABV_OFF:
            return "ABV_OFF";

        case Function::AIR_PUMP:
            return "AIR_PUMP";

        case Function::BRAKE_SQUEALING:
            return "BRAKE_SQUEALING";

        case Function::GRATE_SHAKING:
            return "GRATE_SHAKING";

        case Function::GENERATOR:
            return "GENERATOR";

        case Function::OPERATING_SOUNDS:
            return "OPERATING_SOUNDS";

        case Function::SHOVELING_COAL:
            return "SHOVELING_COAL";

        case Function::DOORS_CLOSING:
            return "DOORSCLOSING";

        case Function::BLOWERS:
            return "BLOWERS";

        case Function::SHOVELING_COAL_2:
            return "SHOVELING_COAL_2";

        case Function::CEILING_LIGHT:
            return "CEILING_LIGHT";

        case Function::TABLE_LIGHT_2:
            return "TABLE_LIGHT_2";

        case Function::GRATE_SHAKING_2:
            return "GRATE_SHAKING_2";

        case Function::RAIL_JOINTS:
            return "RAIL_JOINTS";

        case Function::REAR_LIGHT:
            return "REAR_LIGHT";

        case Function::FRONT_LIGHT:
            return "FRONT_LIGHT";

        case Function::COUPLING_UNCOUPLING_SOUND:
            return "COUPLING_UNCOUPLING_SOUND";

        case Function::SPEECH_OUTPUT:
            return "SPEECH_OUTPUT";

        case Function::CAB_LIGHT:
            return "CAB_LIGHT";

        case Function::INJECTOR:
            return "INJECTOR";

        case Function::REAR_TELEX:
            return "REAR_TELEX";

        case Function::FRONT_TELEX:
            return "FRONT_TELEX";

        case Function::REAR_PANTO:
            return "REAR_PANTO";

        case Function::FRONT_PANTO:
            return "FRONT_PANTO";

        case Function::RUNNING_GEAR_LIGHT:
            return "RUNNING_GEAR_LIGHT";

        case Function::PANTO_SOUND_UP_DOWN:
            return "PANTO_SOUND_UP_DOWN";

        case Function::STATION_ANNOUNCEMENT:
            return "STATION_ANNOUNCEMENT";

        case Function::FEED_WATER_PUMP:
            return "FEED_WATER_PUMP";

        case Function::COMPRESSED_AIR:
            return "COMPRESSED_AIR";

        case Function::RELAY_STEPS:
            return "RELAY_STEPS";

        case Function::HORN_SHORT:
            return "HORN_SHORT";

        case Function::WHISTLE_SHORT:
            return "WHISTLE_SHORT";

        case Function::STATION_ANNOUNCEMENT_2:
            return "STATION_ANNOUNCEMENT_2";

        case Function::DOORS_CLOSING_2:
            return "DOORS_CLOSING";

        case Function::COUPLING_UNCOUPLING_SOUND_2:
            return "COUPLING_UNCOUPLING_SOUND_2";

        case Function::BUFFERS_STRIKING:
            return "BUFFERS_STRIKING";

        case Function::SPEECH_OUTPUT_2:
            return "SPEECH_OUTPUT_2";

        case Function::CYLINDER_STEAM:
            return "CYLINDER_STEAM";

        case Function::COMPRESSED_AIR_2:
            return "COMPRESSED_AIR_2";

        case Function::RADIO_DIALOG:
            return "RADIO_DIALOG";

        case Function::PLATFORM_ANNOUNCEMENT:
            return "PLATFORM_ANNOUNCEMENT";

        case Function::CAB_CONVERSATION:
            return "CAB_CONVERSATION";

        case Function::SANDING:
            return "SANDING";

        default:
            throw moba::UnsupportedOperationException{"ControllableFunction: invalid value given"};
    }
}

inline Function getAlternativeFunction(const Function s) {
    switch(s) {
/*
        case Function::HORN:
            return "HORN";

        case Function::WHISTLE_LONG:
            return "WHISTLE_LONG";

        case Function::BELL:
            return "BELL";

        case Function::CONDUCTOR_WHISTLE:
            return Function::DOORSCLOSING;

        case Function::SHOVELING_COAL:
            return Function::SHOVELING_COAL_2;

        case Function::SHOVELING_COAL_2:
            return Function::SHOVELING_COAL;

        case Function::CEILING_LIGHT:
            return "CEILING_LIGHT";

        case Function::TABLE_LIGHT_2:
            return "TABLE_LIGHT_2";

        case Function::GRATE_SHAKING_2:
            return "GRATE_SHAKING_2";

        case Function::RAIL_JOINTS:
            return "RAIL_JOINTS";

        case Function::REAR_LIGHT:
            return "REAR_LIGHT";

        case Function::FRONT_LIGHT:
            return "FRONT_LIGHT";

        case Function::COUPLING_UNCOUPLING_SOUND:
            return "COUPLING_UNCOUPLING_SOUND";

        case Function::SPEECHOUTPUT:
            return "SPEECHOUTPUT";

        case Function::CAB_LIGHT:
            return "CAB_LIGHT";

        case Function::INJECTOR:
            return "INJECTOR";

        case Function::REAR_TELEX:
            return "REAR_TELEX";

        case Function::FRONT_TELEX:
            return "FRONT_TELEX";

        case Function::REAR_PANTO:
            return "REAR_PANTO";

        case Function::FRONT_PANTO:
            return Function::PANTO_SOUND_UP_DOWN;

        case Function::RUNNING_GEARLIGHT:
            return "RUNNING_GEARLIGHT";

        case Function::PANTO_SOUND_UP_DOWN:
            return "PANTO_SOUND_UP_DOWN";

        case Function::STATION_ANNOUNCEMENT:
            return "STATION_ANNOUNCEMENT";

        case Function::FEED_WATER_PUMP:
            return "FEED_WATER_PUMP";

        case Function::COMPRESSED_AIR:
            return "COMPRESSED_AIR";

        case Function::RELAYSTEPS:
            return "RELAYSTEPS";

        case Function::HORN_SHORT:
            return "HORN_SHORT";

        case Function::WHISTLE_SHORT:
            return "WHISTLE_SHORT";

        case Function::STATION_ANNOUNCEMENT_2:
            return "STATION_ANNOUNCEMENT_2";

        case Function::DOORS_CLOSING:
            return Function::CONDUCTOR_WHISTLE;

        case Function::COUPLING_UNCOUPLING_SOUND_2:
            return "COUPLING_UNCOUPLING_SOUND_2";

        case Function::BUFFERS_STRIKING:
            return "BUFFERS_STRIKING";

        case Function::SPEECHOUTPUT_2:
            return "SPEECHOUTPUT_2";

        case Function::CYLINDER_STEAM:
            return "CYLINDER_STEAM";

        case Function::COMPRESSED_AIR_2:
            return "COMPRESSED_AIR_2";

        case Function::RADIO_DIALOG:
            return "RADIO_DIALOG";

        case Function::PLATFORM_ANNOUNCEMENT:
            return "PLATFORM_ANNOUNCEMENT";

        case Function::CAB_CONVERSATION:
            return "CAB_CONVERSATION";

        case Function::SANDING:
            return "SANDING";
            */
        default:
            throw moba::UnsupportedOperationException{"ControllableFunction: invalid value given"};
    }
}

inline Function getFollowupFunction(const Function f) {
    switch(f) {
        case Function::CONDUCTOR_WHISTLE:
            return Function::DOORS_CLOSING;
        default:
            throw moba::UnsupportedOperationException{"ControllableFunction: invalid value given"};
    }
}
