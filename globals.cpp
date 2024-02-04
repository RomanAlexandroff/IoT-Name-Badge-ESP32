/* ********************************************************************************************** */
/*                                                                                                */
/*   Mini Access Detector Project                                      :::::::::        :::       */
/*   globals.cpp                                                      :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 14:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/11/12 10:35:41                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   Global variables and objects initialization                                                  */
/*                                                                                                */
/* ********************************************************************************************** */

#include "globals.h"

GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(SPI_SS_PIN, DC_PIN, RST_PIN, BUSY_PIN));
WiFiMulti wifiMulti;
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

RTC_DATA_ATTR unsigned short           g_cycle_counter;
RTC_DATA_ATTR volatile unsigned long   g_historic_time;                                 // in seconds

struct GlobalsManagement globals = {
    .reason = ESP_RST_UNKNOWN,
    .battery = 0,
    .reboot = false,
    .ota = false
};
 
