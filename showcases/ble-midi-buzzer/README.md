# BLE MIDI Buzzer Showcase

This firmware composes the reusable BLE MIDI input package, the shared
monophonic instrument package, and the M5StickC Plus2 buzzer output package. It
is intentionally small: BLE MIDI note events flow directly into the monophonic
instrument sink, which drives the M5StickC Plus2 buzzer through M5Unified.

## Hardware

- M5StickC Plus2
- BLE MIDI controller or phone app capable of sending note on/off events
- Pitch bend source for expression tests, preferably SynthBridge on Android or
  an Arturia controller routed through SynthBridge Pro Trial

## Commands

```bash
just showcase-list
just showcase-build
just showcase-upload
just showcase-monitor
just showcase-build 1
```

## Expected Behavior

The device advertises using the BLE MIDI name provided by
`EmbeddedMusicBleMidiInput`. After a controller connects, note on/off events
should start and stop the buzzer. Note On velocity is mapped by
`m5-buzzer-output` to a constrained M5 speaker volume range, so
different key velocities should produce audible loudness changes without using
the distorted upper volume range. This has been validated on the M5StickC Plus2
with a real BLE MIDI controller. Disconnecting the controller should silence the
output through `InstrumentEventSink::onDisconnected()`.

Button A is a local panic action. Pressing it clears held instrument state and
stops the buzzer even if the BLE connection remains open. This was validated on
the M5StickC Plus2 hardware.

Pitch bend events are logged to serial as `pitch_bend` and forwarded to the
instrument. The current instrument policy maps the MIDI bend range
`-8192..8191` to plus or minus two semitones with a small center dead zone.

For velocity-volume calibration, edit `SHOWCASE_VELOCITY_VOLUME_RANGE` in
`src/main.cpp` and upload again with `just showcase-upload`. This only changes
the showcase firmware; it does not require a new package commit.

For pitch bend calibration, edit `SHOWCASE_PITCH_BEND_RANGE_SEMITONES` in
`src/main.cpp` and upload again. The package default is `2.0`, meaning plus or
minus two semitones across the full MIDI pitch bend range.

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

A second My MIDI Hub edge case affects pitch bend performance. With Arturia USB
OTG routed through My MIDI Hub to BLE MIDI, dense pitch strip activity delayed
Note Off. The same physical Arturia strip routed through SynthBridge Pro Trial
stopped notes immediately, and SynthBridge's on-screen pitch bend strip also
kept Note Off immediate. Use SynthBridge as the preferred Android validation
route for audible pitch bend.
