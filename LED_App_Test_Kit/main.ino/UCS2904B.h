Adafruit_NeoPixel strip = Adafruit_NeoPixel(0, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially

// Forward declaration of the setAllPixels function
void setAllPixels(int CP, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);

void neoPixel(int CP, char color){
  strip.updateLength(CP);  // Update the length of the strip with the user input
  strip.begin();           // Initialize the strip
  strip.show();            // Turn all LEDs off to start

    // Turn all LEDs red
  if(color == 'R'){
    setAllPixels(CP, 255, 0, 0, 0);  // Red color
    strip.show();                    // Update the strip to show the red color
  }

      // Turn all LEDs green
  if else(color == 'G'){
    setAllPixels(CP, 0, 255, 0, 0);  // green color
    strip.show();                    // Update the strip to show the red color
  }

      // Turn all LEDs blue
  if else(color == 'B'){
    setAllPixels(CP, 0, 0, 255, 0);  // blue color
    strip.show();                    // Update the strip to show the red color
  }

        // Turn all LEDs white
  if else(color == 'W'){
    setAllPixels(CP, 0, 0, 0, 255);  // white color
    strip.show();                    // Update the strip to show the red color
  }
}

// Helper function to set all pixels to a given color
void setAllPixels(int CP, uint8_t red, uint8_t green, uint8_t blue, uint8_t white) {
  //Adafruit_NeoPixel strip = Adafruit_NeoPixel(0, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially
  for (int i = 0; i < CP; i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue, white));
  }
}
