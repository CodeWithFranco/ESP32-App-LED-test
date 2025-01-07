#include <Adafruit_NeoPixel.h>
#define PIN 11

// Function prototypes
// Forward declaration of the setAllPixels function
void setAllPixels(int CP, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(0, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially

void neoPixel_UCS2904B(int CP, int color, int brightness) {
    strip.begin();
    strip.updateLength(CP);  // Update the length of the strip with the user input

    if (color == 0) {
       setAllPixels(CP, brightness, 0, 0, 0);  // Red color 
    } else if (color == 1) {
        setAllPixels(CP, 0, brightness, 0, 0);  // Green color 
    } else if (color == 2) {
        setAllPixels(CP, 0, 0, brightness, 0);  // Blue
    } else if (color == 3) {
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

void neoPixel_WS2814(int CP, int color, int brightness){
  if (color == 3) //White
  {
    for (int i = 0; i < CP; i++) 
    {
    strip.setPixelColor(i, strip.Color(brightness, 0, 0, 0));  
    if (i % 10 == 0) yield();
    }
  }

  else if(color == 0)//Red
  {
    for (int i = 0; i < CP; i++) 
    {
    strip.setPixelColor(i, strip.Color(0, brightness, 0, 0));  
    if (i % 10 == 0) yield();
    }
  }

  else if(color == 1)//Green
  {
    for (int i = 0; i < CP; i++) 
    {
    strip.setPixelColor(i, strip.Color(0, 0, brightness, 0));  
    if (i % 10 == 0) yield();
    }
  }

  else if(color == 2)//Blue
  {
    for (int i = 0; i < CP; i++) 
    {
    strip.setPixelColor(i, strip.Color(0, 0, 0, brightness));  
    if (i % 10 == 0) yield();
    }
  }
  strip.show();
  yield();  // Feed the watchdog after completing the update
}
