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

Note#1: LED driver is the chip that controls the LEDs   *   
on tapelight. In this code, the name changed into       *
chipset as the company uses 'driver' as the name for    *
power supply
********************************************************/

#include <BluetoothSerial.h>
#include "WS2811_TX1818.h"
#include "UCS2904B.h"
#define DATA_PIN 11

CRGB *leds;                   // Allocated array for FASTLEDs - Pointer 

BluetoothSerial SerialBT;     //Bluetooth object
bool isBTStarted = false;     //Track BT state

String strPlaceHolder = "";  // Placeholder for incoming characters
int cutpoint = 0;            // Integer to store cutpoint value
int colorSelect = -1;        // Initialize as -1(no color selected)        
String chipsetStr = "";      // String to store chipset value
bool isCutpointReceived = false;  // Flag to track Cutpoint reception
bool isChipsetReceived = false;   // Flag to track Chipset reception
bool isColorSelected = false; //Flag to track color selection


void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_LED");  // Start Bluetooth with the name "ESP32_LED"
    Serial.println("Bluetooth started. Ready to connect.");
}

void loop() {
  if (SerialBT.hasClient()) {
    if (!isBTStarted) {
      // Reconnection event
      Serial.println("Bluetooth Reconnected. Clearing buffers and resetting state...");
      while (SerialBT.available()) SerialBT.read(); // Clear Bluetooth input buffer
      isCutpointReceived = false;  // Reset flags
      isChipsetReceived = false;
      strPlaceHolder = "";         // Clear placeholder
      isBTStarted = true;
    }

    if (SerialBT.available()) {
      char receivedChar = SerialBT.read();  // Read one character
      strPlaceHolder += receivedChar;       // Append the character to the buffer

      // Debugging: Print the current buffer
      //Serial.println("Buffer: " + strPlaceHolder);

      // Process Cutpoint command
      if (strPlaceHolder.startsWith("Cutpoint=") && strPlaceHolder.length() >= 12 && !isCutpointReceived) {
        int startIndex1 = 9;  // Position after "Cutpoint="
        String cutpointStr = strPlaceHolder.substring(startIndex1, startIndex1 + 3);  // Extract 3 digits
        cutpoint = cutpointStr.toInt();  // Convert to integer
        if (cutpoint > 0) {  // Validate cutpoint value
          isCutpointReceived = true;  // Mark Cutpoint as received
          Serial.print("Cutpoint received: ");
          Serial.println(cutpoint);
          strPlaceHolder = "";  // Clear the buffer
        } 
      }
      // Process Chipset command
      else if (strPlaceHolder.startsWith("Chipset=") && strPlaceHolder.length() >= 9 && !isChipsetReceived) {
        int startIndex2 = 8;  // Position after "Chipset="
        chipsetStr = strPlaceHolder.substring(startIndex2);
        if (chipsetStr.length() > 0) {  // Validate chipset value
          isChipsetReceived = true;
          Serial.print("Chipset received: ");
          Serial.println(chipsetStr);
          strPlaceHolder = "";  // Clear the buffer
        } 
      }
      // Process Color Commands (R, G, B, W)
      else if (isChipsetReceived && isCutpointReceived) {  // Only process if CP and Chipset are set
        if (strPlaceHolder == "R") {
          isColorSelected = false;                        //Makes the boolean false if user selected a color previously
          colorSelect = -1;                               //Makes sure the location is "No color" for previous allocation
          Serial.println(strPlaceHolder);
          colorSelect = 0;                                 //Another location for a color (0 = RED)
          isColorSelected = true;                         //True if user selects a color
          //Serial.println("Red Command Received");
          strPlaceHolder = "";  // Clear the buffer
        } else if (strPlaceHolder == "G") {
          isColorSelected = false;                        //Makes the boolean false if user selected a color previously
          colorSelect = -1;                               //Makes sure the location is "No color" for previous allocation
          Serial.println(strPlaceHolder);
          colorSelect = 1;                                //Another location for a color (1 = GREEN)
          isColorSelected = true;                         //True if user selects a color
          //Serial.println("Green Command Received");
          strPlaceHolder = "";  // Clear the buffer
        } else if (strPlaceHolder == "B") {
          isColorSelected = false;                        //Makes the boolean false if user selected a color previously
          colorSelect = -1;                               //Makes sure the location is "No color" for previous allocation
          Serial.println(strPlaceHolder);
          colorSelect = 2;                                //Another location for a color (2 = Blue)
          isColorSelected = true;                         //True if user selects a color
          //Serial.println("Blue Command Received");
          strPlaceHolder = "";  // Clear the buffer
        } else if (strPlaceHolder == "W") {
          isColorSelected = false;                        //Makes the boolean false if user selected a color previously
          colorSelect = -1;                               //Makes sure the location is "No color" for previous allocation
          Serial.println(strPlaceHolder);
          colorSelect = 3;                                //Another location for a color (3 = White)
          isColorSelected = true;                         //True if user selects a color
          //Serial.println("White Command Received");
          strPlaceHolder = "";  // Clear the buffer
        }
      }
      //Process Dimming Command
      else if  (isChipsetReceived && isCutpointReceived && isColorSelected){
          if (strPlaceHolder.length() > 1 && strPlaceHolder.length() < 4) {  // Process dimming command (e.g., R255 or G1)
            //char color = strPlaceHolder.charAt(0);  // Extract color ('R', 'G', 'B', 'W')
            int brightness = strPlaceHolder.substring(1).toInt();  // Extract brightness value
            brightness = constrain(brightness, 0, 255);  // Ensure brightness is within range

          switch (colorSelect) {
              case 'R':
                  Serial.println("Dimming Red: " + String(brightness));
                  // Add LED code for Red brightness adjustment here
                  break;
              case 'G':
                  Serial.println("Dimming Green: " + String(brightness));
                  // Add LED code for Green brightness adjustment here
                  break;
              case 'B':
                  Serial.println("Dimming Blue: " + String(brightness));
                  // Add LED code for Blue brightness adjustment here
                  break;
              case 'W':
                  Serial.println("Dimming White: " + String(brightness));
                  // Add LED code for White brightness adjustment here
                  break;
              default:
                  Serial.println("ERROR: Invalid Dimming Command");
                  break;
          }
        }
      }
    
    }
  }   
    else {
    if (isBTStarted) {
      // Handle Bluetooth disconnection
      Serial.println("Bluetooth Disconnected. Waiting to connect...");
      isBTStarted = false;

      // Reset all flags and clear buffer
      isCutpointReceived = false;
      isChipsetReceived = false;
      isColorSelected = false;
      colorSelect = -1;
      strPlaceHolder = "";
      
    }
    delay(3000);
    Serial.println("Restarting Bluetooth...");
    SerialBT.begin("ESP32_LED");  // Restart Bluetooth
    isBTStarted = true;
  }
}

