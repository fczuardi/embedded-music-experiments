# Slice 002: BLE MIDI Buzzer Showcase

The shared contracts package is now used by both experiments, and both reusable
edges are packaged: BLE MIDI input from `midi-receiver` and buzzer output from
`buzzer-instrument`. This slice adds the first executable composition in the
umbrella repository.

The showcase lives in `showcases/ble-midi-buzzer/` instead of a fourth
repository because it is not a new reusable component. Its purpose is to prove
that existing components can be installed together and connected through the
shared `InstrumentEventSink` contract.

The firmware does only the wiring:

```cpp
BleMidiInput -> MonophonicInstrumentSink -> SpeakerToneOutput
```

It avoids display state, local button controls, sustain, pitch bend, waveform
selection, and any adapter between duplicate event types. The two packages are
pinned by commit SHA in `platformio.ini` so the integration build is
reproducible.

This is the first point where the architectural plan becomes audible: a BLE MIDI
controller should be able to make the M5StickC Plus2 buzzer play notes.

Validation for this slice is:

```bash
env PLATFORMIO_CORE_DIR="$PWD/.platformio-home" pio run -d showcases/ble-midi-buzzer
```

Hardware validation should cover connecting a BLE MIDI controller, pressing and
releasing notes, overlapping notes, disconnecting during a note, and reconnecting.

The first hardware run passed the normal path. The Android bridge app could
connect over BLE MIDI, note presses produced audible buzzer notes, note releases
stopped them, overlapping notes followed the monophonic last-note policy, and a
BLE disconnect during a sounding note silenced the output.

One useful edge case was also observed. With My Midi Hub routing USB MIDI to BLE
MIDI, unplugging the USB controller while a note was held did not send any
observed Note Off, CC 120 All Sound Off, CC 123 All Notes Off, or BLE disconnect.
The receiver cannot infer that hidden route break while BLE remains connected,
so a future local panic button remains the appropriate mitigation on our side.
