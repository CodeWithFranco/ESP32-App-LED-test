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
String chipsetStr = "";      // String to store chipset value
bool isCutpointReceived = false;  // Flag to track Cutpoint reception
bool isChipsetReceived = false;   // Flag to track Chipset reception

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_LED");  // Start Bluetooth with the name "ESP32_LED"
    isBTStarted = true;
    Serial.println("Bluetooth started. Ready to connect.");
}

void loop() {
  if (SerialBT.hasClient()){
      if (SerialBT.available()) {
          char receivedChar = SerialBT.read();  // Read one character
          //Serial.println("Initial char received:");
          //Serial.println(receivedChar);
          strPlaceHolder += receivedChar;       // Append the character to the buffer

          // Process Cutpoint command
          if (strPlaceHolder.startsWith("Cutpoint=") && strPlaceHolder.length() >= 12 && isCutpointReceived == false) {
              int startIndex1 = 9;  // Position after "Cutpoint="
              String cutpointStr = strPlaceHolder.substring(startIndex1, startIndex1 + 3);  // Extract 3 digits
              cutpoint = cutpointStr.toInt();  // Convert to integer
              isCutpointReceived = true;  // Mark Cutpoint as received
              Serial.print("Cutpoint received: ");
              Serial.println(cutpoint);
              strPlaceHolder = "";  // Clear the buffer
            }
          // Process Chipset command
          else if (strPlaceHolder.startsWith("Chipset=") && strPlaceHolder.length() >= 9 && isChipsetReceived == false) {
              int startIndex2 = 8;  // Position after "Chipset="
              chipsetStr = strPlaceHolder.substring(startIndex2);
              isChipsetReceived = true;
              Serial.print("Chipset received: ");
              Serial.println(chipsetStr);
              strPlaceHolder = "";  // Clear the buffer
            }
              // Process Color Commands (R, G, B, W)
          else if (isChipsetReceived && isCutpointReceived) {  // Only process if CP and Chipset are set
              if (strPlaceHolder == "R") {
                Serial.println(strPlaceHolder);
                Serial.println("Red Command Received");
                strPlaceHolder = "";
              } else if (strPlaceHolder == "G") {
                Serial.println(strPlaceHolder);
                Serial.println("Green Command Received");
                strPlaceHolder = "";
              } else if (strPlaceHolder == "B") {
                Serial.println(strPlaceHolder);
                Serial.println("Blue Command Received");
                strPlaceHolder = "";
              } else if (strPlaceHolder == "W") {
                Serial.println(strPlaceHolder);
                Serial.println("White Command Received");
                strPlaceHolder = "";
              } else {
                Serial.println("ERROR: Invalid Color Command");
              }
          }
          else {
            Serial.println("Error: CP and Chipset not received yet");
          }
        }
    }
        else {
          if(isBTStarted){
            Serial.println("Bluetooth Disconected");
            isBTStarted = false;
          }

          delay(5000);
          Serial.println("Restarting Bluetooth");
          SerialBT.begin("ESP32_LED"); // Restart Bluetooth
          isBTStarted = true;
        } 
}
        


