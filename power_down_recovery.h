/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   power_down_recovery.h                                            :+:    :+:     :+: :+:      */
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

void  ft_power_down_recovery(void)
{
    RTC_DATA_ATTR static long  power_loss_detector;
    esp_reset_reason_t         reason;

    if (power_loss_detector != 1110111)
    {
        g_cycle_counter = 0;
        g_power_on = false;
        g_reboot = false;
        g_panic = false;
        power_loss_detector = 1110111;
        DEBUG_PRINTF("Power-down Recovery was performed.\nThe cycle counter was set to %d\n", g_cycle_counter);
    }
    reason = esp_reset_reason();
    switch (reason)
    {
        case ESP_RST_POWERON:
        case ESP_RST_BROWNOUT:
            DEBUG_PRINTF("\nReset reason: Power-on or Brown-out reset\n", "");
            g_power_on = true;
            ft_delay(3000);
            break;
        case ESP_RST_SW:
            DEBUG_PRINTF("\nReset reason: Software reset\n", "");
            g_reboot = true;
            break;
        case ESP_RST_PANIC:
            DEBUG_PRINTF("\nReset reason: Panic/exception reset\n", "");
            g_panic = true;
            break;
    }
}
