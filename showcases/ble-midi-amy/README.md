# BLE MIDI AMY Showcase

This firmware composes the reusable module boundaries for a richer instrument:

```text
ble-midi-input -> AmyM5MonophonicSynth -> amy-synth-m5 -> Core Gray speaker
```

The showcase intentionally has no patch browser, display policy, or custom
musical state. It uses one globally monophonic AMY synth slot where MIDI
channels 1 through 16 select the validated Juno patches `0`, `9`, `18`, `24`,
`32`, `40`, `49`, `54`, `64`, `73`, `80`, `89`, `96`, `105`, `114`, and `120`.
The mod wheel (CC1) applies the Juno-style compound frequency modulation
mapping to the active patch. It receives notes, velocity, pitch bend, and
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
`M5 Gray AMY`. MIDI channels are zero-based in the wire protocol, so physical
channels 1 through 16 appear to the firmware as channels 0 through 15. Channel
selection changes the patch in the one shared slot; it does not make the
showcase multitimbral or provide 16 simultaneous voices.
