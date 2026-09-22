# Calculator pattern terminology

## Goal

Keep umbrella research aligned with the Calculator drum sequencer after naming
its four-track, sixteen-step block before implementation begins.

## Decision

The Calculator app calls each instrument row a **track** and the complete block
a **pattern**. The earlier term **section** implied a role in song form that the
baseline does not yet represent.

The radar keeps distinct meanings for nearby concepts:

- pattern owns musical events or steps;
- page is an editing viewport;
- scene combines independently selectable patterns or clips;
- section may describe a structural role such as verse or chorus;
- song orders material over time.

References to the planned Calculator behavior now use current and queued
patterns. External products retain their own documented vocabulary.

## Consequence

The queued pattern change remains a local candidate for a quantized command,
because it is requested during playback and applied at the next sixteen-step
boundary. This terminology change introduces no shared contract and does not
alter the planned interaction or storage limits.

## Verification

Calculator-specific references in the interaction radar and recent research
devlogs were reviewed for consistency. Generic or product-specific uses of
scene, section, page, and pattern were deliberately preserved.
