/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project  ESP32-C3                                  :::::::::        :::       */
/*   telegram_bot_handling.h                                          :+:    :+:     :+: :+:      */
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
/*                                                                                                */
/* ********************************************************************************************** */

short  IRAM_ATTR ft_answer_engine(String chat_id, String text)
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
//        message += "Battery is " + String(ft_battery_check()) + "% charged, ";
        message += "software version " + String(SOFTWARE_VERSION);
        bot.sendMessage(chat_id, message, "Markdown");
        return (0);
    } 
    if (text == ("/" + String(OTA_PASSWORD)) || text == ("/ota " + String(OTA_PASSWORD)))
    {
        bot.sendMessage(chat_id, "Password accepted", "");
        return (ft_ota_mode(chat_id));
    }
    else if (text == "/reboot")
    {
        bot.sendMessage(chat_id, "Rebooting!", "");
        g_reboot = true;
        return (WAIT_FOR_MESSAGES_LIMIT);
    }
    else if (text == "/off")
    {
        bot.sendMessage(chat_id, "Switching off!", "");
        return (WAIT_FOR_MESSAGES_LIMIT);
    }
    else
    {
        message = text;
        message.remove(0, 1);
        display_animated_text_with_font(message);
        text.clear();
        text = "Roman's badge now says:\n\"" + message + "\"";
        bot.sendMessage(chat_id, text, "");
        return (WAIT_FOR_MESSAGES_LIMIT);
    }
    return (0);
}

short ft_new_messages(short numNewMessages)                                       // function to handle what happens when you receive new messages
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

void  ft_check_incomming_messages(short cycles)
{
    short numNewMessages;

    while (cycles <= WAIT_FOR_MESSAGES_LIMIT)
    {
        ElegantOTA.loop();
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
}

void  telegram_bot_init(short cycles)
{
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
    ft_wifi_list();
    if (wifiMulti.run(CONNECT_TIMEOUT) == WL_CONNECTED)
    {
        if (g_power_on)
        {
            bot.sendMessage(CHAT_ID, "Hello! I am the IoT Name Badge. I am ON and ready for work!", "");
            g_power_on = false;
        }
        if (g_reboot)
        {
            bot.sendMessage(CHAT_ID, ("I've successfully rebooted. Current software version " + String(SOFTWARE_VERSION)), "");
            delay(1000);
            bot.sendMessage(CHAT_ID, "Is there anything else I can do for you?", "");
            cycles = 0;
            g_reboot = false;
        }
        if (g_panic)
        {
            bot.sendMessage(CHAT_ID, "Don't panic, but my Core has just panicked!", "");
            delay(3000);
            bot.sendMessage(CHAT_ID, "You were trying to update me, weren't you? Well, let's try again", "");
            delay(2000);
            ft_check_incomming_messages(ft_ota_mode(CHAT_ID));
            g_panic = false;
            ft_go_to_sleep(10);
        }
        ft_check_incomming_messages(cycles);
    }
    if (g_reboot)
        ft_go_to_sleep(10);
}
 
