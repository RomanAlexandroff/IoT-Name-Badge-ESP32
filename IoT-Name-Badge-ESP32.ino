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
    - if not, turn off the working cycle and go deep sleep for a minute until the next cycle
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
    long time_on_display;
    volatile long run_time;
    long time_of_sleep;

    #ifdef DEBUG
        Serial.begin(115200);
    #endif
    DEBUG_PRINTF("\n\n\nDEVICE START. ver. %f\n\n", float(SOFTWARE_VERSION));
    SPI.end();
    SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_SS_PIN);
    display.init(115200, true, 50, false);
    shall_I_start();
    time_on_display = 0;
    run_time = 0;
    time_of_sleep = 0;
    display.setRotation(1);
    switch (g_slide)
    {
        case 1:
            display_bitmap(badge_bitmap_slide_1_hi);
            DEBUG_PRINTF("Now displaying the Slide %d\n", g_slide);
            time_on_display = 2000;
            g_slide++;
            break;
        case 2:
            display_bitmap(badge_bitmap_slide_2_Im);
            DEBUG_PRINTF("Now displaying the Slide %d\n", g_slide);
            time_on_display = 2000;
            g_slide++;
            break;
        case 3:
            display_bitmap(badge_bitmap_slide_3_Roman);
            DEBUG_PRINTF("Now displaying the Slide %d\n", g_slide);
            time_on_display = 10000;
            g_slide++;
            break;
        case 4:
            display_bitmap(badge_bitmap_slide_4_github);
            DEBUG_PRINTF("Now displaying the Slide %d\n", g_slide);
            time_on_display = 5000;
            g_slide++;
            break;
        case 5:
            display_bitmap(badge_bitmap_slide_5_telegram);
            DEBUG_PRINTF("Now displaying the Slide %d\n", g_slide);
            time_on_display = 5000;
            g_slide++;
            break;
        case 6:
            display_bitmap(badge_bitmap_slide_6_logo);
            DEBUG_PRINTF("Now displaying the Slide %d\n", g_slide);
            time_on_display = 5000;
            g_slide++;
            break;
    }
    if (g_slide > 6)
        g_slide = 1;
    telegram_bot_init();
    run_time = millis();
    time_of_sleep = (time_on_display - run_time) * 1000;
    if (time_of_sleep < 10000)
        time_of_sleep = 10000;
    DEBUG_PRINTF("The device will sleep for %lu\n", time_of_sleep);
    ft_go_to_sleep(time_of_sleep);
}

void  loop(void) { /* NOTHING IS HERE */ }
 
