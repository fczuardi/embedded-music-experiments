# Slice 029: BLE MIDI Scan Response Name Repin

## Goal

Update the umbrella showcases to consume the BLE MIDI input package fix that
places the configured device name in NimBLE scan-response data.

## Problem

The previous showcase repin consumed `ble-midi-input@0.1.3`, which called
`setName(deviceName)` on the NimBLE advertising object. A later raw Linux
`btmon` trace showed why that was not enough for BLE MIDI:

- the primary advertisement contained flags plus the 128-bit BLE MIDI service
  UUID;
- the scan response had zero bytes;
- no `Name (complete)` field was present in the raw BLE data.

The old name still shown by some scanners was cached host state, not proof that
the current firmware advertised a name.

## Design

Both umbrella showcases now pin `ble-midi-input` to `midi-receiver` commit
`c40e71bf`, which publishes `ble-midi-input@0.1.4`.

That package version enables NimBLE scan-response data before setting the
device name, leaving the primary advertisement for the BLE MIDI service UUID
and exposing the configured name to active scanners.

## Verification Target

```bash
just showcase-build 1
just showcase-build 2
```

Hardware follow-up should upload each showcase and confirm with `btmon` that
the ESP32 scan response contains `Name (complete)` for the configured showcase
name.

## Hardware Observation

Showcase 1 was uploaded to the M5StickC Plus2 after the repin. The expected
configured name appeared during BLE scanning, confirming that the
scan-response-name fix works for the buzzer showcase path.

Showcase 2 was also uploaded to the M5Stack Core Gray after the repin and the
configured `M5 Gray Speaker` name appeared during BLE scanning. That confirms
the scan-response-name fix across both umbrella showcase targets.
