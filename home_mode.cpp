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

static short ft_get_time(int* p_hour, int* p_minute, int* p_week_day)
{
    const char* ntp_server = "pool.ntp.org";
    const long  gmt_offset_sec = TIME_ZONE * 3600;
    const int   daylight_offset_sec = 3600;
    struct tm   time_info;

    ft_wifi_list();
    if (!wifiMulti.run(CONNECT_TIMEOUT) == WL_CONNECTED)
    {
        DEBUG_PRINTF("Failed to obtain time due to Wi-Fi connection issues\n", "");
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        return (0);
    }
    configTime(gmt_offset_sec, daylight_offset_sec, ntp_server);
    if(!getLocalTime(&time_info))
    {
        DEBUG_PRINTF("Failed to obtain time from the NTP server\n", "");
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        return (0);
    }
    *p_hour = time_info.tm_hour;
    *p_minute = time_info.tm_min;
    *p_week_day = time_info.tm_wday;
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    return (1);
}

unsigned int  ft_home_mode(bool* p_errase_display)
{
    int           hour;
    int           minute;
    int           week_day;
    unsigned int  time_of_sleep;

    time_of_sleep = HOME_SLEEP_TIME;
    DEBUG_PRINTF("\nHome Mode initialised.\nBattery state: %d%%\n", globals.battery);
    if (globals.battery <= 20)
    {
        ft_display_battery_state();
        *p_errase_display = true;
    }
    else
        telegram_bot_init(WAIT_FOR_MESSAGES_LIMIT);
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
 
