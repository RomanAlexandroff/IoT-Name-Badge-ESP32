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

#include "IoT-Name-Badge-ESP32.h"

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

static bool ft_result_check(const int address, int32_t result, int32_t old_max, int32_t old_min)
{
        if (address == MAX_STATE_ADDR)
        {
            if (result > old_max + 200 || result < old_max - 200)
                return (false);
            else
                return (true); 
        }
        if (address == MIN_STATE_ADDR)
        {
            if (result > old_min + 200 || result < old_min - 200 || result >= old_max)
                return (false);
            else
                return (true); 
        }
        return (false);
}

void IRAM_ATTR ft_battery_state(const int address)
{
    int32_t battery;
    int32_t result;
    int32_t old_max;
    int32_t old_min; 

    if (!g_eeprom_state)
        return;
    old_max = EEPROM.readShort(MAX_STATE_ADDR);
    old_min = EEPROM.readShort(MIN_STATE_ADDR);
    #ifdef DEBUG
        if (address == MAX_STATE_ADDR)
        {
            DEBUG_PRINTF("\n======  EEPROM Test  ======\n", "");
            DEBUG_PRINTF("\n current data in the memory:\n", "");
            DEBUG_PRINTF("  - battery Max state %d\n", old_max);
            DEBUG_PRINTF("  - battery Min state %d\n", old_min);
            DEBUG_PRINTF("\n===========================\n", "");
        }
    #endif
    battery = EEPROM.readShort(address);
    if (address == MAX_STATE_ADDR && (!battery || battery == 0xFFFF))
        battery = BATTERY_DEFAULT_MAX;
    if (address == MIN_STATE_ADDR && (!battery || battery == 0xFFFF))
        battery = BATTERY_DEFAULT_MIN;
    result = ceil((adc1_get_raw(ADC1_CHANNEL_0) + battery) / 2);
    DEBUG_PRINTF("\nBattery measurement result: %d\n", result);
    if (!ft_result_check(address, result, old_max, old_min))
    {
        DEBUG_PRINTF(" -- The system consideres this result UNacceptable\n\n", "");
        return;
    }
    DEBUG_PRINTF(" -- The system consideres this result acceptable\n\n", "");
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
 
