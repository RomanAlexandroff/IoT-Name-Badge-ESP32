/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   power_down_recovery.cpp                                          :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/10/21 17:05:00                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This function detects lose of power and resets important variables                           */
/*                                                                                                */
/* ********************************************************************************************** */

#include "../includes/IoT-Name-Badge-ESP32.h"

void  ft_power_down_recovery(void)
{
    globals.reason = esp_reset_reason();
    switch (globals.reason)
    {
        case ESP_RST_BROWNOUT:
            ft_display_bitmap_with_refresh(badge_bitmap_empty_battery);
            display.powerOff();
            esp_sleep_enable_timer_wakeup(DEAD_BATTERY_SLEEP);
            esp_deep_sleep_start();
            break;
        case ESP_RST_POWERON:
            ft_display_bitmap_with_refresh(badge_bitmap_boot_up_screen);
            ft_files_restore();
            rtc_g.cycle_counter = 0;
            DEBUG_PRINTF("\nReset reason: Power-on or Brown-out reset\n");
            DEBUG_PRINTF("Power-down Recovery was performed.\nThe cycle counter was set to %d\n", rtc_g.cycle_counter);
            ft_delay(3000);
            ft_clear_display(true);
            break;
        case ESP_RST_SW:
            rtc_g.cycle_counter++;
            if (rtc_g.cycle_counter >= 65004)
                rtc_g.cycle_counter = 0;
            DEBUG_PRINTF("\nReset reason: Software reset\n");
            DEBUG_PRINTF("cycle number %d\n\n", rtc_g.cycle_counter);
            break;
        case ESP_RST_PANIC:
            DEBUG_PRINTF("\nReset reason: Panic/exception reset\n");
            break;
    }
}
