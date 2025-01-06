#include <Adafruit_NeoPixel.h>
#define PIN 11

// Function prototypes
void setAllPixels(int CP, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(0, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially

void neoPixel(int CP, char color, int brightness) {
    strip.begin();

    if (color == 'R') {
        setAllPixels(CP, brightness, 0, 0, 0);  // Red
    } else if (color == 'G') {
        setAllPixels(CP, 0, brightness, 0, 0);  // Green
    } else if (color == 'B') {
        setAllPixels(CP, 0, 0, brightness, 0);  // Blue
    } else if (color == 'W') {
        setAllPixels(CP, 0, 0, 0, brightness);  // White
    }
    strip.show();
    yield();  // Feed the watchdog
}

// Helper function to set all pixels to a given color
void setAllPixels(int CP, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
  //Adafruit_NeoPixel strip = Adafruit_NeoPixel(0, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially
  for (int i = 0; i < CP; i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue, white));
  }
}
