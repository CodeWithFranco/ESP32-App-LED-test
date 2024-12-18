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

        // Process Cutpoint command
        if (strPlaceHolder.startsWith("Cutpoint=") && strPlaceHolder.length() >= 12 && isCutpointReceived == false) {
            int startIndex1 = 9;  // Position after "Cutpoint="
            String cutpointStr = strPlaceHolder.substring(startIndex1, startIndex1 + 3);  // Extract 3 digits
            cutpoint = cutpointStr.toInt();  // Convert to integer
            isCutpointReceived = true;  // Mark Cutpoint as received
            //Serial.print("Cutpoint received: ");
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
        //RGBW Command - if Chipset & Cutpoint = false
        else if (isChipsetReceived == false && isCutpointReceived == false && strPlaceHolder == "R" || strPlaceHolder == "G" || strPlaceHolder == "B" || strPlaceHolder =="W" ){
          Serial.println("Error CP and Chipset NOT received");
        }
        //RGBW Command - if Chipset = true & CP = false
        else if (isChipsetReceived == true && isCutpointReceived == false && strPlaceHolder == "R" || strPlaceHolder == "G" || strPlaceHolder == "B" || strPlaceHolder =="W" ){
          Serial.println("Error CP NOT received");
        }
        //RGBW Command - if Chipset = false & CP = true
        else if (isChipsetReceived == false && isCutpointReceived == true && strPlaceHolder == "R" || strPlaceHolder == "G" || strPlaceHolder == "B" || strPlaceHolder =="W" ){
          Serial.println("Error chipset NOT received");
        }
        //RGBW Command - if Chipset = true & CP = truex
        else if (isChipsetReceived == true && isCutpointReceived == true && strPlaceHolder == "R"){
          Serial.println(strPlaceHolder);
          strPlaceHolder = "";
        }
        //RGBW Command - if Chipset = true & CP = true
        else if (isChipsetReceived == true && isCutpointReceived == true && strPlaceHolder == "G"){
          Serial.println(strPlaceHolder);
          strPlaceHolder = "";
        }
        //RGBW Command - if Chipset = true & CP = true
        else if (isChipsetReceived == true && isCutpointReceived == true && strPlaceHolder == "B"){
          Serial.println(strPlaceHolder);
          strPlaceHolder = "";
        }
        //RGBW Command - if Chipset = true & CP = true
        else if (isChipsetReceived == true && isCutpointReceived == true && strPlaceHolder == "W"){
          Serial.println(strPlaceHolder);
          strPlaceHolder = "";
        }
      } 
}
        


