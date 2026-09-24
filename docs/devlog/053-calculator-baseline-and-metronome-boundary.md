# Calculator baseline and metronome boundary

## Goal

Synchronize the umbrella architecture notes with the working Calculator drum
sequencer and choose the next experiment that can challenge its timing boundary.

## Calculator evidence

The sibling
[`calculator-face-input`](https://github.com/embedded-music/calculator-face-input)
repository now contains a hardware-validated, self-contained instrument on the
original Core Gray:

- four tracks by sixteen boolean steps;
- continuous 16th-note playback with a visible playhead;
- simultaneous AMY one-shot drum triggers;
- live volume and BPM adjustment under a Core A modifier layer;
- direct assignment of twenty curated drum sounds per track under Core B;
- fixed-size state and no dynamic allocation in event or audio paths.

The final default kit uses Acoustic Snare, Closed Hi-Hat, Splash Cymbal, and Low
Tom. Hardware listening also exposed aliases in AMY's reduced legacy GM drum
kit, reinforcing that the application should curate musical sounds rather than
present the nominal GM table as twenty distinct samples.

This is already a complete single-pattern showcase. It does not yet implement
mute, clear, pattern copy or variation, multiple patterns, persistence, or
chains.

## Boundary decision

The Calculator app has useful local seams: protocol decoding, editor state,
view rendering, a monotonic `StepClock`, and AMY output. Those seams are not yet
shared contracts. In particular, one working clock does not establish whether
the stable abstraction is a step clock, beat clock, transport, scheduler, or a
smaller deadline accumulator.

The next timing experiment will therefore be a focused M5StickC Plus2 metronome
in a sibling `metronome` repository. It can exercise tempo, meter, downbeats,
start/stop policy, two-button gestures, a smaller display, and buzzer output
without also introducing pattern storage or melodic note lifecycles.

The metronome should not begin as an umbrella showcase because its first slices
will contain substantial exploratory application code. The umbrella owns the
composition only after reusable packages make that composition thin.

## Extraction rule

Compare the metronome timing implementation with the Calculator `StepClock`
before extracting either. A shared package becomes justified only when both
consumers reveal the same ownership, phase, catch-up, and tempo-change contract.
Pattern storage and sequencing remain separate questions for a later melodic
sequencer or another complementary consumer.

## Verification

The roadmap and interaction-semantics radar now link the Calculator repository,
describe the validated baseline in the present tense, preserve unimplemented
pattern features as future work, and name the metronome as the next timing
boundary experiment.
