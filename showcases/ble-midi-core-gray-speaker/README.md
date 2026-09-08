# BLE MIDI Core Gray Speaker Showcase

This firmware composes the reusable BLE MIDI input package, the shared
monophonic instrument package, and the shared M5 tone output package for the
M5Stack Core Gray internal speaker.

## Hardware

- M5Stack Core Gray 1.0
- Android phone running SynthBridge
- BLE MIDI controller, or USB MIDI controller bridged through SynthBridge

## Commands

```bash
just showcase-list
just showcase-build 2
just showcase-upload 2
just showcase-monitor 2
```

## Expected Behavior

The device advertises as `M5 Gray Speaker`. After SynthBridge connects, MIDI
Note On/Off events should start and stop the Core Gray speaker. Note velocity
maps to the showcase volume range `5..35`, pitch bend maps to plus or minus
four semitones, and Button A is a local panic action that clears held notes and
silences the speaker.

Disconnecting BLE should silence the instrument through
`InstrumentEventSink::onDisconnected()`.

## Hardware Test Notes

Not yet validated on hardware. The first manual pass should check BLE
advertising, connection from SynthBridge, Note On/Off, overlapping notes,
velocity response, pitch bend, local panic, disconnect cleanup, and reconnect.
