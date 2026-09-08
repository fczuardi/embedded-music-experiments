# Core Gray BLE MIDI Showcase

## Goal

Build the second umbrella showcase: the same BLE MIDI monophonic instrument
idea as showcase 1, but targeting the M5Stack Core Gray speaker instead of the
M5StickC Plus2 buzzer.

## Design

Showcase 1 and showcase 2 now share `showcases/common/BleMidiInstrumentShowcase.h`.
That common runner owns the BLE MIDI input, monophonic instrument, instrument
sink, pitch bend logging, panic button behavior, uptime logging, and simple
display. The board-specific `main.cpp` files only choose M5 initialization,
the tone output backend, labels, velocity-volume calibration, and pitch bend
range.

Showcase 2 lives at `showcases/ble-midi-core-gray-speaker` and composes:

- `ble-midi-input` from `midi-receiver` commit `a58c1119`;
- `monophonic-instrument-0.1.1.tar.gz`;
- `m5-tone-output-0.1.2.tar.gz`;
- `M5CoreGrayToneOutput`.

The Core Gray firmware advertises as `M5 Gray Speaker`, maps velocity to
volume `5..35`, and uses a plus or minus four semitone pitch bend range to
match the expressive showcase behavior already used by the buzzer showcase.

The Core Gray build exceeded the default app slot by about 12 KB, so showcase 2
uses the standard ESP32 `huge_app.csv` partition layout. The resulting firmware
uses 1,322,457 bytes, which is 42.0% of the larger 3,145,728-byte app slot.

## Tooling

`just showcase-list` now exposes:

```text
1	ble-midi-buzzer	showcases/ble-midi-buzzer
2	ble-midi-core-gray-speaker	showcases/ble-midi-core-gray-speaker
```

`just showcase-upload 1` and `just showcase-upload 2` use the ESP32 probe guard
before flashing. The guard can distinguish the M5StickC Plus2 from the Core
Gray based on the ESP32 chip family observed by `esptool.py chip_id`.

Showcase package archives are prepared by `scripts/prepare-showcase-archives.sh`
instead of ad hoc CI YAML. The showcase `platformio.ini` files consume those
archives from the umbrella repo's ignored `.tmp/` directory, which works both
locally and in GitHub Actions.

## Verification

Commands run:

```bash
scripts/prepare-showcase-archives.sh
just showcase-list
just showcase-build 1
just showcase-build 2
```

Both showcase builds passed. Showcase 1 still builds after the common-runner
refactor. Showcase 2 resolves the same package graph with `M5CoreGrayToneOutput`
and links successfully with the larger app partition.

## Hardware Notes

No hardware upload was run in this slice. The next hardware pass should upload
showcase 2 to the Core Gray and validate BLE advertising, SynthBridge
connection, Note On/Off, overlapping notes, velocity response, pitch bend,
Button A panic, disconnect cleanup, and reconnect.
