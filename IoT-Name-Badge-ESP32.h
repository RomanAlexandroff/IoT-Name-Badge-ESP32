/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   IoT-Name-Badge-ESP32.h                                           :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2024/02/13 15:52:46                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/* ********************************************************************************************** */

#ifndef IOT_NAME_BADGE_ESP32_H
# define IOT_NAME_BADGE_ESP32_H

#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "EEPROM.h"
#include <Wire.h>
#include <time.h>
#include <stdio.h>
#include <esp_system.h>
#include <driver/adc.h>
#include "bitmap_library.h"
#include "globals.h"

void  IRAM_ATTR        ft_display_bitmap(const unsigned char* output);
void  IRAM_ATTR        ft_display_bitmap_with_refresh(const unsigned char* output);
void  IRAM_ATTR        ft_display_animated_text_with_font(String output);
void  IRAM_ATTR        ft_display_battery_state(void);
bool  IRAM_ATTR        ft_clear_display(bool errase_display);
void                   ft_run_slideshow(long* p_cycle_length);
void  IRAM_ATTR        ft_display_init(void);
void  IRAM_ATTR        ft_eeprom_init(void);
static bool            ft_result_check(const int address, int32_t result, int32_t old_max, int32_t old_min);
void  IRAM_ATTR        ft_battery_state(const int address);
short                  ft_battery_check(void);
void  IRAM_ATTR        ft_battery_init(void);
static short IRAM_ATTR ft_answer_engine(String chat_id, String text);
static short IRAM_ATTR ft_new_messages(short numNewMessages);
static short IRAM_ATTR ft_check_incomming_messages(short cycles);
void                   telegram_bot_init(short cycles);
void  IRAM_ATTR        ft_wifi_list(void);
void                   ft_ota_init(String chat_id);
static short           ft_get_time(int* p_hour, int* p_minute, int* p_week_day);
unsigned int           ft_home_mode(bool* p_errase_display);
short IRAM_ATTR        shall_I_start(void);
void  IRAM_ATTR        ft_delay(unsigned int time_in_millis);
void                   ft_go_to_sleep(uint64_t time_in_millis);
void                   ft_power_down_recovery(void);

#endif
 
