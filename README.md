# Embedded music experiments

Small, open-ended experiments with MIDI, embedded hardware, and simple musical instruments.

This repository is the documentation hub for the experiments. It does not contain a monolithic application or promise a particular final product.

## Components

| Repository | Status | Purpose |
| --- | --- | --- |
| [midi-receiver](https://github.com/fczuardi/midi-receiver) | First milestone complete | Receive BLE MIDI, interpret messages, and make them observable on an M5StickC Plus2 |
| [buzzer-instrument](https://github.com/fczuardi/buzzer-instrument) | Starting | Explore a small musical instrument using a passive buzzer, beginning with the M5StickC Plus2 |

## Design notes

The current direction, boundaries, decisions, and open questions are recorded in [DESIGN.md](DESIGN.md).

The design is intentionally provisional. Shared libraries and additional repositories should emerge from working experiments rather than being designed in advance.
