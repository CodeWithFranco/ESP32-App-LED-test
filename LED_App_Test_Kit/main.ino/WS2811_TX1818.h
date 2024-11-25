#include <FastLED.h>


void fastLED(CRGB* leds, int CP, char color) {
    if (color == 'R') {
        // Turn all LEDs to red
        for (int i = 0; i < CP; i++) {
            leds[i] = CRGB::Red;
        }
    } else if (color == 'G') {
        // Turn all LEDs to green
        for (int i = 0; i < CP; i++) {
            leds[i] = CRGB::Green;
        }
    } else if (color == 'B') {
        // Turn all LEDs to blue
        for (int i = 0; i < CP; i++) {
            leds[i] = CRGB::Blue;
        }
    } else if (color == 'W') {
        // Turn all LEDs to white
        for (int i = 0; i < CP; i++) {
            leds[i] = CRGB::White;
        }
    }
    FastLED.show();
}
