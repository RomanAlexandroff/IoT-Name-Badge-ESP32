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
/*   Battery charge measurement utility with automatic calibration.                               */
/*                                                                                                */
/* ********************************************************************************************** */

#include "header.h"

void IRAM_ATTR  ft_eeprom_init(void)
{
    RTC_DATA_ATTR static short i = 1;
    
    if (!EEPROM.begin(EEPROM_SIZE))
    {
        if (i <= 2)
        {
            i++;
            DEBUG_PRINTF("\nFailed to initialise EEPROM. Restarting %d...\n", i);
            ft_delay(500);
            ESP.restart();
        }
    }
    else
    {
        i = 1;
        DEBUG_PRINTF("\nEEPROM is successfully initialised.\n", "");
        g_eeprom_state = true;
        return;
    }
    i = 1;
    DEBUG_PRINTF("\nEEPROM was not initialised. Reading and Writing data is unavailable this session.\n", "");
    g_eeprom_state = false;
}

void IRAM_ATTR ft_battery_state(const int address)
{
    unsigned short battery;
    unsigned short result;  

    if (!g_eeprom_state)
        return;
    #ifdef DEBUG
        if (address == MAX_STATE_ADDR)
        {
            DEBUG_PRINTF("\n======  EEPROM Test  ======\n", "");
            DEBUG_PRINTF("\n current data in the memory:\n", "");
            DEBUG_PRINTF("  - battery Max state %d\n", EEPROM.readShort(MAX_STATE_ADDR));
            DEBUG_PRINTF("  - battery Min state %d\n", EEPROM.readShort(MIN_STATE_ADDR));
            DEBUG_PRINTF("\n===========================\n", "");
        }
    #endif
    battery = EEPROM.readShort(address);
    result = ceil((adc1_get_raw(ADC1_CHANNEL_0) + battery) / 2);
    EEPROM.writeShort(address, result);
    EEPROM.commit();
}

short  ft_battery_check(void)
{
    short i;
    short min;
    float coeff;

    i = 0;
    if (!g_eeprom_state)
    {
        min = BATTERY_DEFAULT_MIN;
        coeff = BATTERY_DEFAULT_COEFF;
    }
    else
    {
        min = EEPROM.readShort(MIN_STATE_ADDR);
        coeff = (EEPROM.readShort(MAX_STATE_ADDR) - min) / 100;
    }
    while (i < 10)
    {
        globals.battery += ceil((adc1_get_raw(ADC1_CHANNEL_0) - min) / coeff);
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
 
