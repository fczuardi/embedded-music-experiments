# Roadmap

This roadmap tracks the next useful slices across the umbrella repository,
`midi-receiver`, and `buzzer-instrument`. It is intentionally practical: items
move up when they unlock a better hardware test, clarify a contract, or make a
module more reusable.

## Current Milestone: BLE MIDI Sound Box

Goal: use a BLE MIDI controller to play the M5StickC Plus2 buzzer through
packaged modules.

Status:

- `EmbeddedMusicFirmwareContracts` is shared by both firmware packages.
- `EmbeddedMusicBleMidiInput` is packaged from `midi-receiver`.
- `EmbeddedMusicBuzzerInstrument` is packaged from `buzzer-instrument`.
- `showcases/ble-midi-buzzer` composes both packages and passed happy-path
  hardware tests.
- The showcase has a local panic button for route failures that do not produce
  MIDI cleanup events or BLE disconnects, and that button has been validated on
  real hardware.
- The buzzer package maps Note On velocity to a constrained speaker volume
  range, and the showcase velocity response has been validated on real hardware.
- `PitchBendEvent` is part of the shared contract and the complete event path
  has been observed on hardware, but audible pitch bend is currently
  deprioritized. The Android USB-to-BLE bridge path tested so far can flood the
  BLE-MIDI stack with stale bend values and delay Note Off, even when bend is
  ignored by the instrument.

## Next Priority Slices

1. **Simple channel behavior**
   Decide one small channel-based behavior, such as per-channel waveform choice.
   Keep this as instrument policy, not receiver logic.

2. **Core Gray speaker smoke test**
   Bring the second hardware target into the bench with a minimal local tone
   test. Keep BLE, pitch bend, and cross-repo composition out of this first
   slice.

3. **Raw BLE-MIDI transport research**
   Investigate whether a lower-level BLE packet parser can preserve Note On/Off
   while dropping or sampling pitch bend before it enters a FIFO. This is
   research, not the next performance feature.

## Second Hardware Validation: M5Stack Core Gray

Bring the available M5Stack Core Gray 1.0 into the test bench as the second
hardware target. The
goal is not merely to add another supported board: it is to discover which
existing boundaries are genuinely portable.

1. **Core Gray speaker smoke test**
   Initialize the board through M5Unified, play and stop A4 through its built-in
   1 W speaker, and record the effective speaker configuration. Keep BLE out of
   this first test.

2. **Audio-output boundary check**
   Determine whether `SpeakerToneOutput` can support both devices through
   explicit configuration or whether the Gray needs a separate output backend.
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

5. **Cross-hardware comparison**
   Document clarity, useful volume range, velocity response, note latency,
   cleanup behavior, and the amount of code that remained
   shared. Use these findings to refine boundaries before starting the sampled
   oscillator or external I2S work.

## Parallel Audio Exploration

The proven `SpeakerToneOutput` remains the baseline backend. New audio paths
should be added alongside it and compared in separate showcases; they do not
need to replace it to be useful.

1. **Monophonic sampled oscillator proof**
   Generate one continuous oscillator in software and route it to an available
   output on the M5StickC Plus2. Start with one waveform and one voice. This is
   informed by the multi-oscillator approach in
   [necobit/M5Stack-MIDI-Module](https://github.com/necobit/M5Stack-MIDI-Module),
   but should be implemented within this ecosystem's existing boundaries.

2. **Backend comparison showcase**
   Compare the sampled oscillator with `SpeakerToneOutput` on the same hardware:
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
- Revisit audible pitch bend only after transport-level research shows a way to
  prevent bend floods from delaying Note Off, or after testing a different MIDI
  bridge that does not create the same backlog.
- Make the BLE advertised name configurable in `EmbeddedMusicBleMidiInput`.
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
