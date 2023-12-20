/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   wifi_list.cpp                                                    :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/10/18 17:45:10                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   List of known Wi-Fi networks in accordance with the WiFiMulti library. More                  */
/*   networks credentials can be added in an identical fasion ("SSID", "password"). The           */
/*   list must be called before the wifiMulti.run() function, which initiates connection.         */
/*                                                                                                */
/* ********************************************************************************************** */

#include "header.h"

short IRAM_ATTR shall_I_start(void)
{
    RTC_DATA_ATTR static bool errase_display;
    int                       i;
    int                       quantity;
    long                      time_of_sleep;

    WiFi.mode(WIFI_STA);
    if (g_cycle_counter % 3 != 0)                //check Wi-Fi only every 3rd cycle
    {
        errase_display = true;
        return (1);
    }
    DEBUG_PRINTF("Starting WiFi scan...\n", "");
    WiFi.persistent(true);
    quantity = WiFi.scanNetworks(false, true);
    i = 0;
    if (quantity <= 0)
    {
        DEBUG_PRINTF("No networks found OR WiFi scan error #%d\n", quantity);
        if (errase_display || g_power_on)
        {
            ft_clear_display();
            errase_display = false;
            g_power_on = false;
        }
        ft_go_to_sleep(SLEEP_DURATION);
    }
    else
    {
        DEBUG_PRINTF("%d networks found\n", quantity);
        while (i < quantity)
        {
            if (WiFi.SSID(i) == HOME_SSID)
            {
                DEBUG_PRINTF("Home network detected. Going into extended sleep\n", "");
                time_of_sleep = ft_home_mode(&errase_display);
                if (errase_display || g_power_on)
                {
                    ft_clear_display();
                    errase_display = false;
                    g_power_on = false;
                    display.powerOff();
                }
                ft_go_to_sleep(time_of_sleep);
            }
            else if (WiFi.SSID(i) == OFFICE_SSID    || WiFi.SSID(i) == UNIVERSITY_SSID || WiFi.SSID(i) == BACKUP_SSID    ||
                     WiFi.SSID(i) == SCHOOL42_SSID1 || WiFi.SSID(i) == SCHOOL42_SSID2  || WiFi.SSID(i) == SCHOOL42_SSID3 ||
                     WiFi.SSID(i) == SCHOOL42_SSID4 || WiFi.SSID(i) == SCHOOL42_SSID5  || WiFi.SSID(i) == SCHOOL42_SSID6 ||
                     WiFi.SSID(i) == SCHOOL42_SSID7 || WiFi.SSID(i) == SCHOOL42_SSID8  || WiFi.SSID(i) == SCHOOL42_SSID9 ||
                     WiFi.SSID(i) == SCHOOL42_SSID10)
            {
                DEBUG_PRINTF("Familiar network detected. Initiating the slideshow\n", "");
                errase_display = true;
                return (1);
            }
            i++;
        }
        ft_clear_display();
        errase_display = false;
        g_power_on = false;
        ft_go_to_sleep(SLEEP_DURATION);
    }
    return (0);
}

void  IRAM_ATTR ft_wifi_list(void)
{
    wifiMulti.addAP(BACKUP_SSID, BACKUP_PASSWORD);
    wifiMulti.addAP(HOME_SSID, HOME_PASSWORD);
    wifiMulti.addAP(UNIVERSITY_SSID, UNIVERSITY_PASSWORD);
    wifiMulti.addAP(OFFICE_SSID, OFFICE_PASSWORD);
}
 
