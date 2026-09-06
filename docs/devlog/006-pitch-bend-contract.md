# Slice 006: Pitch Bend Contract

The first BLE MIDI buzzer milestone only carried note events across the shared
firmware boundary. Pitch bend is the next expression control we want to route
without coupling BLE parsing to audio policy.

This slice adds `PitchBendEvent` to the shared contracts package:

```cpp
struct PitchBendEvent {
  uint8_t channel;
  int16_t value;
};
```

The value is centered around zero and uses the MIDI pitch bend range
`-8192..8191`. The contract intentionally does not say how many semitones that
means. A receiver should normalize raw MIDI bytes into this event, while an
instrument decides later how to map it to frequency or timbre.

`InstrumentEventSink` now has an `onPitchBendEvent()` method next to
`onNoteEvent()` and `onDisconnected()`. That makes pitch bend part of the same
typed event boundary as notes, while keeping it a separate event type.
