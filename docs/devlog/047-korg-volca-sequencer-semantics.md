# Korg Volca sequencer semantics

## Goal

Extend the interaction-semantics radar with behaviors from the Korg Volca
family that add distinctions not already captured by the Koala, Roland P-6,
and Pocket Operator comparison.

## Research boundary

Official Korg product documentation was reviewed for Volca Beats, Keys, Drum,
and Sample. The family is recorded as related instruments with model-specific
behavior rather than one uniform sequencer contract.

The strongest additions are:

- Active Step distinguishes a skipped timeline position from a silent rest;
- Step Jump directly intervenes in the current playhead position;
- Flux distinguishes continuous recording from step-quantized capture;
- Step Trigger separates envelope articulation from note content;
- Stutter applies performative trigger repetition;
- per-part choke defines a policy between voices;
- pulse sync demonstrates a minimal external clock boundary.

Swing and motion sequencing already existed in the radar. The Volcas add
supporting evidence rather than duplicate concepts for those behaviors.

## Decision

These behaviors remain external references. The Calculator baseline still uses
sixteen fixed positions containing either a drum trigger or a rest. It does not
need inactive timeline positions, playhead jumps, or continuous performance
recording.

In particular, the research does not introduce `StepState`, a transport API, a
clock package, or timestamped events. Those boundaries require concrete local
experiments before they can become candidates for implementation.

## Verification

The cited official Korg pages and manuals were checked on 2026-09-21. Local
Markdown links and the radar maturity labels were reviewed after the update.
