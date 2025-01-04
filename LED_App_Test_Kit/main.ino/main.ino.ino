/*******************************************************
Title: Pixel Test Android App
Author: Franco Nepomuceno
Rev: A
Description: App that controls colors and dimming LEDs
using MIT App Inventor and the following chipset:
1. WS2811: Fastled Library
2. UCS2804B: Adafruit NeoPixel Library
3. TX1818: Fastled Library
4. WS2814F: Adafruit NeoPixel Library
********************************************************/

#include <BluetoothSerial.h>
#include "WS2811_TX1818.h"
#include "UCS2904B.h"
#define DATA_PIN 11

String strPlaceHolder = "";  // Placeholder for incoming characters
String chipsetStr = "";      // String to store chipset value

int cutpoint = 0;            // Integer to store cutpoint value
int colorSelect = -1;        // Initialize as -1 (no color selected)    
int intensity = 1;            // Brightness level (1-255)    
int chipsetInt = 0;
 
bool isBTStarted = false;     // Track BT state
bool isCutpointReceived = false;  // Flag to track Cutpoint reception
bool isChipsetReceived = false;   // Flag to track Chipset reception
bool isColorSelected = false;     // Flag to track color selection

CRGB *leds;                   // Allocated array for FASTLEDs - Pointer 
BluetoothSerial SerialBT;     // Bluetooth object

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_LED");  // Start Bluetooth with the name "ESP32_LED"
    Serial.println("Bluetooth started. Ready to connect.");
}

void loop() {
    if (SerialBT.hasClient()) 
    {
        if (SerialBT.available()) 
        {
            delay(15);         
            strPlaceHolder = SerialBT.readStringUntil('\n');  // Read one String at a time
            
            //Check value
            Serial.print("Value: ");
            Serial.println(strPlaceHolder);

            // Process Cutpoint command
            if (strPlaceHolder.startsWith("Cutpoint=") && strPlaceHolder.length() >= 12 && !isCutpointReceived) 
            {
                int startIndex1 = 9;  // Position after "Cutpoint="
                String cutpointStr = strPlaceHolder.substring(startIndex1, startIndex1 + 3);  // Extract 3 digits
                cutpoint = cutpointStr.toInt();  // Convert to integer
                if (cutpoint > 0) 
                {  // Validate cutpoint value
                    isCutpointReceived = true;  // Mark Cutpoint as received
                    Serial.print("Cutpoint received: ");
                    Serial.println(cutpoint);
                    strPlaceHolder = "";  // Clear the buffer
                } 
            }
            // Process Chipset command
            else if (strPlaceHolder.startsWith("Chipset=") && strPlaceHolder.length() >= 9 && !isChipsetReceived) 
            {
                int startIndex2 = 8;  // Position after "Chipset="
                chipsetStr = strPlaceHolder.substring(startIndex2);
                if (chipsetStr.length() > 0) 
                {  // Validate chipset value
                    isChipsetReceived = true;
                    chipsetInt = chipsetStr.toInt();
                    Serial.print("Chipset received: ");
                    Serial.println(chipsetInt);
                    strPlaceHolder = "";  // Clear the buffer
                    if (chipsetInt == 1)
                    {
                      //WS2811
                      FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, cutpoint);
                    }
                    else if (chipsetInt == 2)
                    {
                      //TX1818
                    }
                    else if (chipsetInt == 3)
                    {
                      //UCS2804
                    }
                    else if (chipsetInt == 4)
                    {
                      //WS2814
                    }
                  } 
              }
            // Process Color Commands (R, G, B, W)
            else if ((strPlaceHolder == "Red" || strPlaceHolder == "Green" || strPlaceHolder == "Blue" || strPlaceHolder == "White") && isCutpointReceived && isChipsetReceived)
            {  // Only process if CP and Chipset are set
                if (strPlaceHolder == "Red") {
                    colorSelect = 0;  // 0 for Red
                    strPlaceHolder = "";  // Clear the buffer
                    Serial.println("R");
                } else if (strPlaceHolder == "Green") { 
                    colorSelect = 1;  // 1 for Green
                    strPlaceHolder = "";  // Clear the buffer
                    Serial.println("G");
                } else if (strPlaceHolder == "Blue") {
                    colorSelect = 2;  // 2 for Blue
                    strPlaceHolder = "";  // Clear the buffer
                    Serial.println("B");
                } else if (strPlaceHolder == "White") {
                    colorSelect = 3;  // 3 for White
                    strPlaceHolder = "";  // Clear the buffer
                    Serial.println("W");
                }
              }
          else if (isCutpointReceived && isChipsetReceived && isNumber(strPlaceHolder))
          {
            Serial.print("Brightness: ");
            Serial.println(strPlaceHolder);
            strPlaceHolder = "";
          }
        }
      }
}

bool isNumber(String str) {
    for (int i = 0; i < str.length(); i++) {
        if (!isDigit(str[i])) {
            return false;  // If any character is not a digit, return false
        }
    }
    return true;  // All characters are digits
}

