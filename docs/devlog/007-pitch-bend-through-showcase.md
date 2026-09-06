# Slice 007: Pitch Bend Through The Showcase

The shared contract now has `PitchBendEvent`, the BLE MIDI package emits it,
and the buzzer instrument package accepts it. This slice updates the BLE MIDI
buzzer showcase to consume those package versions together.

The showcase wraps `MonophonicInstrumentSink` with a small logging sink:

```cpp
void onPitchBendEvent(const PitchBendEvent& event) override;
```

The wrapper prints `pitch_bend: channel=... value=...` to serial, then forwards
the event to the buzzer instrument sink. The buzzer sink intentionally ignores
the event for now, so this is an integration slice rather than an audible pitch
bend slice.

This gives us a narrow hardware test: connect a BLE MIDI controller, move the
pitch strip or wheel, and confirm that the showcase receives centered
`-8192..8191` values without changing note playback behavior.

Hardware testing with the Arturia controller confirmed the path. The monitor
showed values near the lower limit around `-8192`, an upper value around `7804`,
and a touch-strip return value around `64` instead of a perfect `0`. That
supports adding a small dead zone when a later slice makes pitch bend audible.
