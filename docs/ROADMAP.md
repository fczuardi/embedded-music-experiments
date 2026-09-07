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
- `PitchBendEvent` is part of the shared contract, the BLE MIDI package emits
  it, and the buzzer package accepts it without changing the current voice.
- The showcase logs centered pitch bend values and has validated the complete
  event path on real hardware. Pitch bend is observable but not audible yet.

## Next Priority Slices

1. **Pitch bend musical state and mapping**
   Define the smallest backend-independent interpretation of `PitchBendEvent`.
   Keep the shared event centered at `-8192..8191`, choose an initial musical
   range such as +/-2 semitones in instrument or performance policy, and cover
   the note-plus-bend frequency calculation with native tests. Account for the
   small non-zero return value observed on the Arturia touch strip without
   putting device-specific correction in the BLE receiver.

2. **Audible pitch bend through the current backend**
   Connect the mapped pitch to `SpeakerToneOutput` with the smallest useful
   output capability, then test it on hardware. Record whether frequency updates
   are continuous enough, whether they restart articulation, and whether they
   create audible clicks. Keep those observations as evidence for comparing a
   later sampled-audio backend rather than assuming the current backend must be
   replaced.

3. **Simple channel behavior**
   Decide one small channel-based behavior, such as per-channel waveform choice.
   Keep this as instrument policy, not receiver logic.

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
   pitch-bend continuity, transition clicks, latency, clarity, CPU/memory cost,
   and implementation complexity. Keep both backends if they demonstrate useful
   trade-offs.

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
- Keep each slice small enough to build, test, document, commit, and review.
- Move speculative ideas down until a concrete test makes them relevant.
