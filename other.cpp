/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   other.cpp                                                        :+:    :+:     :+: :+:      */
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

void  ft_go_to_sleep(uint64_t time_in_millis)
{
    display.powerOff();
    DEBUG_PRINTF("The device was running for %d second(s) this time\n", (millis() / 1000));
    DEBUG_PRINTF("Going to sleep for %u seconds.\n", time_in_millis / 1000);
    DEBUG_PRINTF("\nDEVICE STOP\n\n\n", "");
    esp_sleep_enable_timer_wakeup(time_in_millis * 1000);
    g_historic_time += (millis() / 1000);
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
    short battery_timed;

    i = 10;
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_11db);
    g_historic_time += millis() / 1000;
    while (i)
    {
        globals.battery += ceil((adc1_get_raw(ADC1_CHANNEL_0) - 367) / 12.06);                 // see ReadMe regarding these constants
        i--;
    }
    globals.battery = globals.battery / 10;                                                    // counting average of 10 samples
    if (globals.battery <= 0)
        globals.battery = 0;
    if (globals.battery >= 100)
        globals.battery = 100;
    return (globals.battery);
}
 
