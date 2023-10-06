/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   IoT-Name-Badge-ESP32.ino                                         :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/10/02 09:05:00                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This is the Main file of the IoT Name Badge Project.                                         */
/*   More details in the ReadMe file.                                                             */
/*                                                                                                */
/* ********************************************************************************************** */

#include "header.h"

/*
 - turn on
 - quickly check Wi-Fi networks if it is at the right place 
    - if not, turn off the working cyc;e and go deep sleep for a minute until the next cycle
    - if true, proceed to the working cycle
    - initialize all necessary buses and functions
    - start cycling the dafault slides, with the Telegram Sequence and deep sleeping in between
        [HI!] 
          Telegram Sequence, then 2 sec of Deep Sleep and then the whole start-up sequence
        [I'M]
          Telegram Sequence, then 2 sec of Deep Sleep and then the whole start-up sequence
        [NAME]
          Telegram Sequence, then 10 sec of Deep Sleep and then the whole start-up sequence
        [GITHUB]
          Telegram Sequence, then 5 sec of Deep Sleep and then the whole start-up sequence
        [WRITE_ON_ME]
          Telegram Sequence, then 5 sec of Deep Sleep and then the whole start-up sequence
        [LOGO]
          Telegram Sequence, then 5 sec of Deep Sleep and then the whole start-up sequence
    
    Telegram Sequence:
    - try connect to any Wi-Fi
        - if unsuccessfull, continue with the slides,
        - if successful, check incomming messages in Telegram chat,
            - if no messages, continue with the slides,
            - if messages to show, show the message for 10 sec, then continue with the slides.
*/

void  setup(void)
{
    short mode;

    #ifdef DEBUG
        Serial.begin(115200);
    #endif
    DEBUG_PRINTF("\n\n\nDEVICE START\n\n", "");
    esp_sleep_enable_timer_wakeup(SLEEP_DURATION);
    SPI.end();
    SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_SS_PIN);
    display.init(115200, true, 50, false);
    mode = shall_I_start();
    if (!mode)
        ft_go_to_sleep();    
    display.setRotation(1);
    display_refresh();
    WiFi.persistent(true);
    WiFi.mode(WIFI_STA);
    WiFi.hostname("IoT-Name-Badge");
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
    ft_wifi_list();
    if (wifiMulti.run(CONNECT_TIMEOUT) == WL_CONNECTED) 
    {
        display_bitmap(badge_bitmap_slide_1_hi);
        delay(2000);
        display_bitmap(badge_bitmap_slide_2_Im);
        delay(2000);
        display_bitmap(badge_bitmap_slide_3_Roman);
        delay(10000);
        display_bitmap(badge_bitmap_slide_4_github);
        delay(5000);
        display_bitmap(badge_bitmap_slide_5_telegram);
        delay(5000);
        display_bitmap(badge_bitmap_slide_6_logo);
        delay(5000);
        ft_check_incomming_messages(WAIT_FOR_MESSAGES_LIMIT);
    }
    ft_go_to_sleep();
}

void  loop(void) { /* NOTHING IS HERE */ }
 
