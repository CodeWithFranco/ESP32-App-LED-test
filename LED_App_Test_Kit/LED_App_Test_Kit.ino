#include <BluetoothSerial.h>

BluetoothSerial SerialBT;  // Bluetooth Serial object for ESP32

String command = "";  // Variable to store the received command

void setup() {
    Serial.begin(9600);        // Start Serial Monitor
    SerialBT.begin("ESP32_LED"); // Start Bluetooth with the name "ESP32_LED"
    Serial.println("Bluetooth started. Ready to connect.");
}

void loop() {
    if (SerialBT.available()) {
        char received = SerialBT.read();  // Read one character from Bluetooth
        if (received == '\n') {
            // Print the complete command to the Serial Monitor
            Serial.print("Received command: ");
            Serial.println(command);
            
            // Process specific commands for verification
            if (command == "R") {
                Serial.println("Command: Red LED");
            } else if (command == "G") {
                Serial.println("Command: Green LED");
            } else if (command == "B") {
                Serial.println("Command: Blue LED");
            } else if (command == "W") {
                Serial.println("Command: White LED");
            } else if (command.startsWith("CP=")) {
                int cpValue = command.substring(3).toInt();  // Extract CP value
                Serial.print("Cut Point (CP) value received: ");
                Serial.println(cpValue);
            } else if (command.startsWith("Chipset=")) {
                String chipsetValue = command.substring(8);  // Extract Chipset value
                Serial.print("Chipset received: ");
                Serial.println(chipsetValue);
            }

            // Clear the command string after processing
            command = "";
        } else {
            command += received;  // Append each character to the command string
        }
    }
}
