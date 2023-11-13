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
/* ********************************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <Wire.h>
#include <stdio.h>
#include <ElegantOTA.h>
#include <ArduinoJson.h>
#include <esp_system.h>
#include <driver/adc.h>
#include "bitmap_library.h"
#include "credentials.h"
#include "globals.h"

#define SOFTWARE_VERSION        2.06
//#define PRIVATE                                                       // comment out this line to allow bot answer in any Telegram chat
#define DEBUG                                                         // comment out this line to turn off Serial output
#ifdef DEBUG
  #define DEBUG_PRINTF(x, y) Serial.printf(x, y)
  #define DEBUG_PRINTS(q, w, e, r, t) Serial.printf(q, w, e, r, t)
#else
  #define DEBUG_PRINTF(x, y)
  #define DEBUG_PRINTS(q, w, e, r, t)
#endif
#define CONNECT_TIMEOUT         4000                                  // WiFi timeout per each AP, in milliseconds. Increase if cannot connect.
#define WAIT_FOR_OTA_LIMIT      60                                    // in seconds
#define WAIT_FOR_MESSAGES_LIMIT 80                                    // in seconds, 1 == 2 seconds (80 == 160 seconds == 2,5 minutes)
#define SLEEP_DURATION          60000ul                               // in milliseconds

void  IRAM_ATTR display_bitmap(const unsigned char* output);
void  IRAM_ATTR display_bitmap_with_refresh(const unsigned char* output);
void  IRAM_ATTR display_animated_text_with_font(String output);
void  IRAM_ATTR ft_clear_display(void);
void  IRAM_ATTR ft_display_init(void);
short ft_battery_check(void);
short IRAM_ATTR ft_new_messages(short numNewMessages);
short IRAM_ATTR ft_check_incomming_messages(short cycles);
short telegram_bot_init(short cycles);
void  IRAM_ATTR ft_wifi_list(void);
short ft_ota_mode(String chat_id);
short IRAM_ATTR shall_I_start(void);
void  IRAM_ATTR ft_delay(unsigned int time_in_millis);
void  ft_go_to_sleep(unsigned int time_in_millis);
void  ft_power_down_recovery(void);

#endif
 
