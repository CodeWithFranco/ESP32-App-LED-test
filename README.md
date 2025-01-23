This code uses the same concepts from my Pixel Test Kit but the controls are implemented using an app made from MIT App Inventor. It can control the following led drivers:

a. WS2811

b. TX1818

c. UCS2804B

d. WS2814

Creating an app is a very new skill that I am learning while enjoying the easier approach of coding blocks rather than using Java. I also used ESP32 board that can connect commands via Bluetooth. The following items are the obstacles while developing this project:

1. Since the app is from MIT, I have limited choices on how to make my own app's visual GUI

2. As of 1/23/2025, the app can only work on Android devices.

3. While programming using Arduino IDE, the program will continously reset because of the watchdog timer timeout; possibly caused by FastLED.show() or strip.show() calls when updating large number of LEDs. If there’s no yield() or vTaskDelay() in long loops or heavy operations, the watchdog timer triggers a reset.

4. Delays from the MIT app should be improve in the future. If user is "trigger" happy with the buttons, it may cause a wrong command or issue to the output LED. 

Future Changes:

1. Change the delay for receiving command from MIT app

2. Change the GUI for the app. I want to make a button where the LEDs will have a "LED cycle" rather than a static Red, Blue, Green, and White LED output
