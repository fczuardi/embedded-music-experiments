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

Initial hardware validation passed on the M5Stack Core Gray with SynthBridge on
Android.

The first scan/connect attempt was confused by stale Android or SynthBridge BLE
state: SynthBridge continued to show both `M5 Gray Speaker` and the older
`M5 Plus2 MIDI RX` entry after the Stick was powered off. Clearing SynthBridge
app data and resetting Android Bluetooth fixed the connection path.

After reconnecting, the instrument worked through the full package chain. Notes
played correctly, pitch bend was responsive, and the Core Gray speaker handled
lower notes better than the M5StickC Plus2 buzzer.

## Stability Checklist

Use this checklist before calling the Core Gray behavior equivalent to the
M5StickC Plus2 showcase baseline:

| Behavior | Status | Observation target |
| --- | --- | --- |
| Button A panic | Pending deliberate hardware check | Held notes stop immediately after Button A is pressed. |
| Silence on BLE disconnect | Pending deliberate hardware check | Active tone stops when SynthBridge disconnects or the route is broken. |
| BLE reconnection | Pending deliberate hardware check | Notes play again after reconnecting without reflashing or power cycling. |
| Overlapping-note fallback | Pending deliberate hardware check | Releasing the latest held note falls back to the previous held note. |
| Velocity response | Pending deliberate hardware check | Low and high velocities produce an audible volume difference in the configured `5..35` range. |
