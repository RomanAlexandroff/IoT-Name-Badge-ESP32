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
    unsigned int  time_of_sleep;

    cycle_length = 60000;
    run_time = 0;
    time_of_sleep = 0;
    #ifdef DEBUG
        Serial.begin(115200);
        DEBUG_PRINTF("\n\nDEVICE START\nversion %f\n", float(SOFTWARE_VERSION));
        DEBUG_PRINTF("cycle number %d\n\n", g_cycle_counter);
    #endif
    ft_battery_check();
    ft_power_down_recovery();
    ft_display_init();
    shall_I_start();
    ft_display_bitmap_with_refresh(badge_bitmap_slide_6_logo);
    ft_delay(8000);
    if (globals.battery <= 20)
    {
        ft_display_battery_state();
        cycle_length = cycle_length + 6000 * (21 - globals.battery);
        ft_delay(8000);
    }
    ft_display_bitmap(badge_bitmap_slide_4_github);
    ft_delay(8000);
    ft_display_bitmap(badge_bitmap_your_ad_slide);
    ft_delay(8000);
    ft_display_bitmap(badge_bitmap_name_slide_v2);
    display.powerOff();
    g_cycle_counter++;
    if (g_cycle_counter >= 65004)
        g_cycle_counter = 0;
    run_time = millis();
    time_of_sleep = cycle_length - run_time;
    if (time_of_sleep < 10)
        time_of_sleep = 10;
    DEBUG_PRINTF("The device will sleep for %lu milliseconds\n", time_of_sleep);
    ft_go_to_sleep(time_of_sleep);
}

void  loop(void) { /* NOTHING IS HERE */ }
 
