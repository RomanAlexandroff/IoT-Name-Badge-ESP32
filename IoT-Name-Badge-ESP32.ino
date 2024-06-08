/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   IoT-Name-Badge-ESP32.ino                                         :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2024/02/13 15:52:46                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This is the Main file of the IoT Name Badge Project.                                         */
/*   More details in the ReadMe file.                                                             */
/*                                                                                                */
/* ********************************************************************************************** */

#include "IoT-Name-Badge-ESP32.h"

void  setup(void)
{
    #ifdef DEBUG
        Serial.begin(115200);
        DEBUG_PRINTF("\n\nDEVICE START\nversion %s\n", String(SOFTWARE_VERSION));
    #endif
    ft_spiffs_init();
    ft_battery_init();
    ft_display_init();
    ft_power_down_recovery();
    ft_ota_init();
}

void  loop(void)
{
    long          cycle_length;
    volatile long run_time;
    unsigned int  time_of_sleep;

    cycle_length = 60000;
    run_time = 0;
    time_of_sleep = 0;
    ft_ota_waiting_loop();
    ft_battery_check();
    shall_I_start();
    ft_run_slideshow(&cycle_length);
    run_time = millis();
    time_of_sleep = cycle_length - run_time;
    if (time_of_sleep < 10)
        time_of_sleep = 10;
    DEBUG_PRINTF("The device will sleep for %lu milliseconds\n", time_of_sleep);
    ft_go_to_sleep(time_of_sleep);
}
 
