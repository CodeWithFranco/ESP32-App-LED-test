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

CRGB *leds;                   // Allocated array for FASTLEDs - Pointer 

BluetoothSerial SerialBT;     // Bluetooth object
bool isBTStarted = false;     // Track BT state

String strPlaceHolder = "";  // Placeholder for incoming characters
int cutpoint = 0;            // Integer to store cutpoint value
int colorSelect = -1;        // Initialize as -1 (no color selected)        
String chipsetStr = "";      // String to store chipset value
bool isCutpointReceived = false;  // Flag to track Cutpoint reception
bool isChipsetReceived = false;   // Flag to track Chipset reception
bool isColorSelected = false;     // Flag to track color selection

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
            else if (isChipsetReceived && isCutpointReceived && !isColorSelected) {  // Only process if CP and Chipset are set
                if (strPlaceHolder == "R") {
                    colorSelect = 0;  // 0 for Red
                    isColorSelected = true;  // Mark color as selected
                    strPlaceHolder = "";  // Clear the buffer
                    Serial.println("R");
                } else if (strPlaceHolder == "G") { 
                    colorSelect = 1;  // 1 for Green
                    isColorSelected = true;  // Mark color as selected
                    strPlaceHolder = "";  // Clear the buffer
                    Serial.println("G");
                } else if (strPlaceHolder == "B") {
                    colorSelect = 2;  // 2 for Blue
                    isColorSelected = true;  // Mark color as selected
                    strPlaceHolder = "";  // Clear the buffer
                    Serial.println("B");
                } else if (strPlaceHolder == "W") {
                    colorSelect = 3;  // 3 for White
                    isColorSelected = true;  // Mark color as selected
                    strPlaceHolder = "";  // Clear the buffer
                    Serial.println("W");
                }
            }
            // Process Dimming Command
            else if (isChipsetReceived && isCutpointReceived && isColorSelected) {
                if (strPlaceHolder.length() > 1 && strPlaceHolder.length() < 5) {  // Process dimming command
                    // Debugging: Print the raw received command
                    Serial.print("Raw Command: ");
                    Serial.println(strPlaceHolder);

                    // Extract brightness value from the second character onwards
                    String brightnessStr = strPlaceHolder.substring(1);  // Extract numeric part
                    if (brightnessStr.length() > 0 && brightnessStr.toInt() >= 0) {  // Validate numeric input
                        int brightness = brightnessStr.toInt();  // Convert to integer
                        brightness = constrain(brightness, 0, 255);  // Constrain brightness

                        // Handle dimming based on selected color
                        switch (colorSelect) {
                            case 0:  // Red
                                Serial.println("Dimming Red: " + String(brightness));
                                break;
                            case 1:  // Green
                                Serial.println("Dimming Green: " + String(brightness));
                                break;
                            case 2:  // Blue
                                Serial.println("Dimming Blue: " + String(brightness));
                                break;
                            case 3:  // White
                                Serial.println("Dimming White: " + String(brightness));
                                break;
                            default:
                                Serial.println("ERROR: Invalid Dimming Command");
                                break;
                        }
                    } else {
                        Serial.println("ERROR: Invalid Brightness Value");
                    }

                    // Reset only the buffer, keep the color selected
                    strPlaceHolder = "";  // Clear buffer after processing
                }
            }
        }
    } else {
        if (isBTStarted) {
            Serial.println("Bluetooth Disconnected. Waiting to connect...");
            isBTStarted = false;
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

