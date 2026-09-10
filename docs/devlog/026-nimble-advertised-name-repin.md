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

Validated on hardware with both umbrella showcases:

- Showcase 1 uploaded and ran on the M5StickC Plus2. The BLE MIDI buzzer
  showcase remained usable from the Android controller path.
- Showcase 2 uploaded and ran on the M5Stack Core Gray. The BLE MIDI speaker
  showcase remained usable from the Android controller path.

The remaining issue is name presentation in SynthBridge. Even after the
NimBLE backend explicitly sets the configured device name in advertising,
SynthBridge still does not display the expected names consistently. Earlier
tests showed app-dependent behavior: some MIDI apps display `Bluetooth MIDI`,
some generic BLE scanners may show the configured local name, and Android app
cache/state may also affect what appears during repeated firmware tests.
