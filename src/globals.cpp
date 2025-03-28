/* ********************************************************************************************** */
/*                                                                                                */
/*   Mini Access Detector Project                                      :::::::::        :::       */
/*   globals.cpp                                                      :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 14:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2024/02/13 15:52:46                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   Global variables and objects initialization                                                  */
/*                                                                                                */
/* ********************************************************************************************** */

#include "../includes/globals.h"

GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(SPI_SS_PIN, DC_PIN, RST_PIN, BUSY_PIN));
WiFiMulti wifiMulti;
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

RTC_DATA_ATTR struct rtc_global_variables rtc_g;

struct GlobalsManagement globals = {
    .reason = ESP_RST_UNKNOWN,
    .battery = 0,
    .reboot = false,
};
 
