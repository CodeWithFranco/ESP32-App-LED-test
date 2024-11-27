#include <Adafruit_NeoPixel.h>
#define PIN 11

// Function prototypes
void setAllPixels(int CP, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(0, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially

void neoPixel_1(int CP, char color) {
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

void neoPixel_2(int CP, char color){
   Adafruit_NeoPixel strip = Adafruit_NeoPixel(CP, PIN, NEO_RGBW + NEO_KHZ800);
   strip.begin();
   strip.show();  // Initialize all pixels to 'off'

   if (color == 'W'){
    for (int i = 0; i < CP; i++){
      strip.setPixelColor(i, strip.Color(255, 0, 0, 0));
    }
    strip.show();
   }
   else if (color == 'R'){
      for (int i = 0; i < CP; i++){
      strip.setPixelColor(i, strip.Color(0, 255, 0, 0));
    }
    strip.show();
   }
   else if (color == 'G'){
      for (int i = 0; i < CP; i++){
      strip.setPixelColor(i, strip.Color(0, 0, 255, 0));
    }
    strip.show();
   }
   else if (color == ' B'){
      for (int i = 0; i < CP; i++){
      strip.setPixelColor(i, strip.Color(0, 0, 0, 255));
    }
    strip.show();
   }

}