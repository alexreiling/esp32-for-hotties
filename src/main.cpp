#include <Arduino.h>
#include <FastLED.h>

// --- Edit these to match your hardware ---
#define LED_PIN 13   // SK9822 DI; strip data pin (onboard RGB LED: GPIO48 on v1.0 boards, GPIO38 on v1.1)
#define CLOCK_PIN 14 // SK9822 CI
#define NUM_LEDS 5
#define LED_TYPE SK9822 // onboard RGB LED: WS2812B
#define BRIGHTNESS 100  // 0-255

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500); // safety cap while USB-powered
  FastLED.clear(true);
  leds[0].r = 200;
  leds[1].b = 200;
  leds[2].g = 200;
  leds[3].r = 200;
  leds[4].b = 200;

  FastLED.show();
}

void loop()
{
}
