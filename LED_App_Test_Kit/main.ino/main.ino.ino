#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
String strPlaceHolder = "";  // Placeholder for incoming characters
int cutpoint = 0;            // Integer to store cutpoint value
String chipset = "";         // String to store chipset value

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_LED");  // Start Bluetooth with the name "ESP32_LED"
    Serial.println("Bluetooth started. Ready to connect.");
}

void loop() {
    if (SerialBT.available()) {
        char receivedChar = SerialBT.read();  // Read one character

        // Append received character to the placeholder string
        strPlaceHolder += receivedChar;

        // Check if we received the full command (this example assumes no newline is sent, so we process after receiving both keywords)
        if (strPlaceHolder.startsWith("Cutpoint=") && strPlaceHolder.indexOf("Chipset=") != -1) {
            // Extract Cutpoint value
            int cutpointStart = 9;  // Position right after "Cutpoint="
            int chipsetStart = strPlaceHolder.indexOf("Chipset=");  // Find the start of "Chipset="

            String cutpointStr = strPlaceHolder.substring(cutpointStart, chipsetStart);
            cutpoint = cutpointStr.toInt();  // Convert Cutpoint to integer

            // Extract Chipset value
            chipset = strPlaceHolder.substring(chipsetStart + 8);  // Extract everything after "Chipset="

            // Print extracted values for debugging
            Serial.print("Cutpoint value extracted: ");
            Serial.println(cutpoint);
            Serial.print("Chipset extracted: ");
            Serial.println(chipset);

            // Clear the placeholder for the next command
            strPlaceHolder = "";
        }
    }
}

