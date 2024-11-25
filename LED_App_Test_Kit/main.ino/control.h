void Control(int CP, String CS, char receivedChar) {
    // Process Color Commands (Only if CP and Chipset are received)
    if (receivedChar == 'R') {
        Serial.println("Color: Red");
    } else if (receivedChar == 'G') {
        Serial.println("Color: Green");
    } else if (receivedChar == 'B') {
        Serial.println("Color: Blue");
    } else if (receivedChar == 'W') {
        Serial.println("Color: White");
    } else {
        Serial.println("Invalid color command received.");
    }
}
