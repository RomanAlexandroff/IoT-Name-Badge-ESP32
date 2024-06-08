/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   battery_management.cpp                                           :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2024/02/13 10:32:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2024/02/13 15:52:46                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/* ********************************************************************************************** */

#include "IoT-Name-Badge-ESP32.h"

short  ft_battery_check(void)
{
    short i;

    i = 0;
    while (i < 10)
    {
        globals.battery += ceil((adc1_get_raw(ADC1_CHANNEL_0) - BATTERY_DEFAULT_MIN) / BATTERY_DEFAULT_COEFF);
        i++;
    }
    globals.battery = globals.battery / i;                                            // counting average of i samples
    if (globals.battery <= 0)
        globals.battery = 0;
    if (globals.battery >= 100)
        globals.battery = 100;
    return (globals.battery);
}

void IRAM_ATTR ft_battery_init(void)
{
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_11db);
}
 
