/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   IoT-Name-Badge-ESP32.ino                                         :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/09/27 18:14:16                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This is the Main file of the IoT Name Badge Project.                                         */
/*   More details in the ReadMe file.                                                             */
/*                                                                                                */
/* ********************************************************************************************** */

#include "header.h"

void  display_name_with_font(void)
{
    display.setRotation(1);
    display.setFont(&FreeSansBold24pt7b);
    display.setTextColor(GxEPD_BLACK);
    int16_t tbx, tby; uint16_t tbw, tbh;
    //tbx == text boundary x (top left corner); tby == text boundary y (top left corner); tbw == text boundary width; tbx == text boundary hight; 
    display.getTextBounds(g_display_name, 0, 0, &tbx, &tby, &tbw, &tbh);
    // center bounding box by transposition of origin:
    uint16_t x = ((display.width() - tbw) / 2) - tbx;
    uint16_t y = ((display.height() - tbh) / 2) - tby;
    display.setFullWindow();
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        display.setCursor(x, y);
        display.print(g_display_name);
    }
    while (display.nextPage());
}

void  display_name_no_font(void)
{
    display.fillScreen(GxEPD_WHITE);
    display.setTextColor(GxEPD_BLACK);
    display.setTextSize(1);
    display.setCursor(0, 127);
    display.println(g_display_name);
    display.display();
}

void  display_bitmaps(void)
{
    display.drawBitmap(0, 0, name_bitmap_1, 296, 128, GxEPD_BLACK);
    display.display();
    delay(10000);
    display.fillScreen(GxEPD_WHITE);
    display.display();
    display.drawBitmap(0, 0, name_bitmap_2, 296, 128, GxEPD_BLACK);
    display.display();
}

void  setup(void)
{
    #ifdef DEBUG
        Serial.begin(115200);
    #endif
    DEBUG_PRINTF("\n\n\nDEVICE START\n\n", "");
    SPI.end();
    SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_SS_PIN);
    //adc1_config_width(ADC_WIDTH_12Bit);
    //adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_0db);
    esp_sleep_enable_timer_wakeup(g_for_this_long);
    //esp_task_wdt_init(WD_TIMEOUT, true);                                      // watchdog
    display.init(115200);
    
    display.fillScreen(GxEPD_WHITE);
    display.display();
    delay(5000);
    
    display_name_with_font();
    
    delay(10000);
    display.fillScreen(GxEPD_WHITE);
    display.display();
    
    display_name_no_font();
    
    delay(10000);
    
    display.fillScreen(GxEPD_WHITE);
    display.display();
    
    display_bitmaps();
    
    delay(10000);
    
    display.fillScreen(GxEPD_WHITE);
    display.display();
    
    WiFi.persistent(true);                                                    // Save WiFi configuration in flash - optional
    WiFi.mode(WIFI_STA);
    WiFi.hostname("IoT-Name-Badge");
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
    ft_wifi_list();
    if (wifiMulti.run(CONNECT_TIMEOUT) == WL_CONNECTED) 
    {
        //ft_battery_notification();
        ft_ota_mode(CHAT_ID);
        int i = WAIT_FOR_OTA_LIMIT;
        while (i--)
            delay (5000);
    }
    ft_go_to_sleep();
}

void  loop(void) { /* NOTHING IS HERE */ }
 
