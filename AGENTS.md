# ESP32 LED Prototype Agent Notes

## Project Check-In

- State your tool name and "project config loaded for ESP32 LED prototyping".

## Project Mode

This is a solo/owned hardware prototyping project. Track useful textual agent config and use symlinked reusable rule packs under [.agents/rules](.agents/rules) when the sandbox allows it.

## Agent Rule Packs

After reading this file, recursively read adjacent [.agents/rules](.agents/rules) and [.agents.local/rules](.agents.local/rules) directories in deterministic path-sorted order. Treat these rule folders as modular extensions of this entrypoint, not scratch space.

## Project Overview

This repo is a PlatformIO project for rapid ESP32 programmable LED experiments. It uses the Arduino framework with FastLED so sketches can be edited, built, uploaded, and monitored quickly.

Physical hardware: an ESP32-S3 dev board connected via its native USB port, driving a WS2813 strip on GPIO5 (or the onboard WS2812 RGB LED on GPIO48/38).

The setup is intentionally minimal: one sketch, one build environment, hardware constants at the top of the sketch. Keep it that way — no config headers, no env matrices, no abstraction layers unless Alex asks.

## Key Files

- [src/main.cpp](src/main.cpp) is the whole sketch; LED pin/count/type/brightness are `#define`s at the top.
- [platformio.ini](platformio.ini) has a single `esp32s3` environment. Its board/flash/monitor/upload settings encode hard-won hardware quirks (octal flash profile, watchdog-reset after upload, DTR/RTS strap handling) — do not "clean them up".

## Commands

- `pio run` compiles.
- `pio run -t upload` builds and flashes.
- `pio device monitor` opens the serial monitor (exception decoder + timestamps preconfigured).
- Uses the default user-global PlatformIO core (`~/.platformio`); no wrapper scripts, no custom env vars. Keep `platform`/`lib_deps` versions pinned in [platformio.ini](platformio.ini).

## Hardware Notes

If an upload fails to connect, the board needs a manual download-mode entry: hold `BOOT`, tap `RESET`, release `BOOT`, retry. The USB device identity changes between app mode and download mode; both enumerate as `/dev/cu.usbmodem*`.
