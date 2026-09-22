# Synth sequencer strategies

## Goal

Use the A- and S-tier entries from a video ranking of 25 synth sequencers as a
discovery list, then inspect official manuals for semantics not yet represented
in the interaction radar.

## Scope and method

The ranking itself is editorial rather than technical evidence. Official Yamaha,
Moog, Akai, and Arturia documentation was reviewed for Reface CS/DX, DFAM,
Subharmonicon, APC40 mkII, KeyStep, KeyLab mk3, Grandmother, and Matriarch. The
EP-133 K.O. II was already documented in the preceding research slice.

APC40 mkII and KeyLab mk3 were deliberately classified as controllers rather
than autonomous sequencers. Their relevant contribution is how they project,
transform, and command musical state owned elsewhere.

## Strategies found

- Reface CS/DX uses an ephemeral phrase looper whose first performance defines
  loop length and which supports overdub and optional quantization.
- DFAM advances analog pitch and velocity value lanes whose meanings can be
  changed through routing.
- Subharmonicon drives two value sequences from independently assignable rhythm
  generators, separating stored content from clock pulses.
- APC40 projects a bidirectional RGB viewport over Ableton clips and scenes.
- KeyStep distinguishes rest, retriggered notes, tie, gate percentage, and swing.
- KeyLab composes scale, chord, and arpeggiator transformations and separates
  musical MIDI from DAW-control communication.
- Grandmother distinguishes rest, tie, and legato transition.
- Matriarch allows up to four notes plus articulation data in one step.

## Architectural consequences

The radar now records phrase loopers, record-defined length, volatile sketchpads,
control-value lanes, clock/value decoupling, rhythm generators, remote
projections, controller viewports, bidirectional feedback, clip/scene launch,
transformation pipelines, tie/legato transitions, and chord steps.

The strongest boundary is between rhythm generation and value sequencing. A
sequence can expose its current value and advance only when an independent pulse
source requests it. The most directly applicable UI lesson is that an M5 display
may project and command state without owning it.

No new shared contract is introduced. Drum steps remain boolean in the planned
Calculator baseline, and melodic articulation waits for a real local consumer.

## Verification

The cited manuals and product documentation were reviewed on 2026-09-21. Radar
entries remain external references, while the queued Calculator section change
continues to be the only nearby candidate for a shared timing-related semantic.
