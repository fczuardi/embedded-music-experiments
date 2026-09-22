# EP-133 composition hierarchy

## Goal

Study the Teenage Engineering EP-133 K.O. II for composition and performance
semantics that are not visible in a minimal drum step sequencer.

## Findings

The official guide separates project, group, pattern, scene, and song position.
A scene combines group-specific patterns, while song positions reference scenes.
Their duration follows the longest pattern in the scene.

Commit preserves the current arrangement as a scene and starts a new variation
from it without stopping playback. This is a creative checkpoint and
duplicate-and-continue operation rather than only a storage command.

The device also distinguishes parameter scopes, latching pattern automation,
selective quantization, free-time recording, undo, and immediate versus
bar-quantized loop exit. Its oneshot, key, and legato sample modes show that
duration, polyphony, and retrigger behavior are independent voice policies.

## Decision

The radar now records composition hierarchy, commit/variation, scene-duration
policy, parameter scope, retrigger versus legato continuation, selective
quantization, undo, loop windows, quantized commands, and pressure-sensitive
effects.

These remain reference concepts. The Calculator baseline still stores four
tracks directly inside each fixed-length pattern. Its queued pattern change is
the only current candidate for the more general quantized-command semantic.

## Verification

The EP-133 workflow, modes, play-and-record, functions, and effects chapters
were reviewed on 2026-09-21. The radar distinguishes documented device behavior
from architectural inferences and does not introduce a shared API.
