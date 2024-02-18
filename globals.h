/* ********************************************************************************************** */
/*                                                                                                */
/*   Mini Access Detector Project                                      :::::::::        :::       */
/*   globals.h                                                        :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 14:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2024/02/13 15:52:46                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   Global variables and objects declaration                                                     */
/*                                                                                                */
/* ********************************************************************************************** */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <WiFiClientSecure.h>
#include <WiFiMulti.h>
#include <UniversalTelegramBot.h>
#include "credentials.h"
#include "constants.h"

extern GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display;
extern WiFiMulti wifiMulti;
extern WiFiClientSecure client;
extern UniversalTelegramBot bot;

extern RTC_DATA_ATTR unsigned short g_cycle_counter;
extern RTC_DATA_ATTR bool           g_eeprom_state;

struct GlobalsManagement {
    esp_reset_reason_t reason;
    short              battery;
    bool               reboot;
    bool               ota;
};
extern struct GlobalsManagement globals;

#endif
 
