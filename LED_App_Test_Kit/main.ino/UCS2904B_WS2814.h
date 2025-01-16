#include <Adafruit_NeoPixel.h>
#define PIN 27

// Function prototypes
// Forward declaration of the setAllPixels function
void setAllPixels(int CP, uint8_t red, uint8_t green, uint8_t blue, uint8_t white);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(0, PIN, NEO_RGBW + NEO_KHZ800); // Initialize with 0 LEDs initially

void neoPixel_UCS2904B(int CP, int color, int brightness) {
    static int previousCP = -1;
    if (CP <= 0 || CP > 300) {  // Validate CP
        Serial.println("Invalid CP value!");
        return;
    }

    if (CP != previousCP) {
        strip.updateLength(CP);
        strip.begin();
        previousCP = CP;
    }

    uint8_t red = 0, green = 0, blue = 0, white = 0;

    if (color == 0) red = brightness;
    else if (color == 1) green = brightness;
    else if (color == 2) blue = brightness;
    else if (color == 3) white = brightness;

    for (int i = 0; i < CP; i++) {
        strip.setPixelColor(i, strip.Color(red, green, blue, white));
        if (i % 10 == 0) yield();  // Feed the watchdog
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
