# BLE MIDI AMY Showcase

This firmware composes the reusable module boundaries for a richer instrument:

```text
ble-midi-input -> AmyMonophonicInstrumentSink -> amy-synth-m5 -> Core Gray speaker
```

The showcase intentionally has no patch browser, display policy, or custom
musical state. It uses one globally monophonic AMY synth slot where MIDI
channels 1 and 2 select the validated Juno patches 19 and 24 respectively.
The mod wheel (CC1) applies the patch-specific frequency mappings already
validated by the AMY probe. It receives notes, velocity, pitch bend, and
disconnect cleanup through the shared instrument contracts, and drives the
Core Gray speaker through the AMY PCM bridge.

The showcase consumes the published `amy-synth-m5` package. The composition
does not copy code from the AMY probe app.

## Commands

```bash
just showcase-build 3
just showcase-upload 3
just showcase-monitor 3
```

Button A sends panic and stops any held note. The device advertises as
`M5 Gray AMY`. The two MIDI channels are zero-based in the wire protocol, so
the physical MIDI channels 1 and 2 appear to the firmware as channels 0 and 1.
