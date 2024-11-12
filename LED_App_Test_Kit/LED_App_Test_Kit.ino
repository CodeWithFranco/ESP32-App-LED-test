#include "blinkAllColorFast.h"
#include "blinkAllColorNeo.h"
#include "dimmingFast.h"
#include "dimmingNeo.h"
#include <SoftwareSerial.h>  // Include SoftwareSerial library for HC-05/HC-06

SoftwareSerial BTSerial(10, 11); // RX, TX pins for Bluetooth module

String command = "";
int brightness = 255;
String chipset = "";

void setup() {
    Serial.begin(9600);          // Start serial monitor (optional)
    BTSerial.begin(9600);        // Start Bluetooth communication at 9600 baud rate
    Serial.println("Bluetooth Ready. Waiting for commands...");
    initializeLEDs();            // Initialize LEDs
}

void loop() {
    if (BTSerial.available()) {             // Check if there's data from Bluetooth
        char received = BTSerial.read();    // Read a single character
        if (received == '\n') {
            processCommand(command);        // Process the complete command
            command = "";                   // Reset the command
        } else {
            command += received;            // Append character to the command string
        }
    }
}

// The rest of the code remains the same...
