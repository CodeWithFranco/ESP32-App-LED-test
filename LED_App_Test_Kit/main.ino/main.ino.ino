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

        // Check if we have a full "Cutpoint=" command
        if (strPlaceHolder.startsWith("Cutpoint=") && strPlaceHolder.length() > 9) {
            // Extract the cutpoint value after "Cutpoint="
            String cutpointStr = strPlaceHolder.substring(9);  // Get substring after "Cutpoint="
            cutpoint = cutpointStr.toInt();  // Convert cutpoint to integer

            Serial.print("Cutpoint value extracted: ");
            Serial.println(cutpoint);

            // Clear the placeholder for the next command
            strPlaceHolder = "";
        }
        // Check if we have a full "Chipset=" command
        else if (strPlaceHolder.startsWith("Chipset=") && strPlaceHolder.length() > 8) {
            // Extract the chipset value after "Chipset="
            chipset = strPlaceHolder.substring(8);  // Get substring after "Chipset="

            Serial.print("Chipset extracted: ");
            Serial.println(chipset);

            // Clear the placeholder for the next command
            strPlaceHolder = "";
        }
    }
}

