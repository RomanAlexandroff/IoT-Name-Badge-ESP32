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

#include "header.h"

void  ft_power_down_recovery(void)
{
    esp_reset_reason_t  reason;

    reason = esp_reset_reason();
    switch (reason)
    {
        case ESP_RST_POWERON:
        case ESP_RST_BROWNOUT:
            ft_display_bitmap_with_refresh(badge_bitmap_boot_up_screen);
            g_cycle_counter = 0;
            globals.power_on = true;
            globals.reboot = false;
            globals.panic = false;
            DEBUG_PRINTF("\nReset reason: Power-on or Brown-out reset\n", "");
            DEBUG_PRINTF("Power-down Recovery was performed.\nThe cycle counter was set to %d\n", g_cycle_counter);
            ft_delay(3000);
            break;
        case ESP_RST_SW:
            g_cycle_counter++;
            if (g_cycle_counter >= 65004)
                g_cycle_counter = 0;
            DEBUG_PRINTF("\nReset reason: Software reset\n", "");
            DEBUG_PRINTF("cycle number %d\n\n", g_cycle_counter);
            break;
        case ESP_RST_PANIC:
            DEBUG_PRINTF("\nReset reason: Panic/exception reset\n", "");
            globals.panic = true;
            break;
    }
}
