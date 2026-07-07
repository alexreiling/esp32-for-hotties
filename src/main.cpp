#include <Arduino.h>
#include <FastLED.h>

// --- Edit these to match your hardware ---
#define LED_PIN 5        // strip data pin (onboard RGB LED: GPIO48 on v1.0 boards, GPIO38 on v1.1)
#define NUM_LEDS 1
#define LED_TYPE WS2813  // onboard RGB LED: WS2812B
#define BRIGHTNESS 100    // 0-255

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);  // safety cap while USB-powered
  FastLED.clear(true);

  leds[0].r = 200;
  


  FastLED.show();
}

void loop() {
}
