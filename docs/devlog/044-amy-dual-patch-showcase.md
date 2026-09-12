# Showcase 3: dual AMY patches

## Goal

Make the umbrella Showcase 3 demonstrate the multi-channel AMY composition
already validated in `amy-synth-m5`, instead of presenting the same patch on
every MIDI channel.

## Design

The application remains a small composition of published packages:

```text
ble-midi-input -> AmyM5MonophonicSynth -> Core Gray speaker
```

It uses one globally monophonic AMY slot. MIDI channel 1 selects Juno patch 19
and MIDI channel 2 selects patch 24. CC1 mappings are configured declaratively
through the facade's Juno-aware performance default, which targets the common
relative tonal oscillator layout instead of exposing patch-specific oscillator
indices to the showcase. The transport, note-priority policy, AMY facade, audio
gate, and speaker bridge remain package code.

This is not two simultaneous voices. A single controller can change channels
to choose another monophonic instrument, while the active note continues to be
owned by the shared monophonic policy.

## Verification

Expected command-line checks:

```bash
just showcase-build 3
just showcase-budget 3
```

The build consumes the published `amy-synth-m5@0.2.9`, whose facade includes
the Juno-aware CC1 mapping and the post-patch-load control replay barrier.

The hardware target is a Core Gray running Showcase 3. Verify that physical
MIDI channels 1 and 2 produce patches 19 and 24, that velocity and pitch bend
remain functional, that CC1 affects the selected patch, and that Button A
still triggers panic.

The dual-patch behavior and mappings were previously validated in the AMY
repository. The updated published-package build was verified locally; the
hardware validation target remains the same Core Gray sequence, including
cross-channel fallback with modulation preserved.
