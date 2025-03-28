/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   constants.h                                                      :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2024/02/13 15:52:46                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   Here you may find all the definitions exept for the credential constants.                    */
/*                                                                                                */
/* ********************************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define SOFTWARE_VERSION        3.04
//# define PRIVATE                                                       // comment out this line to allow bot answer in any Telegram chat
# define DEBUG                                                         // comment out this line to turn off Serial output
# ifdef DEBUG
    #define DEBUG_PRINTF(...)   Serial.printf(__VA_ARGS__)
    #define WD_RESET_INFO       true
# else
    #define DEBUG_PRINTF(...)
    #define WD_RESET_INFO       false
# endif
# define BATTERY_DEFAULT_MAX     1573                                  // see ReadMe regarding this constant
# define BATTERY_DEFAULT_MIN     367                                   // see ReadMe regarding this constant
# define BATTERY_DEFAULT_COEFF   12.06                                 // see ReadMe regarding this constant
# define CONNECT_TIMEOUT         5000                                  // WiFi timeout per each AP, in milliseconds. Increase if cannot connect.
# define WAIT_FOR_MESSAGES_LIMIT 80                                    // how long to wait for new messages (80 == 2,5 minutes)
# define SLEEP_DURATION          60000ul                               // in milliseconds
# define HOME_SLEEP_TIME         1800000ul                             // in milliseconds, 30 minutes
# define DEAD_BATTERY_SLEEP      7200000ul                             // in milliseconds, 2 HOURS
# define ACTIVE                  "1"                                   // OTA on
# define CLOSED                  "0"                                   // ОТА off

# define SPI_SCK_PIN             6                                     // also known as SCL pin
# define SPI_MISO_PIN            -1                                    // NOT USED IN THIS PROJECT
# define SPI_MOSI_PIN            7                                     // also known as SDA pin, as SPI_D pin or as DIN pin
# define SPI_SS_PIN              10                                    // also known as CS pin
# define DC_PIN                  0
# define RST_PIN                 18                                    // also known as RES pin
# define BUSY_PIN                19
# define ENABLE_GxEPD2_GFX       0
# define GxEPD2_DISPLAY_CLASS    GxEPD2_BW
# define GxEPD2_DRIVER_CLASS     GxEPD2_290_T94_V2
# define GxEPD2_BW_IS_GxEPD2_BW  true
# define IS_GxEPD2_BW(x)         IS_GxEPD(GxEPD2_BW_IS_, x)
# define MAX_DISPLAY_BUFFER_SIZE 65536ul
# define MAX_HEIGHT(EPD)         (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))

#endif
 
