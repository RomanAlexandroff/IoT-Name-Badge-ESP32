/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   power_down_recovery.h                                            :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/10/18 17:05:00                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This function detects lose of power and resets important variables                           */
/*                                                                                                */
/* ********************************************************************************************** */

void  ft_power_down_recovery(void)
{
    RTC_DATA_ATTR static long  power_loss_detector;

    if (power_loss_detector != 1110111)
    {
        g_cycle_counter = 0;
        power_loss_detector = 1110111;
        DEBUG_PRINTF("Power-down Recovery was performed.\nThe cycle counter was set to %d\n", g_cycle_counter);
    }
}
