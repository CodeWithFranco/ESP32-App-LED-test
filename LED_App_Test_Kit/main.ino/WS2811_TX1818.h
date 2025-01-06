#include <FastLED.h>

void fastLED(CRGB* leds, int CP, int color, int brightness) {
    if (CP <= 0 || CP > 999) {  // Validate CP
        Serial.println("Invalid CP value!");
        return;
    }

    if (color == 0) {
        for (int i = 0; i < CP; i++) {
            leds[i] = CRGB::Red;
        }
    } else if (color == 1) {
        for (int i = 0; i < CP; i++) {
            leds[i] = CRGB::Green;
        }
    } else if (color == 2) {
        for (int i = 0; i < CP; i++) {
            leds[i] = CRGB::Blue;
        }
    } else if (color == 3) {
        for (int i = 0; i < CP; i++) {
            leds[i] = CRGB::White;
            if (i % 10 == 0) yield(); // Feed the watchdog every 10 LEDs
        }
    }
    FastLED.setBrightness(brightness);
    FastLED.show();
}
