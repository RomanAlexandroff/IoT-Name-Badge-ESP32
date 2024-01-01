/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   home_mode.cpp                                                    :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/10/18 17:45:10                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This mode is to preserve as much energy as possible. When the device is at home and knows    */
/*   the current time, it puts itself into uninterrupted night sleep until 6:00. If the device    */
/*   is unable to retreive the current time, it puts itself into extended sleep of 30 minutes.    */
/*                                                                                                */
/* ********************************************************************************************** */

#include "header.h"

static void ft_time_correction(int* p_hour)
{
    *p_hour += TIME_ZONE;
    if (*p_hour > 23)
        *p_hour -= 24;
    if (*p_hour < 0)
        *p_hour = 24 - *p_hour;
}

static short ft_get_time(int* p_hour, int* p_minute, String* p_week_day)
{
    int i;
    String line;

    i = 0;
    ft_wifi_list();
    if (wifiMulti.run(CONNECT_TIMEOUT) == WL_CONNECTED)
        DEBUG_PRINTF("Successfully connected to Wi-Fi network\n", "");
    else
    {
        DEBUG_PRINTF("Unable to connect to Wi-Fi network.\n", "");
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        return (0);
    }
    HTTPClient http;
    if (!http.begin("http://www.google.com"))
    {
        DEBUG_PRINTF("Google server connection failed\n", "");
        http.end();
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        return (0);
    }
    DEBUG_PRINTF("Google server connection SUCCESS\n", "");
    http.addHeader("Connection", "close");
    int httpCode = http.GET();
    if (httpCode > 0)
    {
        DEBUG_PRINTF("Retrieving data...\n", "");
        while (http.connected())
        {
            line = http.getString();
            DEBUG_PRINTF("Received data: %s\n\n", line);
            line.toUpperCase();
            if (line.startsWith("DATE: "))
            {
                *p_week_day = line.substring(6, 9);
                *p_hour = (line.substring(23, 25).toInt());
                *p_minute = line.substring(26, 28).toInt();
            }
        }
    }
    else
    {
        DEBUG_PRINTF("HTTP request failed", "");
        http.end();
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        return (0);
    }
    http.end();
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    ft_time_correction(p_hour);
    return (1);
}

unsigned int  ft_home_mode(bool* p_errase_display)
{
    short         battery;
    int           hour;
    int           minute;
    String        week_day;
    unsigned int  time_of_sleep;

    battery = ft_battery_check();
    DEBUG_PRINTF("\nHome Mode initialised.\nBattery state: %d%%\n", battery);
    if (battery <= 20)
    {
        ft_display_battery_state(battery);
        *p_errase_display = true;
    }
    else
        telegram_bot_init(WAIT_FOR_MESSAGES_LIMIT);
    hour = minute = 6; 
    time_of_sleep = 1800000;                  //30 minutes
    if (ft_get_time(&hour, &minute, &week_day) && (hour >= 21 || hour <= 5))
    {
        if (hour >= 21 && hour <= 23)
            time_of_sleep = (6 + 24 - hour) * 3600000 - (minute * 60000);
        if (hour >= 0 && hour <= 5)
            time_of_sleep = (6 - hour) * 3600000 - (minute * 60000);
    }
    DEBUG_PRINTS("\nFinal values:\nhour = %d\nminute = %d\ntime_of_sleep = %d\n\n", hour, minute, time_of_sleep, "");
    DEBUG_PRINTF("Exiting Home Mode\n\n", "");
    return (time_of_sleep);
}
 
