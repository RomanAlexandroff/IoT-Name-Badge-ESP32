/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   header.h                                                         :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/10/18 17:05:12                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*                                                                                                */
/* ********************************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

//#define NOT_BROWNOUT_FRIENDLY                                       // comment out this line to make your brown-out detector happy

#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <Wire.h>
#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <stdio.h>
#include "bitmap_library.h"
#include "credentials.h"
#ifdef NOT_BROWNOUT_FRIENDLY
  #include <WiFiClientSecure.h>
  #include <WiFiMulti.h>
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <ElegantOTA.h>
  #include <UniversalTelegramBot.h>
  #include <ArduinoJson.h>
  #include <esp_system.h>
  #include <driver/adc.h>
#endif

#define SOFTWARE_VERSION        2.05
//#define PRIVATE                                                       // comment out this line to allow bot answer in any Telegram chat
#define DEBUG                                                         // comment out this line to turn off Serial output
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
#define SLEEP_DURATION          60000000ul                            // in microseconds (60000000 == 1 minute; 3600000000 == 1 hour)
#define SPI_SCK_PIN             6                                     // also known as SCL pin
#define SPI_MISO_PIN            -1                                    // NOT USED IN THIS PROJECT
#define SPI_MOSI_PIN            7                                     // also known as SDA pin, as SPI_D pin or as DIN pin
#define SPI_SS_PIN              10                                    // also known as CS pin
#define DC_PIN                  0
#define RST_PIN                 18                                    // also known as RES pin
#define BUSY_PIN                19

#define ENABLE_GxEPD2_GFX 0
#define GxEPD2_DISPLAY_CLASS GxEPD2_BW
#define GxEPD2_DRIVER_CLASS GxEPD2_290_T94_V2
#define GxEPD2_BW_IS_GxEPD2_BW true
#define IS_GxEPD2_BW(x) IS_GxEPD(GxEPD2_BW_IS_, x)
#define MAX_DISPLAY_BUFFER_SIZE 65536ul
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(SPI_SS_PIN, DC_PIN, RST_PIN, BUSY_PIN));

#ifdef NOT_BROWNOUT_FRIENDLY
  WiFiMulti wifiMulti;
  WiFiClientSecure client;
  UniversalTelegramBot bot(BOTtoken, client);
  AsyncWebServer server(80);
#endif

RTC_DATA_ATTR unsigned short  g_cycle_counter;
bool                          g_power_on;
bool                          g_reboot;
bool                          g_panic;

#include "display_handling.h"
#include "other.h"
#include "wifi_networking.h"
#ifdef NOT_BROWNOUT_FRIENDLY
  #include "ota_mode.h"
  #include "telegram_bot_handling.h"
#endif
#include "power_down_recovery.h"

void        IRAM_ATTR display_bitmap(const unsigned char* output);
void        IRAM_ATTR display_animated_text_with_font(String output);
inline void ft_clear_display(void);
inline void ft_display_init(void);
#ifdef NOT_BROWNOUT_FRIENDLY
  short     IRAM_ATTR ft_new_messages(short numNewMessages);
  void      IRAM_ATTR ft_check_incomming_messages(short cycles);
  void      telegram_bot_init(short cycles);
  void      IRAM_ATTR ft_wifi_list(void);
  short     ft_ota_mode(String chat_id);
  short     ft_battery_notification(void);
  short     ft_battery_check(void);
#endif
short       IRAM_ATTR shall_I_start(void);
void        IRAM_ATTR ft_delay(unsigned int time_in_millis);
void        ft_go_to_sleep(unsigned int time_in_millis);
void        ft_power_down_recovery(void);

#endif
 
