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

BluetoothSerial SerialBT;
String strPlaceHolder = "";  // Placeholder for incoming characters
int cutpoint = 0;            // Integer to store cutpoint value
String chipsetStr = "";      // String to store chipset value
bool isCutpointReceived = false;  // Flag to track Cutpoint reception
bool isChipsetReceived = false;   // Flag to track Chipset reception

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_LED");  // Start Bluetooth with the name "ESP32_LED"
    Serial.println("Bluetooth started. Ready to connect.");
}

void loop() {
    if (SerialBT.available()) {
        char receivedChar = SerialBT.read();  // Read one character
        //Serial.println("Initial char received:");
        //Serial.println(receivedChar);
        strPlaceHolder += receivedChar;       // Append the character to the buffer

       if (isCutpointReceived == false &&  isChipsetReceived == false){
          // Process Cutpoint command
          if (strPlaceHolder.startsWith("Cutpoint=") && strPlaceHolder.length() >= 12) {
              int startIndex = 9;  // Position after "Cutpoint="
              String cutpointStr = strPlaceHolder.substring(startIndex, startIndex + 3);  // Extract 3 digits
              cutpoint = cutpointStr.toInt();  // Convert to integer
              isCutpointReceived = true;  // Mark Cutpoint as received
              Serial.print("Cutpoint received: ");
              Serial.println(cutpoint);
              strPlaceHolder = "";  // Clear the buffer
          }
          // Process Chipset command
          else if (strPlaceHolder.startsWith("Chipset=") && strPlaceHolder.length() >= 9) {
              int startIndex = 8;  // Position after "Chipset="
              chipsetStr = strPlaceHolder.substring(startIndex);
              isChipsetReceived = true;
              Serial.print("Chipset received: ");
              Serial.println(chipsetStr);
              strPlaceHolder = "";  // Clear the buffer
            }
        // Cutpoint is NOT receive and Chipset is received
        else if (isCutpointReceived == false &&  isChipsetReceived == true){
            Serial.print("Enter Cutpoint Value");
            // Reject Color Commands if CP or Chipset is missing
            if (receivedChar == 'R' || receivedChar == 'G' || receivedChar == 'B' || receivedChar == 'W') {
              Serial.println("Error: Send Cutpoint and Chipset values first!");
            } 
        }
        //Cutpoint is received and Chipset is NOT received
        else if (isCutpointReceived == true &&  isChipsetReceived == false){
            Serial.print("Enter Chipset Value");
            // Reject Color Commands if CP or Chipset is missing
            if (receivedChar == 'R' || receivedChar == 'G' || receivedChar == 'B' || receivedChar == 'W') {
              Serial.println("Error: Send Cutpoint and Chipset values first!");
            }
        }
        //Cutpoint and Chipset are received
        else{
          Serial.println("Chipset: ");
          Serial.println(chipsetStr);
          Serial.println("Cutpoint: ");
          Serial.println(cutpoint);
          if (chipsetStr == "WS2811" || chipsetStr == "TX1818"){
            FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, cutpoint);
            if (receivedChar == 'R' || receivedChar == 'G' || receivedChar == 'B' || receivedChar == 'W') {
                fastLED(leds, cutpoint, receivedChar);
            }
          }
          else if (chipsetStr == "UCS2904B"){
            if (receivedChar == 'R' || receivedChar == 'G' || receivedChar == 'B' || receivedChar == 'W') {
                neoPixel_1(cutpoint, receivedChar);
            }
          }
          else if (chipsetStr == "WS2814"){
            if (receivedChar == 'R' || receivedChar == 'G' || receivedChar == 'B' || receivedChar == 'W') {
                neoPixel_2(cutpoint, receivedChar);
          }
        }
      }
    }
  }
}

        


