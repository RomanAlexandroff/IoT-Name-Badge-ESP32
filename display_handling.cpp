/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project  ESP32-C3                                  :::::::::        :::       */
/*   display_handling.h                                               :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/02 11:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/10/18 12:12:41                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   These functions draw everything on the display                                               */
/*                                                                                                */
/* ********************************************************************************************** */

#include "header.h"

void  IRAM_ATTR display_animated_text_with_font(String output)                 // flikers and inverts colours while running, animation doesn't work yet
{
    int16_t   tbx;
    int16_t   tby;
    uint16_t  tbw;
    uint16_t  tbh;
    uint16_t  y;
    uint16_t  x;

    display.setFont(&FreeSansBold24pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setRotation(1);
    display.getTextBounds(output, 0, 0, &tbx, &tby, &tbw, &tbh);
    y = (display.height() - tbh) / 2;
    x = display.width();
    display.setFullWindow();
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        display.setCursor(x, y);
        display.print(output);
        x -= 25;                                                               // this value here controls the speed of movement
        if (x + tbw < 0)
            x = display.width();
    } while (display.nextPage());
}

void  IRAM_ATTR display_bitmap_with_refresh(const unsigned char* output)       // flickers, does NOT invert colours while running 
{
    display.setRotation(1);
    display.setFullWindow();
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        display.drawBitmap(0, 0, output, 296, 128, GxEPD_BLACK);
    }
    while (display.nextPage());
}

void  IRAM_ATTR display_bitmap(const unsigned char* output)                     // uses Full Screen Partial Mode. Does NOT flicker, does NOT invert colours while running 
{
    display.setPartialWindow(0, 0, display.width(), display.height());
    display.setRotation(1);
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        display.drawBitmap(0, 0, output, 296, 128, GxEPD_BLACK);
    }
    while (display.nextPage());
}

void  IRAM_ATTR ft_clear_display(void)                                               // flickers
{
    display.clearScreen();
    display.writeScreenBuffer();
}


void  IRAM_ATTR ft_display_init(void)
{
    SPI.end();
    SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_SS_PIN);
    display.init(115200);
    display.powerOff();
}



 
