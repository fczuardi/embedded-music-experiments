# NimBLE Advertised Name Repin

## Goal

The BLE MIDI package now explicitly includes the configured device name in the
NimBLE advertising data. Revalidate the umbrella showcases against that package
commit so the examples track the current plug-and-play BLE path.

## Design

Both BLE showcases now pin `ble-midi-input` to `midi-receiver` commit
`902f1e52`, which publishes `ble-midi-input@0.1.3`.

This commit keeps the prior NimBLE 2 callback fix and adds explicit
`_advertising->setName(deviceName)` behavior in the package-owned NimBLE
backend.

## Verification

Commands:

```bash
cd showcases/ble-midi-buzzer
pio run

cd ../ble-midi-core-gray-speaker
pio run
```

Both builds passed.

## Hardware Observation

Pending. The expected check is to upload a showcase and scan/connect from
Android. MIDI-specific apps may still show `Bluetooth MIDI`, but generic BLE
scanners should have a better chance of seeing the configured local name instead
of `-`.
