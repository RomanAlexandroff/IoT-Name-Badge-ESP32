/* ********************************************************************************************** */
/*                                                                                                */
/*   Soft  Tracker  Project  ESP32-C3                                  :::::::::        :::       */
/*   display_handling.h                                               :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/02 11:49:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/10/02 12:12:41                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   These functions draw everything on the display                                               */
/*                                                                                                */
/* ********************************************************************************************** */

void  display_text_with_font(String output)
{
    display.setFont(&FreeSansBold24pt7b);
    display.setTextColor(GxEPD_BLACK);
    int16_t tbx, tby; uint16_t tbw, tbh;
    //tbx == text boundary x (top left corner); tby == text boundary y (top left corner); tbw == text boundary width; tbx == text boundary hight; 
    display.getTextBounds(output, 0, 0, &tbx, &tby, &tbw, &tbh);
    // center bounding box by transposition of origin:
    uint16_t x = ((display.width() - tbw) / 2) - tbx;
    uint16_t y = ((display.height() - tbh) / 2) - tby;
    display.setFullWindow();
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        display.setCursor(x, y);
        display.print(output);
    }
    while (display.nextPage());
}

void  display_text_no_font(String output)
{
    display.setTextColor(GxEPD_BLACK);
    display.setTextSize(10);
    display.firstPage();
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, 0);
    display.print(output);
    display.nextPage();
}

void  display_bitmap(const unsigned char* output)
{
    display.firstPage();
    display.fillScreen(GxEPD_WHITE);
    display.drawBitmap(0, 0, output, 296, 128, GxEPD_BLACK);
    display.nextPage();
}
 
