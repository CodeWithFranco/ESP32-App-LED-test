#include <FastLED.h>

void fastLED(CRGB* leds, int CP, int color, int brightness) {
    if (leds == nullptr) {
        Serial.println("Error: LEDs not initialized!");
        return;
    }
    if (CP <= 0 || CP > 300) {  // Validate CP
        Serial.println("Invalid CP value!");
        return;
    }

    FastLED.clear();
    for (int i = 0; i < CP; i++) {
        if (color == 0) leds[i] = CRGB(brightness, 0, 0);      // Red
        else if (color == 1) leds[i] = CRGB(0, brightness, 0); // Green
        else if (color == 2) leds[i] = CRGB(0, 0, brightness); // Blue
        else if (color == 3) leds[i] = CRGB::White;            // White
        if (i % 10 == 0) yield();  // Feed the watchdog
    }
    FastLED.setBrightness(brightness);
    FastLED.show();
}
