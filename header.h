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
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <Wire.h>
#include <time.h>
#include <stdio.h>
#include <esp_system.h>
#include <driver/adc.h>
#include "bitmap_library.h"
#include "credentials.h"
#include "globals.h"

#define SOFTWARE_VERSION        2.18
//#define PRIVATE                                                       // comment out this line to allow bot answer in any Telegram chat
#define DEBUG                                                         // comment out this line to turn off Serial output
#ifdef DEBUG
  #define DEBUG_PRINTF(x, y) Serial.printf(x, y)
  #define DEBUG_PRINTS(q, w, e, r, t) Serial.printf(q, w, e, r, t)
#else
  #define DEBUG_PRINTF(x, y)
  #define DEBUG_PRINTS(q, w, e, r, t)
#endif
#define CONNECT_TIMEOUT         5000                                  // WiFi timeout per each AP, in milliseconds. Increase if cannot connect.
#define WAIT_FOR_OTA_LIMIT      60                                    // in seconds
#define WAIT_FOR_MESSAGES_LIMIT 80                                    // in seconds, 1 == 2 seconds (80 == 160 seconds == 2,5 minutes)
#define SLEEP_DURATION          60000ul                               // in milliseconds
#define HOME_SLEEP_TIME         1800000                               // in milliseconds, 30 minutes
#define DEAD_BATTERY_SLEEP      7200000                               // in milliseconds, 2 HOURS

void          IRAM_ATTR ft_display_bitmap(const unsigned char* output);
void          IRAM_ATTR ft_display_bitmap_with_refresh(const unsigned char* output);
void          IRAM_ATTR ft_display_animated_text_with_font(String output);
void          IRAM_ATTR ft_display_battery_state(void);
bool          IRAM_ATTR ft_clear_display(bool errase_display);
void          ft_run_slideshow(long* p_cycle_length);
void          IRAM_ATTR ft_display_init(void);
short         ft_battery_check(void);
short         IRAM_ATTR ft_new_messages(short numNewMessages);
short         IRAM_ATTR ft_check_incomming_messages(short cycles);
void          telegram_bot_init(short cycles);
void          IRAM_ATTR ft_wifi_list(void);
short         ft_ota_mode(String chat_id);
static short  ft_get_time(int* p_hour, int* p_minute, int* p_week_day);
unsigned int  ft_home_mode(bool* p_errase_display);
short         IRAM_ATTR shall_I_start(void);
void          IRAM_ATTR ft_delay(unsigned int time_in_millis);
void          ft_go_to_sleep(uint64_t time_in_millis);
void          ft_power_down_recovery(void);

#endif
 
