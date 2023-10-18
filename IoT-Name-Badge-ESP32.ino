/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   IoT-Name-Badge-ESP32.ino                                         :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/10/18 17:05:00                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This is the Main file of the IoT Name Badge Project.                                         */
/*   More details in the ReadMe file.                                                             */
/*                                                                                                */
/* ********************************************************************************************** */

#include "header.h"

void  setup(void)
{
    long          cycle_length;
    volatile long run_time;
    long          time_of_sleep;

    cycle_length = 60000;
    run_time = 0;
    time_of_sleep = 0;
    #ifdef DEBUG
        Serial.begin(115200);
        DEBUG_PRINTF("\n\n\nDEVICE START\nversion %f\n", float(SOFTWARE_VERSION));
        DEBUG_PRINTF("cycle number %d\n\n", g_cycle_counter);
    #endif
    ft_power_down_recovery();
    shall_I_start();
    ft_display_init();
    telegram_bot_init();
    WiFi.setSleep(WIFI_MODE_AP);
    display_bitmap_with_refresh(badge_bitmap_slide_6_logo);
    ft_delay(5);
    display_bitmap(badge_bitmap_slide_4_github);
    ft_delay(10);
    display_bitmap(badge_bitmap_slide_5_telegram);
    ft_delay(10);
    display_bitmap(badge_bitmap_slide_3_Roman);
    g_cycle_counter++;
    run_time = millis();
    time_of_sleep = (cycle_length - run_time) * 1000;
    if (time_of_sleep < 10000)
        time_of_sleep = 10000;
    DEBUG_PRINTF("The device will sleep for %lu microseconds\n", time_of_sleep);
    ft_go_to_sleep(time_of_sleep);
}

void  loop(void) { /* NOTHING IS HERE */ }
 
