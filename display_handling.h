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

/*  
void  display_text_with_font(String output)               // flikers and inverts colours while running!
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

void  display_text_no_font(String output)                     // flikers and inverts colours while running!
{
    display.setTextColor(GxEPD_BLACK);
    display.setFullWindow();
    display.setTextSize(10);
    display.firstPage();
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, 0);
    display.print(output);
    display.nextPage();
}

void  display_bitmap_unsafe(const unsigned char* output)               // flikers and inverts colours while running!
{
    display.setFullWindow();
    display.firstPage();
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(0, 0);
    display.drawBitmap(0, 0, output, 296, 128, GxEPD_BLACK);
    display.nextPage();
}

void  display_animated_bitmap(const unsigned char* output)              // flikers and inverts colours while running! But animation works fine
{
    int x;

    x = 296;
    display.setFullWindow();
    display.firstPage();
    while (x >= 0)
    {
        display.fillScreen(GxEPD_WHITE);
        display.setCursor(0, 0);
        display.drawBitmap(x, 0, output, 296, 128, GxEPD_BLACK);
        display.nextPage();
        x -= 25;
    }
} */

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
        x -= 25;                            // this value here controls the speed of movement
        if (x + tbw < 0)
            x = display.width();
    } while (display.nextPage());
}

void  IRAM_ATTR display_bitmap(const unsigned char* output)                     // uses Full Screen Partial Mode. Does NOT flicker, does NOT invert colours while running 
{
    display.setPartialWindow(0, 0, display.width(), display.height());
    display.setRotation(1);
    display.firstPage();
    do
    {
        display.fillScreen(GxEPD_WHITE);
        display.setCursor(0, 0);
        display.drawBitmap(0, 0, output, 296, 128, GxEPD_BLACK);
    }
    while (display.nextPage());
}

inline void display_refresh(void)                                            // flickers, but does NOT invert colours while running 
{
    display.setFullWindow();
    display.firstPage();
    display.fillScreen(GxEPD_WHITE);
    display.nextPage();
}

inline void display_init(void)
{
    SPI.end();
    SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_SS_PIN);
    display.init(115200, true, 50, false);
    display.setRotation(1);
}
 
