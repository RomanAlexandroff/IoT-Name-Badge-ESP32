/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   ota_mode.cpp                                                     :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/09/27 18:14:16                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This file allowes to update the microntroller wirelessly, simply by sending a compiled       */
/*   binary file into its file system. The microcontroller opens a gate, accessable through       */
/*   any web-browser via a link, that is provided by the microcontroller through both Serial      */
/*   port and Telegram chat.                                                                      */
/*   NOTE! When updating, the new software gets downloaded into the OTA memory partition first.   */
/*   So, in Arduino IDE, choosing any "No OTA" partition scheme will block OTA functionality.     */
/*                                                                                                */
/* ********************************************************************************************** */

#include "header.h"

void  ft_ota_init(String chat_id) 
{
    const char* ssid;
    uint16_t    maxlen;
    const char* nameprefix;
    char*       fullhostname;
    uint8_t     mac[6];

    ssid = WiFi.SSID().c_str();
    nameprefix = "IoT Name Badge";
    maxlen = strlen(nameprefix) + 7;
    fullhostname = new char[maxlen];
    WiFi.macAddress(mac);
    snprintf(fullhostname, maxlen, "%s-%02x%02x%02x", nameprefix, mac[3], mac[4], mac[5]);
    ArduinoOTA.setHostname(fullhostname);
    delete[] fullhostname;
    ArduinoOTA.onStart([chat_id]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
        else
            type = "filesystem";
        bot.sendMessage(chat_id, "Updating...", "");
        ft_display_bitmap(badge_bitmap_ota_updating);
    });
    ArduinoOTA.onEnd([chat_id]() {
        bot.sendMessage(chat_id, "Successfully updated!", "");
        ft_display_bitmap(badge_bitmap_ota_success);
        ft_delay(5000);
        ft_clear_display(true);
        display.powerOff();
        ft_delay(500);
        ESP.restart();
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    });
    ArduinoOTA.onError([chat_id](ota_error_t error) {
        bot.sendMessage(chat_id, "Something went wrong. Updating was not completed. Try again", "");
        ft_display_bitmap(badge_bitmap_ota_fail);
        ft_delay(3000);
        ft_clear_display(true);
        ESP.restart();
    });
    ArduinoOTA.begin();
}
 
