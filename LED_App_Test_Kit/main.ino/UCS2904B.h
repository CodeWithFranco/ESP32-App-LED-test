#include <Adafruit_NeoPixel.h>
#define PIN 11
 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(0, PIN, NEO_RGBW + NEO_KHZ800);
// Function prototypes
void setAllPixels(int CP, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

void neoPixel(int CP, char color) {
    strip.updateLength(CP);  // Update the length of the strip with the user input
    strip.begin();           // Initialize the strip
    strip.show();            // Turn all LEDs off to start

    if (color == 'R') {
        setAllPixels(CP, 255, 0, 0, 0);  // Red color
    } else if (color == 'G') {
        setAllPixels(CP, 0, 255, 0, 0);  // Green color
    } else if (color == 'B') {
        setAllPixels(CP, 0, 0, 255, 0);  // Blue color
    } else if (color == 'W') {
        setAllPixels(CP, 0, 0, 0, 255);  // White color
    }
    strip.show();
}

void setAllPixels(int CP, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
    for (int i = 0; i < CP; i++) {
        strip.setPixelColor(i, strip.Color(red, green, blue, white));
    }
}
