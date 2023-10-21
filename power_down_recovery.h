/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   power_down_recovery.h                                            :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/10/21 17:05:00                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This function detects lose of power and resets important variables                           */
/*                                                                                                */
/* ********************************************************************************************** */

void  ft_power_down_recovery(void)
{
    RTC_DATA_ATTR static long  power_loss_detector;
    esp_reset_reason_t         reason;

    if (power_loss_detector != 1110111)
    {
        g_cycle_counter = 0;
        g_reboot = false;
        power_loss_detector = 1110111;
        DEBUG_PRINTF("Power-down Recovery was performed.\nThe cycle counter was set to %d\n", g_cycle_counter);
    }
    reason = esp_reset_reason();
    switch (reason)
    {
        case ESP_RST_POWERON:
        case ESP_RST_BROWNOUT:
            DEBUG_PRINTF("\nReset reason: Power-on or Brown-out reset\n", "");
            WiFi.persistent(true);
            client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
            ft_wifi_list();
            if (wifiMulti.run(CONNECT_TIMEOUT) == WL_CONNECTED)
            bot.sendMessage(CHAT_ID, "Hello! I am the IoT Name Badge. I am ON and ready for work!", "");
            break;
        case ESP_RST_SW:
            DEBUG_PRINTF("\nReset reason: Software reset\n", "");
            WiFi.persistent(true);
            client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
            ft_wifi_list();
            if (wifiMulti.run(CONNECT_TIMEOUT) == WL_CONNECTED)
            {
                bot.sendMessage(CHAT_ID, ("I've successfully rebooted. Current software version " + String(SOFTWARE_VERSION)), "");
                delay(1000);
                bot.sendMessage(CHAT_ID, "Is there anything else I can do for you?", "");
                ft_check_incomming_messages(0);
                ft_go_to_sleep(0);
            }
            break;
        case ESP_RST_PANIC:
            DEBUG_PRINTF("\nReset reason: Panic/exception reset\n", "");
            WiFi.persistent(true);
            client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
            ft_wifi_list();
            if (wifiMulti.run(CONNECT_TIMEOUT) == WL_CONNECTED)
            {
                bot.sendMessage(CHAT_ID, "Don't panic, but my Core has just panicked!", "");
                delay(3000);
                bot.sendMessage(CHAT_ID, "You were trying to update me, weren't you? Well, let's try again", "");
                delay(2000);
                ft_check_incomming_messages(ft_ota_mode(CHAT_ID));
                ft_go_to_sleep(0);
            }
            break;
    }
}
