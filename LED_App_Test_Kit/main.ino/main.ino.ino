#include <BluetoothSerial.h>

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
        strPlaceHolder += receivedChar;       // Append the character to the buffer

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
        else if (strPlaceHolder.startsWith("Chipset=") && strPlaceHolder.length() >= 14) {
            int startIndex = 8;  // Position after "Chipset="
            chipsetStr = strPlaceHolder.substring(startIndex, strPlaceHolder.length());  // Extract remaining string
            isChipsetReceived = true;  // Mark Chipset as received
            Serial.print("Chipset received: ");
            Serial.println(chipsetStr);
            strPlaceHolder = "";  // Clear the buffer
        }
        // Process Color Commands (Only if CP and Chipset are received)
        else if (isCutpointReceived && isChipsetReceived) {
            if (receivedChar == 'R') {
                Serial.println("Color: Red");
            } else if (receivedChar == 'G') {
                Serial.println("Color: Green");
            } else if (receivedChar == 'B') {
                Serial.println("Color: Blue");
            } else if (receivedChar == 'W') {
                Serial.println("Color: White");
            }
        }
        // Reject Color Commands if CP or Chipset is missing
        else if (receivedChar == 'R' || receivedChar == 'G' || receivedChar == 'B' || receivedChar == 'W') {
            Serial.println("Error: Send Cutpoint and Chipset values first!");
        }
    }
}

        

