# Slice 003: Local Panic Button

The first BLE MIDI buzzer hardware test showed that BLE disconnects silence the
instrument correctly. It also showed a different route failure: an Android
bridge can keep BLE connected while losing its upstream USB MIDI controller and
forwarding no cleanup event.

This slice adds a local panic action to the showcase. Button A calls
`MonophonicInstrumentSink::panic()`, which comes from the reusable
`EmbeddedMusicBuzzerInstrument` package. The showcase only maps hardware UI to
that domain action; it does not implement the panic semantics itself.

The panic action clears held note state and stops the buzzer even when no MIDI
message or BLE lifecycle event arrives. This keeps the workaround local and
explicit without pretending that a panic is a transport disconnect.

Verification command:

```bash
env PLATFORMIO_CORE_DIR="$PWD/.platformio-home" pio run -d showcases/ble-midi-buzzer
```

Hardware validation passed on the M5StickC Plus2. Pressing Button A while a note
was sounding stopped the buzzer immediately, confirming that the showcase now
has a reliable local recovery path for stuck notes.
