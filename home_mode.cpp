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

static short  ft_get_time(int* p_hour, int* p_minute, String* p_week_day)
{
    int     i;
    String  line;

    i = 0;
    ft_wifi_list();
    if (wifiMulti.run(CONNECT_TIMEOUT) == WL_CONNECTED) 
        DEBUG_PRINTF("Successfully connected to Wi-Fi network", "");
    else
    {
        DEBUG_PRINTF("Unable to connect to Wi-Fi network.", "");
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        return (0);
    }
    HTTPClient http;
    if (!client.connect("www.google.com", 80))
    {
        DEBUG_PRINTF("Google server connection failed", "");
        http.end();
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        return (0);
    }
    DEBUG_PRINTF("Google server connection SUCCESS", "");
    client.print(String("GET / HTTP/1.1\r\n") +
        String("Host: www.google.com\r\n") +
        String("Connection: close\r\n\r\n"));           
    while (!client.available() && i < 10)
    {
        delay(500);
        DEBUG_PRINTF("Retreiving data...", "");
        i++;
    }
    client.setNoDelay(false);
    while (client.connected() && client.available())
    {
        line = client.readStringUntil('\n');
        line.toUpperCase();
        if (line.startsWith("DATE: "))
        {
            *p_week_day = line.substring(6, 9);
            *p_hour = (line.substring(23, 25).toInt());
            *p_minute = line.substring(26, 28).toInt();
        }
    }
    http.end();
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    ft_time_correction(p_hour);
    return (1);
}

long  ft_home_mode(bool* p_errase_display)
{
    short   battery;
    int     hour;
    int     minute;
    String  week_day;
    long    time_of_sleep;

    battery = ft_battery_check();
    if (battery <= 20)
    {
        ft_display_battery_state(battery);
        *p_errase_display = true;
    }
    time_of_sleep = 1800000;                  //30 minutes
    if (ft_get_time(&hour, &minute, &week_day) && (hour >= 21 || hour <= 5))
    {
        if (hour >= 21 && hour <= 23)
            time_of_sleep = (6 + 24 - hour) * 3600000 - (minute * 60000);
        if (hour >= 0 && hour <= 5)
            time_of_sleep = (6 - hour) * 3600000 - (minute * 60000);
    }
    return (time_of_sleep);
}
