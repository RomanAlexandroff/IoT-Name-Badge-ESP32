# The IoT Name Badge

## About the Project

Get ready to meet the IoT Name Badge, the electronic name badge designed to enhance convenience and efficiency of your work life. This nifty gadget can tell if you are at work or not, so it displays your name only to your workmates and automatically hides it as soon as you leave the place. 

That being said, the badge is not limited to your work space only — add as many locations as you want where you are comfortable displaying your personal info. It is not limited solely to a name either. The badge can run a full-blown slideshow of images (e.g. logos, contact info, signs, QR-codes etc.) to impress everyone around!

## Hardware Components

- ESP32–C3–01M Wi-Fi module: Powers the badge with its reliable Wi-Fi connectivity.
- 2.9'' e-paper black-n-white SPI display: Delivers clear visuals and low power consumption.
- 500mAh LiPol battery: Provides ample power for extended usage. 

## How It Works

Here's the lowdown on how the IoT Name Badge operates:
1. The badge's ESP32 periodically wakes up to scan for familiar Wi-Fi networks.
2. If it can't detect any of the familiar networks, it takes a nap to conserve energy.
3. Once a familiar Wi-Fi network is detected, the badge activates the e-paper display and initiates a slideshow of pre-uploaded images.
4. During the slideshow, the ESP32 occasionally checks if it can still detect familiar Wi-Fi networks.
5. If it does find those networks, the slideshow seamlessly keeps on rollin'.
6. But if it can't find the familiar networks any more, the badge clears up the display, and goes back to sleep mode.
7. This cycle repeats indefinitely as long as the battery is charged.

## Key Points

- Effortless Operation: the badge is always on point, automatically activating and deactivating without you lifting a finger.
- Enhanced Privacy: your information gets concealed as soon as you leave the set locations, ensuring data safety.
- No Fuss, All Fun: No need to take off your badge when you're grabbing a coffee outside of your office or commuting from the university in an overcrowded bus. Leave it safe on your neck and it will leave your information safe from everyone's eyes. 
- Energy Efficiency: Thanks to the power-efficient e-paper display, your badge will keep rockin' while conserving energy.
- Dynamic: The badge can showcase individual names or entire slideshows, adapting to diverse scenarios — your imagination is the limit!
- Interact and Connect: When on the display, easily-scanable QR codes can share your contact info or web links. Stay in touch like a true tech pro.

## Features

- Multiple Wi-Fi Enabled: Connect to multiple known Wi-Fi networks instead of being restricted to a single network.
- Telegram Interaction: Write personalized messages onto your badge using the Telegram chat.
- User Commands: Control some badge functionality via Telegram chat commands.
- OTA Update: Effortlessly update the badge's firmware through the Telegram chat, eliminating the need for disassembly.

## Future Development

- Optimize Memory: Move bitmap images into the filesystem, freeing up space for even more features.
- Location Management: Add and delete locations using Telegram chat commands.
- Find Your Badge: If you forget your badge in any of the places you usually go to, it will be able to connect to the Internet and send you its location in the Telegram chat.

## Regards

The project is based on Jean-Marc Zingg's [GxEPD2](https://github.com/ZinggJM/GxEPD2) library for e-paper displays.
      
The Telegram-related functionality is possible thanks to Brian Lough's [Universal Telegram Bot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot) library.

The OTA functionality added using [ElegantOTA](https://github.com/ayushsharma82/ElegantOTA) as well as [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) libraries.


## Example of the credentials.h File

```  
#define BOTtoken    "xxxxxxxxxx:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" // Telegram Bot Token
#define CHAT_ID     "-xxxxxxxxxxxxx"                                 // Telegram chat ID

#define OTA_PASSWORD        1234

#define TIME_ZONE           2                                        // according to the GMT standart

#define SSID1               "wifi1_name"
#define PASSWORD1           "wifi1_password"

#define BACKUP_SSID1        "wifi2_name"
#define BACKUP_PASSWORD1    "wifi2_password"

#define BACKUP_SSID2        "wifi3_name"
#define BACKUP_PASSWORD2    "wifi3_password"
```
 
## Calculating Constants for the Battery Charge Function

You will need to check the following little utility:
https://github.com/RomanAlexandroff/ESP-Battery-Charge-Utility
      
It was designed to be a universal solution for battery charge level detection in ESP-based projects and has all the instructions inside of it.
