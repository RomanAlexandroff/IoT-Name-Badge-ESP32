/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project  ESP32-C3                                  :::::::::        :::       */
/*   telegram_bot_handling.cpp                                        :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/09 14:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/09/25 09:48:41                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   These functions are for checking on new Telegram messages, reading them and reacting to      */
/*   them accordingly.                                                                            */
/*   WARNING! DO NOT CALL THE ft_go_to_sleep() FUNCTION FROM ANY OF THESE FUNCTIONS! THE DEVICE   */
/*   WOULD BECOME UNRESPONSIVE TO ANY MESSAGES FROM THE TELEGRAM CHAT!                            */
/*   The "cycles" variable is also responsible for how long the device stays ON and responds to   */
/*   the user's messages. E.g. cycles == WAIT_FOR_MESSAGES_LIMIT equals to ≈ 1 second;            */
/*   cycles == 0 equals to ≈ 2 x WAIT_FOR_MESSAGES_LIMIT seconds; cycles == -32767 equals to      */
/*   ≈ 2 x (32767 + WAIT_FOR_MESSAGES_LIMIT) seconds.                                             */
/*                                                                                                */
/* ********************************************************************************************** */

#include "IoT-Name-Badge-ESP32.h"

static short  IRAM_ATTR ft_answer_engine(String chat_id, String text)
{
    String      message;

    #ifdef PRIVATE
    if (chat_id != CHAT_ID)
    {
        bot.sendMessage(chat_id, "UNAUTHORIZED. ACCESS DENIED.\nThe device is unaccessable from this chat.\n\nhttps://www.youtube.com/watch?v=XV25MrouozE", "");
        return (WAIT_FOR_MESSAGES_LIMIT);
    }
    #endif
    if (text == "/status")
    {
        message = "Connected to " + String(WiFi.SSID());   
        message += ". Signal strength is " + String(WiFi.RSSI()) + " dBm. ";
        message += "Battery is " + String(globals.battery) + "% charged, ";
        message += "software version " + String(SOFTWARE_VERSION);
        bot.sendMessage(chat_id, message, "Markdown");
        return (0);
    } 
    else if (text == ("/" + String(OTA_PASSWORD)) || text == ("/ota " + String(OTA_PASSWORD)))
    {
        bot.sendMessage(chat_id, "Password accepted", "");
        DEBUG_PRINTF("\n\nIoT Name Badge\nOTA update mode activated.\n\n", "");
        bot.sendMessage(chat_id, "OTA mode activated", "");
        ft_display_bitmap_with_refresh(badge_bitmap_ota_active);
        globals.ota = true;
        return (WAIT_FOR_OTA_LIMIT);
    }
    else if (text == "/reboot")
    {
        bot.sendMessage(chat_id, "Rebooting!", "");
        globals.reboot = true;
        return (WAIT_FOR_MESSAGES_LIMIT);
    }
    else if (text == "/off")
    {
        bot.sendMessage(chat_id, "Switching off!", "");
        return (WAIT_FOR_MESSAGES_LIMIT);
    }
    else if (text == "/clear")
    {
        bot.sendMessage(chat_id, "The display has been cleared", "");
        ft_clear_display(true);
        return (0);
    }
    else
    {
        message = text;
        message.remove(0, 1);
        ft_display_animated_text_with_font(message);
        text.clear();
        text = "Roman's badge now says:\n\"" + message + "\"";
        bot.sendMessage(chat_id, text, "");
        return (0);
    }
    return (0);
}

static short ft_new_messages(short numNewMessages)                                // function to handle what happens when you receive new messages
{
    short   cycles;
    String  chat_id;
    String  text;
    String  from_name;

    cycles = WAIT_FOR_MESSAGES_LIMIT;
    DEBUG_PRINTF("\nHandling new messages\n", "");
    DEBUG_PRINTF("Number of messages to handle: %d\n", numNewMessages);
    for (short i = 0; i < numNewMessages; i++) 
    {
        DEBUG_PRINTF("Handling loop iterations: i = %d\n", i);
        chat_id = String(bot.messages[i].chat_id);
        text = bot.messages[i].text;
        from_name = bot.messages[i].from_name;
        DEBUG_PRINTF("%s says: ", from_name.c_str());
        DEBUG_PRINTF("%s\n\n", text.c_str());
        cycles = ft_answer_engine(chat_id, text);
    }
    return (cycles);
}

static short  ft_check_incomming_messages(short cycles)
{
    short numNewMessages;

    while (cycles <= WAIT_FOR_MESSAGES_LIMIT)
    {
        if (globals.ota)
            ArduinoOTA.handle();
        DEBUG_PRINTF("Waiting for incomming commands from Telegram chat. Waiting loop cycles: %d\n", cycles);       
        numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        while (numNewMessages)
        {
            cycles = ft_new_messages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
        if ((cycles + 25) == WAIT_FOR_MESSAGES_LIMIT)
            bot.sendMessage(CHAT_ID, "Going to sleep in 1 minute. To keep me awake, write me any command", "");
        if ((cycles + 1) == WAIT_FOR_MESSAGES_LIMIT)
            bot.sendMessage(CHAT_ID, "Good talk! I'm off now", "");
        cycles++; 
    }
    return (numNewMessages);
}

void  telegram_bot_init(short cycles)
{
    short numNewMessages;
    
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
    ft_wifi_list();
    if (wifiMulti.run(CONNECT_TIMEOUT) == WL_CONNECTED)
    {
        ft_ota_init(CHAT_ID);
        DEBUG_PRINTF("\nTelegram bot initialised\n", "");
        switch (globals.reason)
        {
            case ESP_RST_POWERON:
                bot.sendMessage(CHAT_ID, "Hello! I am the IoT Name Badge. I am ON and ready for work!", "");
                break;
            case ESP_RST_PANIC:
                bot.sendMessage(CHAT_ID, "Don't panic, but my Core has just panicked!", "");
                cycles = 0;
                break;
        }
        numNewMessages = ft_check_incomming_messages(cycles);
    }
    esp_wifi_set_mode(WIFI_MODE_NULL);
    if (globals.ota)
        ft_clear_display(true);
    DEBUG_PRINTF("Telegram bot has stopped. Wi-Fi is now OFF\n", "");
    if (globals.reboot)
        ESP.restart();
}
 
