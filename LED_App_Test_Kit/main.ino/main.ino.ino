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
#define PIN 27
#define MAX_CP 999            //Subject to change


CRGB *leds;                   // Allocated array for FASTLEDs - Pointer 

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


BluetoothSerial SerialBT;     // Bluetooth object
String currentColor = ""; //Placeholder for colors - R G B W


void setup() {
  Serial.begin(115200);
  delay(100);                   //Allow some time for initialization
  SerialBT.begin("ESP32_LED");  // Start Bluetooth with the name "ESP32_LED"
  Serial.println("Bluetooth started. Ready to connect.");

  // Wait for Bluetooth client to connect
  while (!SerialBT.hasClient()) {
      delay(100);  // Wait for a client
      Serial.print(".");
  }
  Serial.println("\nBluetooth connected!");


  // Process commands from Bluetooth
  while (!isCutpointReceived || !isChipsetReceived) {
    if (SerialBT.available())
    {
      delay(15);  // Small delay for stable input
      strPlaceHolder = SerialBT.readStringUntil('\n');  // Read one string at a time

      // Debugging
      //Serial.print("Received command: ");
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
              /*Check for MAX cut points*/ 
              if (cutpoint > MAX_CP){
                cutpoint = MAX_CP;
              }
              else if (cutpoint <= 0){
                cutpoint = 1; // Make sure it's at least 1
              }
              leds = new CRGB[cutpoint];      //  Allocate memory for the LED array based on user input
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

              bool valid_answer = false;
              while (!valid_answer)                                 // Loop while answer is incorrect
              {
                switch (chipsetInt)
                {
                  case 1:{ //WS2811
                  FastLED.addLeds<WS2811, PIN, RGB>(leds, cutpoint); //WS2811
                  valid_answer = true; 
                  break;
                  }
                  case 2:{ //TX1818
                  FastLED.addLeds<WS2811, PIN, RGB>(leds, cutpoint); //TX1818
                  valid_answer = true; 
                  break;
                  }
                  case 3:{ //UCS2904B
                  strip.begin();           // Reinitialize the NeoPixel strip
                  valid_answer = true; 
                  break;
                  }
                  case 4:{ //WS2814
                  strip.begin();           // Reinitialize the NeoPixel strip
                  valid_answer = true;  
                  break;
                  }
                  default: // Invalid Choice
                  valid_answer = true; 
                  break;   
                } 
              }
            }     
        }
    } //end of if(SerialBT.available)
  }//end of while(!isCutpointReceived || !isChipsetReceived) 
}//end of void setup()

void loop() 
{
    strPlaceHolder = SerialBT.readStringUntil('\n');  // Read one string at a time
    if (strPlaceHolder.isEmpty()) {
      Serial.println("Empty input, ignoring...");
      return;
    } 

    // Process Color Commands (R, G, B, W)
    if ((strPlaceHolder == "Red" || strPlaceHolder == "Green" || strPlaceHolder == "Blue" || strPlaceHolder == "White") && isCutpointReceived && isChipsetReceived)
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
              case 3: //UCS2904
              {
              //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially
              neoPixel_UCS2904B(cutpoint, colorSelect, intBrightness);
              break;
              }
              case 4: //WS2814
              {
              //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800);
              neoPixel_WS2814(cutpoint, colorSelect, intBrightness);
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
              case 3: //UCS2904
              {
              //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially
              neoPixel_UCS2904B(cutpoint, colorSelect, intBrightness);
              break;
              }
              case 4: //WS2814
              {
              //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800);
              neoPixel_WS2814(cutpoint, colorSelect, intBrightness);
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
              neoPixel_UCS2904B(cutpoint, colorSelect, intBrightness);
              break;
              }
              case 4: //WS2814
              {
              //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800);
              neoPixel_WS2814(cutpoint, colorSelect, intBrightness);
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
              neoPixel_UCS2904B(cutpoint, colorSelect, intBrightness);
              break;
              }
              case 4: //WS2814
              {
              //Adafruit_NeoPixel strip = Adafruit_NeoPixel(cutpoint, PIN, NEO_RGBW + NEO_KHZ800);
              neoPixel_WS2814(cutpoint, colorSelect, intBrightness);
              break;
              }
            }
          }//end of else if (strPlaceHolder == "White")
    } //End of color command

    //brightness level
    else if (isCutpointReceived && isChipsetReceived && isNumber(strPlaceHolder)) 
    {
    int newBrightness = strPlaceHolder.toInt();  // Convert to integer
    newBrightness = constrain(newBrightness, 0, 255); // Constrain brightness

      if (newBrightness != intBrightness) {  // Only update if brightness is different
          intBrightness = newBrightness;
          Serial.print("Updated Brightness: ");
          Serial.println(intBrightness);

          // Apply brightness to the LEDs
          switch (chipsetInt) {
              case 1: case 2:
                  fastLED(leds, cutpoint, colorSelect, intBrightness);
                  break;
              case 3:
                  neoPixel_UCS2904B(cutpoint, colorSelect, intBrightness);
                  break;
              case 4:
                  neoPixel_WS2814(cutpoint, colorSelect, intBrightness);
                  break;
            }
        } else {
            Serial.println("Brightness unchanged.");
                }
        strPlaceHolder = "";  // Clear buffer after processing
    }
}

bool isNumber(String str) {
    for (int i = 0; i < str.length(); i++) {
        if (!isDigit(str[i])) {
            Serial.print("Invalid character in brightness: ");
            Serial.println(str[i]);
            return false;
        }
    }
    return true;
}
