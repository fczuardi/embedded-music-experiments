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

## Next Priority Slices

1. **Pitch bend event contract**
   Add a typed pitch bend path separate from `NoteEvent`. The receiver already
   observes pitch bend, and a monophonic instrument can use it naturally by
   changing the active voice frequency.

2. **Simple channel behavior**
   Decide one small channel-based behavior, such as per-channel waveform choice.
   Keep this as instrument policy, not receiver logic.

## Candidate Slices

- Add support for CC 120 All Sound Off and CC 123 All Notes Off.
- Revisit the velocity curve if more hardware tests show that the current
  `64..128` speaker volume range is too subtle or too aggressive.
- Add a serial diagnostic sink to the showcase for integration debugging.
- Make the BLE advertised name configurable in `EmbeddedMusicBleMidiInput`.
- Document the one-active-instance constraint of BLE MIDI examples in the
  showcase README.
- Add tags for package milestones once the SHA-pinned integration settles.

## Deferred Ideas

- Sustain/hold behavior in the monophonic instrument.
- Modulation CC1 mapped to vibrato or timbre.
- Polyphonic buzzer mixing.
- I2S audio backend experiments.
- Sequencer or arpeggiator.
- USB MIDI host on hardware that supports it well.

## Prioritization Rules

- Prefer slices that produce a hardware-observable improvement.
- Prefer contract changes only after at least one producer and one consumer need
  them.
- Keep transport, event contracts, instrument policy, and audio output separate.
- Keep each slice small enough to build, test, document, commit, and review.
- Move speculative ideas down until a concrete test makes them relevant.
