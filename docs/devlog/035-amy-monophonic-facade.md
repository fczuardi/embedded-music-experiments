# 035. AMY monophonic facade

## Goal

Make the simple AMY showcase communicate a simple composition. The application
should not need to assemble the runtime, slot, speaker bridge, activity gate,
and AMY instrument sink itself.

## Change

Showcase 3 now uses `AmyM5MonophonicSynth` as both its AMY instrument and its
`InstrumentEventSink`. The facade represents the chosen defaults explicitly:
one M5 speaker output and a monophonic AMY instrument. It hides the fact that
AMY pitch bend is global, which is not useful information for this single
instrument composition, while retaining the lower-level APIs in the package.

The showcase manifest still points to `fcz2/amy-synth-m5@0.1.1` until the new
facade version is published. The local package build was validated against
`amy-synth-m5` 0.1.2 before this documentation was written.

## Verification

The local Core Gray firmware build passed with the updated facade. No new
hardware test was performed in this slice; the previous Showcase 3 hardware
validation remains applicable to the unchanged audio and MIDI behavior.
