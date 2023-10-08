/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   wifi_list.h                                                      :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/09/27 18:14:16                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   List of known Wi-Fi networks in accordance with the WiFiMulti library. More                  */
/*   networks credentials can be added in an identical fasion ("SSID", "password"). The           */
/*   list must be called before the wifiMulti.run() function, which initiates connection.         */
/*                                                                                                */
/* ********************************************************************************************** */

inline void ft_slide_check(void)
{
    if (g_slide < 1 || g_slide > 6)
    {
        g_slide = 1;
        display_refresh();
    }
    DEBUG_PRINTF("The slide number is set to %d\n", g_slide);
}

short IRAM_ATTR shall_I_start(void)
{
    int i;
    int quantity;

    i = 0;
    WiFi.mode(WIFI_STA);
    if (g_slide > 1 && g_slide <= 6)
    {
        display_refresh();
        return (0);
    }
    DEBUG_PRINTF("Starting WiFi scan...\n", "");
    quantity = WiFi.scanNetworks(false, true);
    if (quantity > 0)
    {
        DEBUG_PRINTF("%d networks found\n", quantity);
        while (i < quantity)
        {
            if (WiFi.SSID(i) == OFFICE_SSID)
            {
                DEBUG_PRINTF("OFFICE network detected\n", "");
                ft_slide_check();
                return (1);
            }
            if (WiFi.SSID(i) == UNIVERSITY_SSID)
            {
                DEBUG_PRINTF("UNIVERSITY network detected\n", "");
                ft_slide_check();
                return (2);
            }
            if (WiFi.SSID(i) == HOME_SSID)
            {
                DEBUG_PRINTF("HOME network detected\n", "");
                ft_slide_check();
                return (3);
            }
            i++;
        }
    }
    else if (quantity == 0)
        DEBUG_PRINTF("No networks found\n", "");
    else
        DEBUG_PRINTF("WiFi scan error %d", quantity);
    display_refresh();
    ft_go_to_sleep(SLEEP_DURATION);
    return (0);
}

void  IRAM_ATTR ft_wifi_list(void)
{
    wifiMulti.addAP(HOME_SSID, HOME_PASSWORD);
    wifiMulti.addAP(UNIVERSITY_SSID, UNIVERSITY_PASSWORD);
    wifiMulti.addAP(OFFICE_SSID, OFFICE_PASSWORD);
}
 
