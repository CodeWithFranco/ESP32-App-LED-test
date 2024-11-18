#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
String strPlaceHolder = "";  // Placeholder for incoming characters
int cutpoint = 0;            // Integer to store cutpoint value
String chipset = "";         // String to store chipset value

void setup() {
    Serial.begin(115200);
    SerialBT.begin("ESP32_LED");  // Start Bluetooth with the name "ESP32_LED"
    Serial.println("Bluetooth started. Ready to connect.");

    // Initialize variables
    strPlaceHolder = "";  // Empty string
}

void loop() {
    if (SerialBT.available()) {
        char receivedChar = SerialBT.read();  // Read one character
        strPlaceHolder += receivedChar;       // Append the character to the buffer

        // Debugging: Print the current buffer
        //Serial.print("Current buffer: ");
        //Serial.println(strPlaceHolder);
        

        if (strPlaceHolder.startsWith("Cutpoint=")){
          int startIndex = 9; //Cutpoint= is 9 characters
          String cutpointStr = strPlaceHolder.substring(startIndex, startIndex + 3);

          //Convert to integer
          Serial.println("cutpointStr: ");
          Serial.println(cutpointStr);
          cutpoint = cutpointStr.toInt();

          if (strPlaceHolder.substring(startIndex = 3)){
            // Debugging: Print the extracted cutpoint value
            Serial.print("Cutpoint value extracted: ");
            Serial.println(cutpoint);
          }

        }
    }
}
