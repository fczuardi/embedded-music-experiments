# Backlog

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
notes without requiring a BLE disconnect or local panic button.
