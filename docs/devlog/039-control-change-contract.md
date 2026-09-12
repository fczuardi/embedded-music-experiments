# Control Change Contract

## Goal

Carry MIDI continuous controllers from a receiver to an instrument without
coupling the shared contract to a particular backend. The first consumer is
the AMY facade, which will interpret CC1 as modulation-wheel input for a
vibrato experiment.

## Design

`ControlChangeEvent` preserves the raw MIDI representation: zero-based channel
0-15, controller 0-127, and value 0-127. `InstrumentEventSink` exposes this as
an optional event because frequency-oriented instruments may have no use for
continuous controllers.

The receiver remains responsible only for parsing and forwarding the event.
The meaning of CC1, including whether it becomes vibrato, remains an AMY
backend decision. No AMY or audio concepts were added to this repository.

## Verification

The native firmware-contracts test now exercises the new event and its raw
fields. The receiver-side forwarding and AMY interpretation are separate
follow-up work; no hardware behavior is claimed by this contract change.
