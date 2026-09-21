# Interaction semantics radar

## Goal

Preserve the design vocabulary uncovered while comparing the planned
Calculator drum sequencer with established sampler and sequencer behavior,
without turning that research into premature shared APIs or roadmap promises.

## Decision

The umbrella owns a new interaction-semantics radar because trigger, gate,
playback policies, step expression, and transport cross repository boundaries.
Individual experiment repositories should record only the subset that affects
their concrete interaction.

The radar distinguishes external references, observations in our hardware,
candidates, locally adopted behavior, extracted contracts, and deferred ideas.
It records official Koala, Roland P-6, and Teenage Engineering Pocket Operator
documentation alongside explicit inferences for our architecture. Pocket
Operators are treated as a family with a recurring 16-step workflow and
model-specific semantics, not as one uniform contract.

The comparison currently supports a boundary between:

- sequencer decisions such as probability, micro-timing, and sub-steps;
- musical events such as trigger or gate;
- voice policies such as one-shot, loop, choke, envelope, and polyphony.

The Pocket Operator comparison also records parameter locks, punch-in effects,
accent, swing, pattern chains, and the reuse of one 16-key grid through modes.
The PO-32, PO-33, and PO-20 demonstrate distinct drum-synthesis, sample-slicing,
and harmonic workflows on that common physical vocabulary.

No new C++ contract or package is introduced. `TriggerEvent` remains a possible
name rather than an approved API.

## Verification

This documentation-only slice was checked by reviewing local Markdown links,
the maturity labels for current experiments, and the cited official product
documentation on 2026-09-21.

## Consequence

The umbrella now has a durable place for comparative research. The Calculator
sequencer can start with boolean steps and one-shot drum triggers while richer
step expression remains visible without expanding the first implementation.
