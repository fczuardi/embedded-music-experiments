# Behringer Crave melodic-step semantics

## Goal

Extend the interaction-semantics radar beyond drum and sample sequencing by
examining what a compact monophonic melodic sequencer stores and performs.

## Research boundary

The official Behringer Crave Quick Start Guide and product overview were
reviewed on 2026-09-21. The confirmed sequencer vocabulary includes notes,
rests, gate length, accent, ratchet, four editing pages, a configurable pattern
end, playhead reset and hold, banks and patterns, and an arpeggiator with several
traversal orders.

The synth has glide/portamento, but the reviewed documentation does not justify
claiming programmable tie or slide semantics for each sequencer step. Those
terms were deliberately excluded from the confirmed comparison.

## Findings

A one-shot drum step can be represented initially by the presence or absence of
a track trigger. A melodic step needs at least a choice between note and rest;
a note may additionally carry pitch, gate length, accent, and ratchet behavior.

The Crave also exposes keyboard CV and gate as separate physical outputs. This
supports the conceptual separation between pitch state and voice articulation:
the same pitch can receive multiple gates, and a rest can close the gate without
requiring a new pitch value.

Editing pages, logical pattern length, stored pattern selection, and musical
sections are related navigation concepts but not synonyms. Likewise, the
arpeggiator generates a traversal from held notes rather than replaying the
literal content of a recorded pattern.

## Decision

The new concepts remain research references. No universal `Step` type, melodic
sequencer, transport contract, or arpeggiator API is introduced.

The Calculator drum sequencer baseline remains unchanged: four tracks, sixteen
fixed positions, and boolean one-shot drum triggers. A future melodic consumer
must exist before deciding whether patterns can share a generic container or
should keep distinct `DrumStep` and `MonophonicNoteStep` models.

## Verification

The radar entries were checked against the cited official sources, and the
documentation was reviewed to ensure that external behavior, local evidence,
and possible future abstractions remain separately labeled.
