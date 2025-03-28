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
 
struct rtc_global_variables {
    unsigned short  cycle_counter;
    String          chat_id;
    String          from_name;
    bool            ota;
};
extern struct rtc_global_variables rtc_g;

struct GlobalsManagement {
    esp_reset_reason_t reason;
    short              battery;
    bool               reboot;
};
extern struct GlobalsManagement globals;

#endif
 
