# Core Gray BLE MIDI Showcase

## Goal

Build the second umbrella showcase: the same BLE MIDI monophonic instrument
idea as showcase 1, but targeting the M5Stack Core Gray speaker instead of the
M5StickC Plus2 buzzer.

## Design

Showcase 1 and showcase 2 intentionally keep complete `main.cpp` files. These
showcases are usage examples for composing the package set, so each sketch shows
the full wiring: BLE MIDI input, monophonic instrument, instrument sink, tone
output backend, pitch bend logging, panic button behavior, uptime logging, and
simple display.

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

Both showcase builds passed. Showcase 1 remains the Plus2 buzzer sample.
Showcase 2 resolves the same package graph with `M5CoreGrayToneOutput` and
links successfully with the larger app partition.

## Hardware Notes

After the build slice, showcase 2 was uploaded to the M5Stack Core Gray and
validated with SynthBridge on Android.

The first connection attempt exposed stale Android or SynthBridge BLE state.
SynthBridge still displayed both `M5 Gray Speaker` and `M5 Plus2 MIDI RX` after
the Stick was powered off, and the Core Gray entry did not connect reliably.
Clearing SynthBridge app data and resetting Android Bluetooth fixed the scan and
connection path.

With that cleared, the Core Gray showcase connected and the instrument worked.
Note playback reached the speaker through the composed package chain, pitch bend
was responsive, and the speaker handled lower notes better than the Plus2
buzzer.

Still to check in a later pass: local Button A panic, disconnect cleanup,
reconnect, and a more deliberate velocity-volume comparison.
