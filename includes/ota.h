/* ********************************************************************************************** */
/*                                                                                                */
/*   Flower Happiness Detector                                         :::::::::        :::       */
/*   ota.h                                                            :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2024/05/19 12:50:00                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2024/05/24 18:45:00                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This file contains inline functions declared in the flower_happiness_detector.h header.      */
/*   This file has to be included AFTER all the functions' declarations.                          */
/*                                                                                                */
/* ********************************************************************************************** */

#ifndef OTA_H
# define OTA_H

void ft_ota_init(void)
{
    if (rtc_g.ota)
    {
        char    fullhostname[16] = "IoT Name Badge ";

        if (wifiMulti.run(CONNECT_TIMEOUT) != WL_CONNECTED)
            wifiMulti.run(CONNECT_TIMEOUT);
        if (wifiMulti.run(CONNECT_TIMEOUT) != WL_CONNECTED)
        {
            DEBUG_PRINTF("\n[OTA] Failed to initialise OTA update due to Wi-Fi connection issues\n");
            rtc_g.ota = false;
            ft_write_spiffs_file("/ota.txt", CLOSED);
            return;
        }
        ArduinoOTA.setHostname(fullhostname);
        ArduinoOTA
            .onStart([]() {
                String type;
                if (ArduinoOTA.getCommand() == U_FLASH)
                    type = "sketch";
                else // U_SPIFFS
                    type = "filesystem";
                ft_display_bitmap(badge_bitmap_ota_updating);
                DEBUG_PRINTF("[OTA] Start updating %s", type.c_str());
                bot.sendMessage(rtc_g.chat_id, "Updating...", "");
            })
            .onEnd([]() {
                DEBUG_PRINTF("\n[OTA] End");
                rtc_g.ota = false;
                ft_write_spiffs_file("/ota.txt", CLOSED);
                bot.sendMessage(rtc_g.chat_id, "Successfully updated!", "");
                ft_display_bitmap(badge_bitmap_ota_success);
                ft_delay(5000);
                ft_clear_display(true);
                display.powerOff();
            })
            .onProgress([](unsigned int progress, unsigned int total) {
                DEBUG_PRINTF("\n[OTA] Progress: %u%%\r", (progress / (total / 100)));
            })
            .onError([](ota_error_t error) {
                DEBUG_PRINTF("\n[OTA] Error[%u]: ", error);
                if (error == OTA_AUTH_ERROR) DEBUG_PRINTF("Auth Failed\n", "");
                else if (error == OTA_BEGIN_ERROR) DEBUG_PRINTF("Begin Failed\n", "");
                else if (error == OTA_CONNECT_ERROR) DEBUG_PRINTF("Connect Failed\n", "");
                else if (error == OTA_RECEIVE_ERROR) DEBUG_PRINTF("Receive Failed\n", "");
                else if (error == OTA_END_ERROR) DEBUG_PRINTF("End Failed\n", "");
                bot.sendMessage(rtc_g.chat_id, "Something went wrong. Updating was not completed. Try again later", "");
                rtc_g.ota = false;
                ft_write_spiffs_file("/ota.txt", CLOSED);
                ft_display_bitmap(badge_bitmap_ota_fail);
                ft_delay(5000);
                ft_clear_display(true);
            });
        DEBUG_PRINTF("\n[OTA] Ready to update\n\n");
        bot.sendMessage(rtc_g.chat_id, "OTA Update is active", "");
        ArduinoOTA.begin();
    }
}

void ft_ota_waiting_loop(void)
{
    if (rtc_g.ota)
    {
        uint16_t ota_limit = 0;
        if (wifiMulti.run(CONNECT_TIMEOUT) != WL_CONNECTED)
            wifiMulti.run(CONNECT_TIMEOUT);
        if (wifiMulti.run(CONNECT_TIMEOUT) != WL_CONNECTED)
        {
            DEBUG_PRINTF("\n[OTA] OTA update was canceled due to Wi-Fi connection issues\n");
            rtc_g.ota = false;
            ft_write_spiffs_file("/ota.txt", CLOSED);
            return;
        }
        while (rtc_g.ota && ota_limit < 1000)                                       // 1000 gives 5 minutes to perform OTA
        {
            ArduinoOTA.handle();
            DEBUG_PRINTF("\n[OTA] Active");
            ota_limit++;
            delay(300);
        }
        rtc_g.ota = false;
        ft_write_spiffs_file("/ota.txt", CLOSED);
        bot.sendMessage(rtc_g.chat_id, "OTA Update port closed", "");
        DEBUG_PRINTF("\n[OTA] OTA Update port closed");
    }
}

#endif
 
