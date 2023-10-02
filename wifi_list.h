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
/*   List of known Wi-Fi networks in accordance with the ESP8266WiFiMulti library. More           */
/*   networks credentials can be added in an identical fasion ("SSID", "password"). The           */
/*   list must be called before the wifiMulti.run() function, which initiates connection.         */
/*                                                                                                */
/* ********************************************************************************************** */

short IRAM_ATTR shall_I_start(void)
{
    int i;
    int quantity;

    i = 0;
    DEBUG_PRINTF("Starting WiFi scan.../n", "");
    WiFi.mode(WIFI_STA);
    quantity = WiFi.scanNetworks(false, true);
    if (quantity > 0)
    {
        DEBUG_PRINTF("%d networks found\n", quantity);
        while (i < quantity)
        {
            if (WiFi.SSID(i) == OFFICE_SSID)
                return (1);
            if (WiFi.SSID(i) == UNIVERSITY_SSID)
                return (2);
            if (WiFi.SSID(i) == HOME_SSID)
                return (3);
            i++;
        }
    }
    else if (quantity == 0)
        DEBUG_PRINTF("No networks found\n", "");
    else
        DEBUG_PRINTF("WiFi scan error %d", quantity);
    display.fillScreen(GxEPD_WHITE);
    display.display();
    return (0);
}

void  IRAM_ATTR ft_wifi_list(void)
{
    wifiMulti.addAP(HOME_SSID, HOME_PASSWORD);
    wifiMulti.addAP(UNIVERSITY_SSID, UNIVERSITY_PASSWORD);
    wifiMulti.addAP(OFFICE_SSID, OFFICE_PASSWORD);
}
 
