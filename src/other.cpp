/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   other.cpp                                                        :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2024/02/13 15:52:46                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This file contains all the little utility functions that are not too important to have       */
/*   their own personal files. They are not necesarrily connected with each other logically.      */
/*                                                                                                */
/* ********************************************************************************************** */

#include "../includes/IoT-Name-Badge-ESP32.h"

void  ft_go_to_sleep(uint64_t time_in_millis)
{
    display.powerOff();
    DEBUG_PRINTF("The device was running for %d second(s) this time\n", (millis() / 1000));
    DEBUG_PRINTF("Going to sleep for %u seconds.\n", time_in_millis / 1000);
    DEBUG_PRINTF("\nDEVICE STOP\n\n\n");
    esp_sleep_enable_timer_wakeup(time_in_millis * 1000);
    esp_deep_sleep_start();
}

void  IRAM_ATTR ft_delay(unsigned int time_in_millis)
{
    esp_sleep_enable_timer_wakeup(time_in_millis * 1000);
    esp_light_sleep_start();
}
 
