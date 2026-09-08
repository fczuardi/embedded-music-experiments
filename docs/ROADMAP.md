# Roadmap

This roadmap tracks the next useful slices across the umbrella repository,
`midi-receiver`, and `monophonic-instrument`. It is intentionally practical: items
move up when they unlock a better hardware test, clarify a contract, or make a
module more reusable.

## Completed Milestone: BLE MIDI Sound Box

Goal: use a BLE MIDI controller to play the M5StickC Plus2 buzzer through
packaged modules.

Status:

- `firmware-contracts` is shared by both firmware packages.
- `ble-midi-input` is packaged from `midi-receiver`.
- The original combined buzzer instrument package has been split
  into `monophonic-instrument` and `m5-tone-output` archives for the showcase
  migration.
- `showcases/ble-midi-buzzer` composes both packages and passed happy-path
  hardware tests.
- `showcases/ble-midi-core-gray-speaker` now runs the same BLE MIDI monophonic
  instrument idea on the M5Stack Core Gray speaker. Initial hardware validation
  passed with SynthBridge after clearing stale Android BLE app state.
- The showcase now composes `ble-midi-input`, `monophonic-instrument`,
  and `m5-tone-output`.
- The showcase has a local panic button for route failures that do not produce
  MIDI cleanup events or BLE disconnects, and that button has been validated on
  real hardware.
- The M5 tone output package maps Note On velocity to a constrained speaker
  volume range, and the showcase velocity response has been validated on real
  hardware.
- `PitchBendEvent` is part of the shared contract, the complete event path has
  been observed on hardware, and the showcase now consumes the buzzer package
  version that makes bend audible. Comparative route tests point to My MIDI
  Hub's USB-to-BLE bridge as the problematic path; SynthBridge routes stop notes
  immediately even during pitch bend activity.
- Audible pitch bend has been validated through the responsive SynthBridge
  route. The package keeps a ±2-semitone default while the showcase deliberately
  overrides it to ±4 semitones, just as it overrides the default velocity-volume
  range.

**Status: complete.**

## Next Priority Slices

1. **Simple channel behavior**
   Decide one small channel-based behavior, such as per-channel waveform choice.
   Keep this as instrument policy, not receiver logic.

2. **Raw BLE-MIDI transport research**
   Keep this as a fallback if future sources reproduce the My MIDI Hub backlog.
   Do not redesign the transport while SynthBridge routes remain responsive.

## Second Hardware Validation: M5Stack Core Gray

Bring the available M5Stack Core Gray 1.0 into the test bench as the second
hardware target. The goal is not merely to add another supported board: it is
to discover which
existing boundaries are genuinely portable.

1. **Core Gray speaker smoke test**
   Initialize the board through M5Unified, play and stop A4 through its built-in
   1 W speaker, and record the effective speaker configuration. Keep BLE out of
   this first test.

2. **Audio-output boundary check**
   Determine whether `M5ToneOutputCore` can support both devices through
   explicit configuration wrappers or whether the Gray needs a separate output
   backend.
   Keep Plus2 buzzer calibration and Gray speaker calibration outside musical
   policy, and base the decision on observed differences rather than on a goal
   of maximizing shared code.

3. **Multi-board build coverage**
   Build the relevant firmware for both Plus2 and Gray in CI. Board selection,
   pinout, speaker setup, display layout, and physical controls may vary;
   shared contracts and pure instrument policy should compile unchanged.

4. **Core Gray BLE MIDI showcase**
   Compose the existing BLE MIDI input and monophonic instrument with the Gray
   output. Validate Note On/Off, overlapping-note fallback, velocity, panic,
   and disconnect cleanup on its speaker. Preserve the Plus2 showcase as the
   baseline rather than converting it into a single application full of board
   conditionals.
   Complete: the showcase passed deliberate hardware validation with an Arturia
   controller routed through Android SynthBridge to the M5Stack Core Gray.
   Validated local panic, disconnect cleanup, reconnect without reset,
   overlapping-note fallback with preserved velocities, velocity-to-volume
   response, and the previously observed pitch bend path.

5. **Cross-hardware comparison**
   Document clarity, useful volume range, velocity response, note latency,
   cleanup behavior, and the amount of code that remained
   shared. Use these findings to refine boundaries before starting the sampled
   oscillator or external I2S work.

## Parallel Audio Exploration

The proven `M5BuzzerToneOutput` remains the Plus2 baseline backend. New audio
paths should be added alongside it and compared in separate showcases; they do
not need to replace it to be useful.

1. **Monophonic sampled oscillator proof**
   Generate one continuous oscillator in software and route it to an available
   output on the M5StickC Plus2. Start with one waveform and one voice. This is
   informed by the multi-oscillator approach in
   [necobit/M5Stack-MIDI-Module](https://github.com/necobit/M5Stack-MIDI-Module),
   but should be implemented within this ecosystem's existing boundaries.

2. **Backend comparison showcase**
   Compare the sampled oscillator with `M5BuzzerToneOutput` on the same hardware:
   transition clicks, latency, clarity, CPU/memory cost, and implementation
   complexity. Keep both backends if they demonstrate useful trade-offs.

3. **Expression experiments on the sampled path**
   Only after the basic oscillator is proven, explore envelope-controlled
   amplitude, legato, glide, vibrato, or multiple oscillators within one
   monophonic voice. Polyphony remains a separate later experiment.

4. **External I2S line output**
   Explore a PCM5102-based output for the M5StickC Plus2 after continuous sample
   generation is understood. Treat the DAC board and board-specific pinout as a
   hardware backend while preserving reusable oscillator and musical-policy
   code. A later M5StickS3 experiment may use its built-in audio path or its own
   dedicated DAC wiring without requiring the physical HATs to be identical.

## Candidate Slices

- Add support for CC 120 All Sound Off and CC 123 All Notes Off.
- Revisit the velocity curve if more hardware tests show that the current
  package default or the showcase's calibrated `96..136` speaker volume range
  is too subtle or too aggressive.
- Choose showcase-specific BLE advertised names now that `ble-midi-input` accepts
  a compile-time name.
- Document the one-active-instance constraint of BLE MIDI examples in the
  showcase README.
- Add tags for package milestones once the SHA-pinned integration settles.

## Deferred Ideas

- Sustain/hold behavior in the monophonic instrument.
- Modulation CC1 mapped to vibrato or timbre.
- Polyphonic buzzer mixing.
- Sequencer or arpeggiator.
- USB MIDI host on hardware that supports it well.

## Prioritization Rules

- Prefer slices that produce a hardware-observable improvement.
- Prefer contract changes only after at least one producer and one consumer need
  them.
- Keep transport, event contracts, instrument policy, and audio output separate.
- Keep board selection, pinout, calibration, display, and physical controls at
  composition edges instead of spreading hardware conditionals through musical
  semantics.
- Keep each slice small enough to build, test, document, commit, and review.
- Move speculative ideas down until a concrete test makes them relevant.
