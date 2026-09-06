# BLE MIDI Buzzer Showcase

This firmware composes the reusable BLE MIDI input package with the reusable
buzzer instrument package. It is intentionally small: BLE MIDI note events flow
directly into the monophonic instrument sink, which drives the M5StickC Plus2
buzzer through M5Unified.

## Hardware

- M5StickC Plus2
- BLE MIDI controller or phone app capable of sending note on/off events

## Commands

```bash
just showcase-list
just showcase-build
just showcase-upload
just showcase-monitor
just showcase-build 1
env PLATFORMIO_CORE_DIR="$PWD/.platformio-home" pio run -d showcases/ble-midi-buzzer
env PLATFORMIO_CORE_DIR="$PWD/.platformio-home" pio run -d showcases/ble-midi-buzzer --target upload
env PLATFORMIO_CORE_DIR="$PWD/.platformio-home" pio device monitor -d showcases/ble-midi-buzzer
```

## Expected Behavior

The device advertises using the BLE MIDI name provided by
`EmbeddedMusicBleMidiInput`. After a controller connects, note on/off events
should start and stop the buzzer. Disconnecting the controller should silence
the output through `InstrumentEventSink::onDisconnected()`.

Button A is a local panic action. Pressing it clears held instrument state and
stops the buzzer even if the BLE connection remains open. This was validated on
the M5StickC Plus2 hardware.

## Hardware Test Notes

The first M5StickC Plus2 test passed the regular path: connect over BLE MIDI,
play notes, release notes, overlap notes, disconnect BLE during a sounding note,
and reconnect.

One external bridge edge case is known. When My Midi Hub on Android routes a USB
MIDI controller to BLE MIDI, unplugging the USB controller while a note is held
keeps the BLE connection open. In the observed test, the bridge sent no Note Off,
no BLE disconnect, and no standard cleanup control messages such as CC 120 or
CC 123. This showcase does not currently handle those CC messages; they are
mentioned here only as examples of signals that a bridge could send to make the
route failure observable. Without any such signal, the note can remain sounding
until the local panic action or a BLE disconnect occurs.
