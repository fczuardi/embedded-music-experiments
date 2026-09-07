# Backlog

Prioritized near-term work is tracked in [ROADMAP.md](ROADMAP.md). This file
keeps lower-certainty ideas and notes that may become roadmap slices later.

## MIDI Panic and Cleanup Events

Support standard MIDI cleanup messages in a future contract or transport slice:

- CC 120: All Sound Off
- CC 123: All Notes Off

These messages should not be folded into `NoteEvent`, because they are not note
press/release events. A future design can add a separate typed event or sink
method that lets instruments silence active output without pretending a
disconnect happened.

The BLE MIDI buzzer showcase exposed why this matters: if an upstream bridge can
send CC 120 or CC 123 when a route breaks, the receiver could recover from stuck
notes without requiring the local panic button that is now validated in the
showcase.

## Pitch Bend Route Compatibility

Pitch bend is back on the near-term roadmap, but route compatibility remains a
known risk. Hardware tests with an Arturia controller routed through Android USB
MIDI to BLE MIDI in My MIDI Hub showed that pitch-strip movement can delay Note
Off by seconds.

Attempts above the BLE-MIDI library did not solve the problem:

- coalescing pending pitch bend events in the receiver;
- draining more MIDI parser messages per update;
- sampling pitch bend in an instrument runtime;
- removing serial pitch bend logs;
- ignoring pitch bend before it reached the instrument;
- disabling the receiver pitch bend callback.

The delay persisted even when pitch bend was not audible and was not delivered
to the instrument. Later comparative tests narrowed the problem:

- Arturia USB OTG -> Android My MIDI Hub -> BLE MIDI -> showcase: Note Off
  delays when the physical pitch strip is used.
- Android SynthBridge -> BLE MIDI -> showcase: Note Off remains immediate while
  using the on-screen pitch bend strip.
- Arturia USB OTG -> Android SynthBridge Pro Trial -> BLE MIDI -> showcase:
  Note Off remains immediate while using the Arturia physical pitch strip.

That points to My MIDI Hub's USB-to-BLE bridge path as the likely problematic
route, not to BLE MIDI, Android USB OTG, the Arturia strip, or the showcase
architecture in general.

Future research options:

- inspect whether the Android bridge can reduce pitch bend rate;
- prototype a raw BLE-MIDI packet parser that preserves Note On/Off while
  dropping or sampling pitch bend before it enters a byte FIFO if the problem
  appears outside My MIDI Hub;
- compare with a non-BLE or direct hardware MIDI path before changing the shared
  event contract.
