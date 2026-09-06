# Slice 001: Shared Instrument Contracts

The MIDI receiver and buzzer instrument now both have concrete code that wants
to talk about the same thing: typed musical note events. This is the first point
where a shared contract is justified by real consumers instead of by guesswork.

This slice creates `firmware-contracts/include/` as a small header-only area for
embedded C++ contracts. It starts with two files:

- `NoteEvent.h`: describes Note On and Note Off using channel, note, and
  velocity.
- `InstrumentEventSink.h`: describes the input boundary that a receiver or local
  test producer can call.

The contract deliberately excludes BLE details, M5 display code, speaker output,
Control Change, Pitch Bend, sustain, sequencing, and timing. Those concepts can
be added later as separate contracts when a real integration slice needs them.

The next slices should migrate the two existing firmware projects one at a
time. `buzzer-instrument` can consume these headers first because it already has
an `InstrumentEventSink` implementation. `midi-receiver` can then produce the
same `NoteEvent` type from its parsed BLE MIDI input.

This repository now has a minimal GitHub Actions workflow. The workflow compiles
small C++ programs that include the shared headers and exercise their basic
shape. It is not a firmware build; it only guards the shared contract syntax and
interface boundary.

Local verification mirrors CI:

```bash
g++ -std=c++17 -Ifirmware-contracts/include -Wall -Wextra -Werror /tmp/check_note_event.cpp -o /tmp/check_note_event
g++ -std=c++17 -Ifirmware-contracts/include -Wall -Wextra -Werror /tmp/check_instrument_event_sink.cpp -o /tmp/check_instrument_event_sink
```
