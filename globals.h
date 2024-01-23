/* ********************************************************************************************** */
/*                                                                                                */
/*   Mini Access Detector Project                                      :::::::::        :::       */
/*   globals.h                                                        :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/31 14:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/11/12 10:35:41                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   Global variables and objects declaration                                                     */
/*                                                                                                */
/* ********************************************************************************************** */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <WiFiClientSecure.h>
#include <WiFiMulti.h>
#include <UniversalTelegramBot.h>
#include "credentials.h"

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

extern GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display;
extern WiFiMulti wifiMulti;
extern WiFiClientSecure client;
extern UniversalTelegramBot bot;

extern RTC_DATA_ATTR unsigned short  g_cycle_counter;
extern RTC_DATA_ATTR unsigned long   g_historic_time;

struct GlobalsManagement {
    bool  power_on;
    bool  reboot;
    bool  panic;
    bool  ota;
    };
extern struct GlobalsManagement globals;

#endif
