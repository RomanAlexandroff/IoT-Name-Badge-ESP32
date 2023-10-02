/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   header.h                                                         :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/09/27 18:14:16                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*                                                                                                */
/* ********************************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <Arduino.h>                                                  // OTA
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiMulti.h>
#include <Wire.h>
#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <stdio.h>
#include <AsyncTCP.h>                                                 // OTA
#include <ESPAsyncWebServer.h>                                        // OTA
#include <AsyncElegantOTA.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>                                              // Telegram
#include <SPIFFS.h>
#include <driver/adc.h>
#include "esp_adc_cal.h"
#include <esp_task_wdt.h>
#include "bitmap_library.h"
#include "credentials.h"

#define SOFTWARE_VERSION        0.15
#define PRIVATE                                                       // comment out this line to allow bot answer in any Telegram chat
//#define DEBUG                                                         // comment out this line to turn off Serial output
#ifdef DEBUG
  #define DEBUG_PRINTF(x, y) Serial.printf(x, y)
  #define DEBUG_PRINTS(q, w, e, r, t) Serial.printf(q, w, e, r, t)
#else
  #define DEBUG_PRINTF(x, y)
  #define DEBUG_PRINTS(q, w, e, r, t)
#endif
#define WD_TIMEOUT              8000                                  // watchdog, in milliseconds (5000 == 5 seconds; 8500 — system max val)
#define CONNECT_TIMEOUT         3000                                  // WiFi timeout per each AP, in milliseconds. Increase if cannot connect.
#define WAIT_FOR_OTA_LIMIT      60                                    // in seconds
#define WAIT_FOR_MESSAGES_LIMIT 80                                    // in seconds, 1 == 2 seconds (80 == 160 seconds == 2,5 minutes)
#define SLEEP_DURATION          30000000ul                            // in microseconds (60000000 == 1 minute; 3600000000 == 1 hour)
#define SPI_SCK_PIN             6                                     // also known as SCL pin
#define SPI_MISO_PIN            -1                                    // NOT USED IN THIS PROJECT
#define SPI_MOSI_PIN            7                                     // also known as SDA pin, as SPI_D pin or as DIN pin
#define SPI_SS_PIN              10                                    // also known as CS pin
#define DC_PIN                  0
#define RST_PIN                 18                                    // also known as RES pin
#define BUSY_PIN                19
#define ENABLE_GxEPD2_GFX       0                                     // enable or disable GxEPD2_GFX base class
#define GxEPD2_DISPLAY_CLASS    GxEPD2_BW
#define GxEPD2_DRIVER_CLASS     GxEPD2_290_T94_V2
#define GxEPD2_BW_IS_GxEPD2_BW  true
#define IS_GxEPD2_BW(x)         IS_GxEPD(GxEPD2_BW_IS_, x)
#define MAX_DISPLAY_BUFFER_SIZE 65536ul
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(SPI_SS_PIN, DC_PIN, RST_PIN, BUSY_PIN));

WiFiMulti wifiMulti;
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
AsyncWebServer server(80);

#include "other.h"
#include "ota_mode.h"
#include "wifi_list.h"
#include "display_handling.h"
#include "check_incomming_messages.h"

void    IRAM_ATTR display_text_with_font(String output);
void    IRAM_ATTR display_text_no_font(String output);
void    IRAM_ATTR display_bitmap(const unsigned char* output);
short   IRAM_ATTR ft_new_messages(short numNewMessages);
void    IRAM_ATTR ft_check_incomming_messages(short cycles);
short   IRAM_ATTR shall_I_start(void);
void    IRAM_ATTR ft_wifi_list(void);
short   ft_ota_mode(String chat_id);
short   ft_battery_notification(void);
short   ft_battery_check(void);
void    ft_go_to_sleep(void);

#endif
 
