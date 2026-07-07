# ESP32 LED Prototype

Minimal PlatformIO sandbox for setting individual addressable LEDs from an ESP32-S3 (native USB port, the one labeled `USB`).

The whole project is two files: [platformio.ini](platformio.ini) (board + library config) and [src/main.cpp](src/main.cpp) (the sketch).

## Workflow

1. Edit the constants and colors at the top of [src/main.cpp](src/main.cpp) (`LED_PIN`, `NUM_LEDS`, `LED_TYPE`, `BRIGHTNESS`).
2. `pio run -t upload`
3. Look at the LEDs.

- `pio run` — compile without flashing
- `pio device monitor` — serial output, if the sketch uses `Serial.printf(...)`. Close it (Ctrl+C) before uploading; it holds the port exclusively.

In VS Code with the PlatformIO extension, the check-mark (build), arrow (upload), and plug (monitor) buttons in the status bar do the same.

## IntelliSense

Install the recommended extensions when VS Code prompts (PlatformIO IDE + C/C++, listed in `.vscode/extensions.json`). PlatformIO generates the include paths for FastLED and the Arduino core automatically into `.vscode/c_cpp_properties.json`. If completion ever goes stale, run `pio project init --ide vscode`.

## Portability (Windows/Linux)

Nothing here is macOS-specific. On another machine: install VS Code + the PlatformIO IDE extension, copy this folder, plug the board into its native USB port, upload. Toolchains download to the user-global PlatformIO core (`~/.platformio`) on first build; serial ports are auto-detected (`COMx` on Windows).

## Setting LEDs

```cpp
leds[0] = CRGB::Red;          // named color
leds[7] = CRGB(255, 100, 0);  // r, g, b
FastLED.show();               // nothing changes until you call this
```

## Wiring

WS2813 strip (single data wire):

- Strip `DI` → GPIO5 (ideally through a ~330 Ω resistor), strip GND → board GND.
- Tie strip `BI` → GND at the input end for the first test. If that fails, try feeding GPIO5 to both `DI` and `BI`.

SK9822/APA102 strip (data + clock): `DI` → GPIO5, `CI` → GPIO6, and in the sketch use
`FastLED.addLeds<SK9822, LED_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);`

Either way: power the strip from its external supply (check the voltage marking), never from the board's 3V3 pin, and share grounds. The onboard RGB LED needs no wiring: `LED_PIN 48` (board v1.0) or `38` (v1.1), `NUM_LEDS 1`, `LED_TYPE WS2812B`.

Power draw is capped at 500 mA in `setup()` — raise it once the strip has its own adequate supply.

## Notes

- The board config in [platformio.ini](platformio.ini) looks odd but is deliberate: this S3 has octal flash (the generic devkit profile boot-loops with `flash_ret == ESP_OK`), RTS reset re-straps it into download mode (uploads exit via watchdog reset instead), and DTR/RTS must stay in the right state when opening the monitor. Don't simplify it away.
- If an upload ever fails to connect: hold `BOOT`, tap `RESET`, release `BOOT`, retry.
