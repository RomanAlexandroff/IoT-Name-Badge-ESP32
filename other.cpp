/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   other.h                                                          :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/10/18 20:56:16                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This file contains all the little utility functions that are not too important to have       */
/*   their own personal files. They are not necesarrily connected with each other logically.      */
/*                                                                                                */
/* ********************************************************************************************** */

#include "header.h"

void  ft_go_to_sleep(unsigned int time_in_millis)
{
    DEBUG_PRINTF("The device was running for %d second(s) this time\n", (millis() / 1000));
    DEBUG_PRINTF("\nDEVICE STOP\n\n\n", "");
    if (time_in_millis = 10)
        esp_restart();
    esp_sleep_enable_timer_wakeup(time_in_millis * 1000);
    esp_deep_sleep_start();
}

void  IRAM_ATTR ft_delay(unsigned int time_in_millis)
{
    esp_sleep_enable_timer_wakeup(time_in_millis * 1000);
    esp_light_sleep_start();
}

short  ft_battery_check(void)
{
    short i;
    short battery;

    i = 4;
    while (i)
    {
        battery += ceil((adc1_get_raw(ADC1_CHANNEL_0) - 886) / 12.14);                 // see ReadMe regarding these constants
        i--;
    }
    battery = battery / 4;                                                             // counting average of 4 samples
    if (battery <= 0)
        battery = 0;
    if (battery >= 100)
        battery = 100;
    return (battery);
}
 
