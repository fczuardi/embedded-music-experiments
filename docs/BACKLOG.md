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

## Pitch Bend Transport Research

Audible pitch bend is intentionally deprioritized until the transport behavior
is better understood. Hardware tests with an Arturia controller routed through
Android USB MIDI to BLE MIDI showed that pitch-strip movement can delay Note Off
by seconds.

Attempts above the BLE-MIDI library did not solve the problem:

- coalescing pending pitch bend events in the receiver;
- draining more MIDI parser messages per update;
- sampling pitch bend in an instrument runtime;
- removing serial pitch bend logs;
- ignoring pitch bend before it reached the instrument;
- disabling the receiver pitch bend callback.

The delay persisted even when pitch bend was not audible and was not delivered
to the instrument. That points to backlog inside the bridge, BLE-MIDI byte FIFO,
or MIDI parser before our semantic event boundary.

Future research options:

- test a different BLE MIDI bridge or controller path;
- inspect whether the Android bridge can reduce pitch bend rate;
- prototype a raw BLE-MIDI packet parser that preserves Note On/Off while
  dropping or sampling pitch bend before it enters a byte FIFO;
- compare with a non-BLE or direct hardware MIDI path before changing the shared
  event contract.
