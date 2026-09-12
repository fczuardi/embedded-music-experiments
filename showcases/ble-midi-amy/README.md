# BLE MIDI AMY Showcase

This firmware composes the reusable module boundaries for a richer instrument:

```text
ble-midi-input -> AmyMonophonicInstrumentSink -> amy-synth-m5 -> Core Gray speaker
```

The showcase intentionally has no patch browser, display policy, or custom
musical state. It uses one AMY synth slot with the validated Juno patch 19,
receives notes, velocity, pitch bend, and disconnect cleanup through the shared
instrument contracts, and drives the Core Gray speaker through the AMY PCM
bridge.

The showcase consumes the published `amy-synth-m5` package. The composition
does not copy code from the AMY probe app.

## Commands

```bash
just showcase-build 3
just showcase-upload 3
just showcase-monitor 3
```

Button A sends panic and stops any held note. The device advertises as
`M5 Gray AMY`.
