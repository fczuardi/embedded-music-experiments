# Slice 016: Use M5 Tone Output In Showcase 1

Showcase 1 now consumes `monophonic-instrument-0.1.1.tar.gz` and the renamed
`m5-tone-output-0.1.1.tar.gz` package archive instead of the removed
`m5-buzzer-output` archive. The runtime behavior remains the same: BLE MIDI
events flow through `MonophonicInstrumentSink`, and `M5BuzzerToneOutput` drives
the M5StickC Plus2 buzzer through the shared M5 tone output core.

This keeps the proven Plus2 showcase aligned with the package shape needed for
the next Core Gray speaker output slice.

Validation target:

```bash
just showcase-build 1
```
