/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   header.h                                                         :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2024/02/13 15:52:46                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   Here you may find all the constants definitions.                                             */
/*                                                                                                */
/* ********************************************************************************************** */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SOFTWARE_VERSION        3.00
//#define PRIVATE                                                       // comment out this line to allow bot answer in any Telegram chat
#define DEBUG                                                         // comment out this line to turn off Serial output
#ifdef DEBUG
  #define DEBUG_PRINTF(x, y) Serial.printf(x, y)
  #define DEBUG_PRINTS(q, w, e, r, t) Serial.printf(q, w, e, r, t)
#else
  #define DEBUG_PRINTF(x, y)
  #define DEBUG_PRINTS(q, w, e, r, t)
#endif
#define EEPROM_SIZE             8                                     // stores 2 unsigned shorts with 2-bytes buffers behind each
#define MAX_STATE_ADDR          0
#define MIN_STATE_ADDR          4
#define BATTERY_DEFAULT_MIN     367                                   // see ReadMe regarding this constant
#define BATTERY_DEFAULT_COEFF   12.06                                 // see ReadMe regarding this constant
#define CONNECT_TIMEOUT         5000                                  // WiFi timeout per each AP, in milliseconds. Increase if cannot connect.
#define WAIT_FOR_OTA_LIMIT      60                                    // in seconds
#define WAIT_FOR_MESSAGES_LIMIT 80                                    // in seconds, 1 == 2 seconds (80 == 160 seconds == 2,5 minutes)
#define SLEEP_DURATION          60000ul                               // in milliseconds
#define HOME_SLEEP_TIME         1800000                               // in milliseconds, 30 minutes
#define DEAD_BATTERY_SLEEP      7200000                               // in milliseconds, 2 HOURS

#define SPI_SCK_PIN             6                                     // also known as SCL pin
#define SPI_MISO_PIN            -1                                    // NOT USED IN THIS PROJECT
#define SPI_MOSI_PIN            7                                     // also known as SDA pin, as SPI_D pin or as DIN pin
#define SPI_SS_PIN              10                                    // also known as CS pin
#define DC_PIN                  0
#define RST_PIN                 18                                    // also known as RES pin
#define BUSY_PIN                19
#define ENABLE_GxEPD2_GFX       0
#define GxEPD2_DISPLAY_CLASS    GxEPD2_BW
#define GxEPD2_DRIVER_CLASS     GxEPD2_290_T94_V2
#define GxEPD2_BW_IS_GxEPD2_BW  true
#define IS_GxEPD2_BW(x)         IS_GxEPD(GxEPD2_BW_IS_, x)
#define MAX_DISPLAY_BUFFER_SIZE 65536ul
#define MAX_HEIGHT(EPD)         (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))

#endif
 
