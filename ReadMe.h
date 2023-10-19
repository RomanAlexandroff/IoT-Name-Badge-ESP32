/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   ReadMe.h                                                         :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/10/18 16:05:38                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This file contains only notes.                                                               */
/*                                                                                                */
/* ************************************************************************************************
  
          ABOUT THE PROJECT

      E-paper electronic badge that can be updated from your Telegram chat.
      The project is currently under construction and yet requires a lot of fixing and polishing.

      Features:

          - multiple Wi-Fi enabled — every program cycle the Tracker tries to connect to all known
            Wi-Fi networks instead of just one of them;
          - user commands — Users can control some functionality of the Tracker by sending it commands
            via Telegram chat;
          - OTA update — no need to take the Tracker out from wherever you put it to update it! Simply
            open the Telegram chat, command the Tracker to start updating and it will send you a link 
            to open with your web-browser and to drop a binary file with new firmware there.
      

      The IoT Name Badge hardware:
      
      - ESP32–C3–01M module;
      - WeAct 2.9'' E-paper black/white display;
      - LiPol Battery, *230mAh, 3.7V   
      * charge-measuring function in other.h uses capacity-specific constants, hence the 230mAh capacity
        is important. To use batteries with different capacities, the constants may need to be
        recalculated, otherwise the readings will not be precise. See the instructions at the bottom
        of the page.

      
      The project is based on Jean-Marc Zingg's GxEPD2 library for E-paper displays:
      https://github.com/ZinggJM/GxEPD2
      
      The Telegram-related functionality is possible thanks to the Universal Telegram Bot library:
      https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot

      The OTA functionality added using AsyncElegantOTA as well as ESPAsyncWebServer libraries:
      https://github.com/ayushsharma82/AsyncElegantOTA
      https://github.com/me-no-dev/ESPAsyncWebServer


  ***********************************************************************************************    


      EXAMPLE OF THE credentials.h FILE
  
      #define BOTtoken      "xxxxxxxxxx:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"     // Telegram Bot Token
      #define CHAT_ID       "-xxxxxxxxxxxxx"                                     // Telegram chat ID

      #define HOME_SSID             "home_wifi_name"
      #define HOME_PASSWORD         "home_wifi_password"
    
      #define UNIVERSITY_SSID       "uni_wifi_name"
      #define UNIVERSITY_PASSWORD   "uni_wifi_password"
    
      #define OFFICE_SSID           "office_wifi_name"
      #define OFFICE_PASSWORD       "office_wifi_password"


   
  ***********************************************************************************************


      CALCULATING CONSTANTS FOR BATTERY CHARGE FUNCTION

      You will need to check the following little utility:
      https://github.com/RomanAlexandroff/ESP-Battery-Charge-Utility
      
      It was designed to be a universal solution for battery charge level detection in ESP-based
      projects and has all the instructions inside of it.
    

  *********************************************************************************************** */
