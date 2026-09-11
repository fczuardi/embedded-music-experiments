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

The facade was published as `fcz2/amy-synth-m5@0.1.2`, and the showcase
manifest now consumes that exact Registry version. The local package build was
also validated against the package source before publication.

## Verification

The local Core Gray firmware build passed with the updated facade. No new
hardware test was performed in this slice; the previous Showcase 3 hardware
validation remains applicable to the unchanged audio and MIDI behavior.
