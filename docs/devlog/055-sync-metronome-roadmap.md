# Synchronize the metronome roadmap

## Goal

Bring the umbrella roadmap up to the current M5StickC Plus2 metronome baseline
without yet resolving the separate open questions about fractional timing,
long-term drift, or a shared clock contract.

## Updated status

The roadmap previously described the metronome as the next application to
create. The sibling repository now has a hardware-validated baseline with:

- a mutable beat clock and phase-preserving BPM changes;
- visible four-beat position;
- generated PCM clicks and ten selectable recipes;
- live tempo, volume, accent-sound, and regular-sound controls;
- a three-mode two-button interaction with A+B chord suppression;
- local state, input, display, audio, clock, and sound-catalog boundaries.

The roadmap now describes those capabilities in the present tense and keeps
transport and meter explicitly open.

## Current cross-repository boundary

The Calculator and metronome clocks have been compared but do not yet justify a
shared timing package. Their differences remain experimental policy choices.

The stronger immediate boundary finding is in audio lifecycle. The metronome
showed that restarting PCM after speaker idle can add a physical transient, and
that a silent keep-alive channel prevents it. Investigation and possible API
ownership now belong to `monophonic-instrument` / `m5-tone-output`; the umbrella
roadmap records that direction without declaring the experimental workaround a
finished package feature.

## Deferred considerations

This synchronization intentionally does not yet add conclusions about integer
interval truncation, fractional deadlines, long-term drift, or a preferred
tempo-change policy. Those remain separate timing-design work following the
current PCM idle-policy investigation.

## Verification

Review `docs/ROADMAP.md` and confirm that:

1. the Calculator and metronome both appear as completed application baselines;
2. the metronome is no longer described as a repository that still needs to be
   created;
3. transport and meter remain open work;
4. clock extraction remains deferred;
5. PCM idle behavior is identified as the immediate package-boundary probe.
