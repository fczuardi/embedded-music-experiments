# Tiny sequencer strategies

## Goal

Use Floyd Steinberg's *Tiny Sequencers Compared* video as a discovery index for
compact instruments that address limited controls and displays with different
sequencing models.

## Method

The video supplied the candidate list. Technical behavior was checked against
project manuals and product documentation for Wavy Industries Monkey,
picoTracker, RetroKits RK-008, MicroDexed Touch, Woovebox, and Donner MEDO.

The Elecrow Raspberry Pi computer was classified as a host platform. Geonkick,
Surge XT, ZynAddSubFX, and TAL Noisemaker were classified as sound engines or
software instruments in this context, not sequencer workflows.

## Strategies found

- Monkey captures a fixed 16-beat loop through overdub checkpoints and uses
  MIDI channels for mute and coarse erase.
- picoTracker composes references from song channels to chains and phrases,
  with reusable command tables for automation and effects.
- RK-008 captures free MIDI performance, keeps tracks independent from MIDI
  channels, applies realtime modifiers nondestructively, and materializes them
  through mixdown.
- MicroDexed Touch runs an LSDJ-inspired pattern/chain sequencer and a direct
  LiveSequencer in parallel against shared sound engines.
- Woovebox gives steps conditionals, modifiers, probability, generation, and
  randomization.
- MEDO combines a modal multirole looper with discrete and motion-based gesture
  control.

## Architectural consequences

The survey argues against a universal sequencer API. A tracker, overdub looper,
realtime MIDI recorder, and conditional groovebox may share clock or sound
outputs while retaining fundamentally different editing and storage models.

New radar concepts include tracker hierarchy, reusable command tables, overdub
checkpoints, nondestructive modifiers followed by mixdown, track/channel
independence, parallel sequencer models, conditional/generative steps, and
gesture mapping.

None is promoted to a shared contract. The Calculator app remains a deliberately
small drum grid and can reveal its own stable needs through hardware use.

## Verification

Sources were reviewed on 2026-09-21. The radar labels all additions as external
references and separates the video's discovery role from technical evidence in
official or project-owned documentation.
