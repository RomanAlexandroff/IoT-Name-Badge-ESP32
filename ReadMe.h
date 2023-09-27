/* ********************************************************************************************** */
/*                                                                                                */
/*   IoT  Name  Badge  ESP32-C3                                        :::::::::        :::       */
/*   ReadMe.h                                                         :+:    :+:     :+: :+:      */
/*                                                                   +:+    +:+    +:+   +:+      */
/*   By: Roman Alexandrov <r.aleksandroff@gmail.com>                +#++:++#:    +#++:++#++:      */
/*                                                                 +#+    +#+   +#+     +#+       */
/*   Created: 2023/09/27 18:14:16                                 #+#    #+#   #+#     #+#        */
/*   Updated: 2023/09/27 18:14:16                                ###    ###   ###     ###         */
/*                                                                                                */
/*                                                                                                */
/*   This file contains only notes.                                                               */
/*                                                                                                */
/* ************************************************************************************************
  
          ABOUT THE PROJECT


      
      How it works:
      

      Features:

          - multiple Wi-Fi enabled — every program cycle the Tracker tries to connect to all known
            Wi-Fi networks instead of just one of them;
          - battery status notifications — low battery charge will not go unnoticed by Users, since
            the Tracker can ask them to charge it via Telegram chat;
          - user commands — Users can control some functionality of the Tracker by sending it commands
            via Telegram chat; e.g. add new locations to track right from the Telegram chat and it
            will be stored in the microcontroller memory, your ESP32 will automatically use it next
            time it wakes up — no hardcoding necessary;
          - OTA update — no need to take the Tracker out from wherever you put it to update it! Simply
            open the Telegram chat, command the Tracker to start updating and it will send you a link 
            to open with your web-browser and to drop a binary file with new firmware there.
      
      What applications it can have:
      

      The IoT Name Badge hardware:
      
      - ESP32 module;
      - LiPol Battery, *230mAh, 3.7V   
      * charge-measuring function in other.h uses capacity-specific constants, hence the 230mAh capacity
        is important. To use batteries with different capacities, the constants need to be recalculated,
        otherwise the readings will not be precise. See the instructions at the bottom of the page.

      Future development:


      
      The project is based on Brian Lough's Universal Telegram Bot Library:
      https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot

      The OTA functionality added using AsyncElegantOTA as well as ESPAsyncWebServer libraries:
      https://github.com/ayushsharma82/AsyncElegantOTA
      https://github.com/me-no-dev/ESPAsyncWebServer


  ***********************************************************************************************    


      EXAMPLE OF THE credentials.h FILE
  
      #define BOTtoken      "xxxxxxxxxx:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"     // Telegram Bot Token
      #define CHAT_ID       "-xxxxxxxxxxxxx"                                     // Telegram chat ID

      #define OTA_PASSWORD  1234

      #define BACKUP_SSID1         "home_wifi_name"
      #define BACKUP_PASSWORD1     "home_wifi_password"
    
      #define BACKUP_SSID2         "office_wifi_name"
      #define BACKUP_PASSWORD2     "office_wifi_password"
    
      #define BACKUP_SSID3         "friends_wifi_name"
      #define BACKUP_PASSWORD3     "friends_wifi_password"
     
   
  ***********************************************************************************************


      CALCULATING CONSTANTS FOR BATTERY CHARGE FUNCTION

      First, you need to find out so called Battery_Max_Reading. Fully charge your battery,
      connect it to your ESP, measure the battery state with "adc1_get_raw(ADC1_CHANNEL_0)" command
      and output the measurements into Serial monitor. Battery_Max_Reading is the first number
      outputed to Serial monitor. You will need it later.

      Second, you need to find out so called Battery_Min_Reading. Let ESP connected to Serial 
      monitor until the battery drowns down and ESP browns-out. Battery_Min_Reading is the last 
      number outputed to Serial monitor.

      The 1st constant equals to Battery_Min_Reading. You already have that value. In this sketch
      it equals to 3040 for a 230mAh battery. For other batteries the value may be different.

      The 2nd constant is so called Battery_Coefficient. In this sketch Battery_Coefficient equals
      to 12.22 for a 230mAh battery. For other batteries the number may be different.
      Battery_Coefficient needs to be calculated by the following formula:

      Battery_Coefficient == (Battery_Max_Reading - Battery_Min_Reading) / 100


      Put the obtained constants into the sketch accordingly:

      battery = ceil((adc1_get_raw(ADC1_CHANNEL_0) - Battery_Min_Reading) / Battery_Coefficient);
    

  *********************************************************************************************** */
