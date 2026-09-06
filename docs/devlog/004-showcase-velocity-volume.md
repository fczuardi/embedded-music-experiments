# Slice 004: Showcase Velocity Volume

The buzzer package now maps MIDI Note On velocity to a constrained M5 speaker
volume range. This slice updates the BLE MIDI buzzer showcase to consume that
package version.

No showcase logic was added for velocity. The existing composition remains:

```cpp
BleMidiInput -> MonophonicInstrumentSink -> SpeakerToneOutput
```

The difference is inside the instrument package. `BleMidiInput` forwards
`NoteEvent.velocity`, `MonophonicInstrument` preserves the velocity of held
notes, and `SpeakerToneOutput` maps it to the hardware-tested volume range.

Validation command:

```bash
env PLATFORMIO_CORE_DIR="$PWD/.platformio-home" pio run -d showcases/ble-midi-buzzer
```

Hardware validation passed on the M5StickC Plus2. Soft and hard key presses from
a real BLE MIDI controller produced useful loudness variation without the
distortion heard in the raw `192..255` speaker volume range.
