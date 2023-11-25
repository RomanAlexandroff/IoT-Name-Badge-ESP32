/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   ota_mode.h                                                       :+:    :+:     :+: :+:      */
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

short  ft_ota_mode(String chat_id) 
{
    String      ssid;
    String      message;
    uint16_t    maxlen;
    const char* nameprefix;
    char*       fullhostname;
    uint8_t     mac[6];

    g_ota = true;
    ssid = WiFi.SSID();
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
    });
    ArduinoOTA.onEnd([chat_id]() {
        bot.sendMessage(chat_id, "Successfully updated!", "");
        ft_clear_display();
        ft_go_to_sleep(10);
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    });
    ArduinoOTA.onError([chat_id](ota_error_t error) {
        bot.sendMessage(chat_id, "Something went wrong. Updating was not completed. Try again", "");
    });
    ArduinoOTA.begin();
    DEBUG_PRINTF("\n\nIoT Name Badge\nOTA update mode initialized.\n\n", "");
    DEBUG_PRINTF("Wi-Fi network: %s\n", ssid.c_str());
    message = "OTA mode activated. \n\nConnected to\n" + String(ssid);
    message += "\n\nConnect to this Wi-Fi and use Arduino IDE";
    message += "\n\nTo cancel the OTA update write any other command.";
    bot.sendMessage(chat_id, message, "");
    return (-2000);
}
 
