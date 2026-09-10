# Slice 025: Re-pin Showcases to NimBLE BLE MIDI

## Goal

Revalidate the two existing umbrella showcases after `ble-midi-input` made the
ESP32 NimBLE backend the package default.

## Design Choices

Both showcases now pin `ble-midi-input` to `midi-receiver` commit `d155e75`.
That commit keeps BLE backend selection inside the package instead of forcing
each consumer to know about BLE-MIDI's classic ESP32 backend versus NimBLE.

The showcase PlatformIO environments also move to pioarduino, matching the
modern ESP32 platform used by the AMY synth probe. The M5StickC Plus2 showcase
sets `board_build.variant = m5stack_stickc_plus2` because pioarduino provides
the Arduino variant but the board manifest does not select it automatically.

## Limits

This slice validates command-line builds. Hardware behavior still needs the same
physical BLE MIDI smoke checks used by the original showcase slices.

## Verification Commands

```bash
cd showcases/ble-midi-buzzer
pio run

cd ../ble-midi-core-gray-speaker
pio run
```

## Build Observations

Both showcase builds passed with `ble-midi-input@0.1.1+sha.d155e75`.
PlatformIO installed `NimBLE-Arduino@2.5.1` through BLE-MIDI and compiled the
package through `BLEMIDI_ESP32_NimBLE.h`, confirming that consumers no longer
need an app-local backend flag.
