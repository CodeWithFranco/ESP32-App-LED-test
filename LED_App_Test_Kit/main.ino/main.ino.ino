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
#include <FastLED.h>
#include "WS2811_TX1818.h"
#include "UCS2904B_WS2814.h"
#define DATA_PIN 11

String strPlaceHolder = "";  // Placeholder for incoming characters
String chipsetStr = "";      // String to store chipset value

int cutpoint = 0;            // Integer to store cutpoint value
int colorSelect = -1;        // Initialize as -1 (no color selected)     
int chipsetInt = 0;
int intBrightness = 1;       // initial brightness
 
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
            //Serial.print("Value: ");
            //Serial.println(strPlaceHolder);

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
                      FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, cutpoint);
                    }
                    else if (chipsetInt == 3)
                    {
                      //UCS2804
                      Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, DATA_PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially
                    }
                    else if (chipsetInt == 4)
                    {
                      //WS2814
                      Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, DATA_PIN, NEO_RGBW + NEO_KHZ800);
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
                    switch(chipsetInt)
                    {
                      case 1: //WS2811
                      {
                      fastLED(leds, cutpoint, colorSelect, intBrightness);
                      break;
                      }
                      case 2: //TX1818
                      {
                      fastLED(leds, cutpoint, colorSelect, intBrightness);
                      break;
                      }
                      case 3: //UCS2804
                      {
                      //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially
                      break;
                      }
                      case 4: //WS2814
                      {
                      //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800);
                      break;
                      }
                    }
                  } else if (strPlaceHolder == "Green") { 
                    colorSelect = 1;  // 1 for Green
                    strPlaceHolder = "";  // Clear the buffer
                    Serial.println("G");
                    switch(chipsetInt)
                    {
                      case 1: //WS2811
                      {
                      fastLED(leds, cutpoint, colorSelect, intBrightness);
                      break;
                      }
                      case 2: //TX1818
                      {
                      fastLED(leds, cutpoint, colorSelect, intBrightness);
                      break;
                      }
                      case 3: //UCS2804
                      {
                      //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially
                      break;
                      }
                      case 4: //WS2814
                      {
                      //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800);
                      break;
                      }
                    }
                } else if (strPlaceHolder == "Blue") {
                    colorSelect = 2;  // 2 for Blue
                    strPlaceHolder = "";  // Clear the buffer
                    Serial.println("B");
                    switch(chipsetInt)
                    {
                      case 1: //WS2811
                      {
                      fastLED(leds, cutpoint, colorSelect, intBrightness);
                      break;
                      }
                      case 2: //TX1818
                      {
                      fastLED(leds, cutpoint, colorSelect, intBrightness);
                      break;
                      }
                      case 3: //UCS2804
                      {
                      //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially
                      break;
                      }
                      case 4: //WS2814
                      {
                      //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800);
                      break;
                      }
                    }
                } else if (strPlaceHolder == "White") {
                    colorSelect = 3;  // 3 for White
                    strPlaceHolder = "";  // Clear the buffer
                    Serial.println("W");
                    switch(chipsetInt)
                    {
                      case 1: //WS2811
                      {
                      fastLED(leds, cutpoint, colorSelect, intBrightness);
                      break;
                      }
                      case 2: //TX1818
                      {
                      fastLED(leds, cutpoint, colorSelect, intBrightness);
                      break;
                      }
                      case 3: //UCS2804
                      {
                      //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially
                      break;
                      }
                      case 4: //WS2814
                      {
                      //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800);
                      break;
                      }
                    }
                }
            } //End of color command
          else if (isCutpointReceived && isChipsetReceived && isNumber(strPlaceHolder))
          {
            String strBrightness = strPlaceHolder; 
            intBrightness = strBrightness.toInt();  // Convert to integer
            intBrightness = constrain(intBrightness, 0, 255); //Constrain brightness
            Serial.print("Brightness: ");
            Serial.println(intBrightness);
            strPlaceHolder = "";

            switch(chipsetInt)
            {
              case 1: //WS2811
              {
              fastLED(leds, cutpoint, colorSelect, intBrightness);
              break;
              }
              case 2: //TX1818
              {
              fastLED(leds, cutpoint, colorSelect, intBrightness);
              break;
              }
              case 3: //UCS2804
              {
              //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially
              break;
              }
              case 4: //WS2814
              {
              //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800);
              break;
              }
            }
          }
        }// end of if/else SerialBT.available
      }// end of if SerialBT.hasclient
}

bool isNumber(String str) {
    for (int i = 0; i < str.length(); i++) {
        if (!isDigit(str[i])) {
            return false;  // If any character is not a digit, return false
        }
    }
    return true;  // All characters are digits
}

