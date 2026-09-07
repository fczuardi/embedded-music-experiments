# Slice 011: Audible Pitch Bend Showcase

The route comparison gave us a better test target: SynthBridge routes preserve
immediate Note Off during pitch bend, while My MIDI Hub's USB-to-BLE bridge does
not. This slice updates the BLE MIDI buzzer showcase to use the
`EmbeddedMusicBuzzerInstrument` package version where pitch bend changes the
active note frequency.

The showcase did not need new dispatch logic. It was already forwarding
`PitchBendEvent` through the logging wrapper:

```cpp
innerSink_.onPitchBendEvent(event);
```

The important change is the package revision. `MonophonicInstrument` now treats
pitch bend as instrument policy: the MIDI range `-8192..8191` maps linearly to a
configurable semitone range, with a small dead zone around center for touch
strips that do not return to perfect zero.

The showcase sets the initial range explicitly:

```cpp
constexpr float SHOWCASE_PITCH_BEND_RANGE_SEMITONES = 4.0f;
instrument.setPitchBendRangeSemitones(SHOWCASE_PITCH_BEND_RANGE_SEMITONES);
```

This mirrors the velocity-volume calibration style. We can change the showcase
constant and upload again without committing a new instrument package revision.
The package default remains plus or minus two semitones; the showcase uses plus
or minus four to make the override and audible movement explicit.

The hardware validation used the responsive SynthBridge route:

```text
Android SynthBridge -> BLE MIDI -> showcase
Arturia USB OTG -> Android SynthBridge Pro Trial -> BLE MIDI -> showcase
```

My MIDI Hub remains useful for some basic BLE routing tests, but it is a
known-problem route for dense pitch bend performance.

The final test made bend audible in both directions while Note Off remained
immediate. This closes the complete path from the BLE MIDI source through the
shared event contract and monophonic policy to the current buzzer backend.
