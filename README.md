# Embedded music experiments

Small, open-ended experiments with MIDI, embedded hardware, and simple musical instruments.

This repository is the documentation hub for the experiments. It does not contain a monolithic application or promise a particular final product.

## Components

| Repository | Status | Purpose |
| --- | --- | --- |
| [midi-receiver](https://github.com/fczuardi/midi-receiver) | First milestone complete | Receive BLE MIDI, interpret messages, and make them observable on an M5StickC Plus2 |
| [buzzer-instrument](https://github.com/fczuardi/buzzer-instrument) | Starting | Explore a small musical instrument using a passive buzzer, beginning with the M5StickC Plus2 |

## Showcases

Executable compositions live in `showcases/`. The first one,
`showcases/ble-midi-buzzer/`, combines the BLE MIDI input package with the buzzer
instrument package so an M5StickC Plus2 can act as a small BLE MIDI sound box.

## Design notes

The current direction, boundaries, decisions, and open questions are recorded in [DESIGN.md](DESIGN.md).

The design is intentionally provisional. Shared libraries and additional repositories should emerge from working experiments rather than being designed in advance.

## Shared firmware contracts

The first shared C++ contracts live in `firmware-contracts/include/`. They are
header-only and intentionally small so firmware experiments can include the same
event vocabulary without sharing BLE, display, or audio backend code.

This repository is also a PlatformIO library package. The root `library.json`
points PlatformIO at `firmware-contracts/include/` through `build.includeDir`.

## CI

GitHub Actions validates the shared C++ headers, runs `pio pkg pack`, and builds
the showcase firmware on pushes and pull requests. The workflow lives at
`.github/workflows/ci.yml`.
