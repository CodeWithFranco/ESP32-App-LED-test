#include <Adafruit_NeoPixel.h>
#define PIN 11

// Function prototypes
void setAllPixels(int CP, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(0, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially

void neoPixel_1(int CP, char color) {
    if (CP <= 0 || CP > 999) {  // Validate CP
        Serial.println("Invalid CP value!");
        return;
    }
    strip.updateLength(CP);  // Update the length of the strip
    strip.begin();
    strip.show();  // Turn all LEDs off initially

    if (color == 'R') {
        setAllPixels(CP, 255, 0, 0, 0);  // Red
    } else if (color == 'G') {
        setAllPixels(CP, 0, 255, 0, 0);  // Green
    } else if (color == 'B') {
        setAllPixels(CP, 0, 0, 255, 0);  // Blue
    } else if (color == 'W') {
        setAllPixels(CP, 0, 0, 0, 255);  // White
    }
    strip.show();
    yield();  // Feed the watchdog
}


