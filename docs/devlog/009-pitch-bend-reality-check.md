# Slice 009: Pitch Bend Reality Check

After pitch bend reached the shared contract, we tried to make it audible in the
BLE MIDI buzzer showcase. The first implementation proved that pitch could move,
but hardware testing showed it was not playable.

Dragging the Arturia touch strip produced a backlog effect: after a key was
released, the buzzer kept chasing old pitch positions for seconds before the
note finally stopped. That made the instrument feel like it was replaying the
past instead of responding in real time.

We tested several hypotheses:

- coalesce pitch bend events after receiver callbacks;
- prioritize Note Off over queued bend values;
- drain more messages from the MIDI parser each loop;
- sample pitch bend in an instrument runtime;
- remove serial logging from the hot path;
- ignore pitch bend before it reached the instrument;
- disable the receiver's pitch bend callback.

The critical result was the last pair of tests: even when pitch bend was not
audible and was not delivered to the instrument, moving the strip still delayed
Note Off. That places the backlog below our instrument boundary, likely in the
Android bridge route, BLE-MIDI byte FIFO, or MIDI parser consumption path.

The conclusion is not that `PitchBendEvent` was a bad contract. It remains a
useful semantic event. The conclusion is that audible pitch bend through this
specific transport path is not ready to be a near-term feature. We are moving it
back to research and restoring the showcase to the simpler, validated sound-box
behavior: notes, velocity, panic, disconnect cleanup, and modular composition.
