# Embedded music experiments

Small, open-ended experiments with MIDI, embedded hardware, and simple musical instruments.

This repository is the documentation hub for the experiments. It does not contain a monolithic application or promise a particular final product.

## Components

| Repository | Status | Purpose |
| --- | --- | --- |
| [midi-receiver](https://github.com/fczuardi/midi-receiver) | First milestone complete | Receive BLE MIDI, interpret messages, and make them observable on an M5StickC Plus2 |
| [monophonic-instrument](https://github.com/fczuardi/monophonic-instrument) | Two-hardware milestone complete | Provide shared monophonic policy and M5 audio output backends |
| [amy-synth-m5](https://github.com/fczuardi/amy-synth-m5) | AMY package and showcase validated | Provide AMY musical-control and Core Gray PCM bridge components |

## Showcases

Executable compositions live in `showcases/`.

- `showcases/ble-midi-buzzer/` combines BLE MIDI input, the monophonic
  instrument policy, and the M5StickC Plus2 buzzer output.
- `showcases/ble-midi-core-gray-speaker/` uses the same input and instrument
  policy with the M5Stack Core Gray speaker output.
- `showcases/ble-midi-amy/` composes BLE MIDI input with the AMY synth package
  and the Core Gray PCM speaker bridge.

Run `just showcase-list` to see the numeric showcase IDs used by the build,
upload, and monitor recipes.

## Design notes

The current direction, boundaries, decisions, and open questions are recorded in [DESIGN.md](DESIGN.md).
Near-term priorities are tracked in [docs/ROADMAP.md](docs/ROADMAP.md), while
lower-certainty follow-up ideas live in [docs/BACKLOG.md](docs/BACKLOG.md).

The design is intentionally provisional. Shared libraries and additional repositories should emerge from working experiments rather than being designed in advance.

## Shared firmware contracts

The first shared C++ contracts live in `firmware-contracts/include/`. They are
header-only and intentionally small so firmware experiments can include the same
event vocabulary without sharing BLE, display, or audio backend code.

This repository is also a PlatformIO library package. The root `library.json`
points PlatformIO at `firmware-contracts/include/` through `build.includeDir`.

## CI

GitHub Actions validates the shared C++ headers, runs `pio pkg pack`, and builds
the three M5StickC Plus2/Core Gray showcases on pushes and pull requests. The
workflow lives at `.github/workflows/ci.yml`.

## Local PlatformIO Cache

Sibling firmware repositories share the parent workspace cache at
`../.platformio-home` when checked out side by side. Each PlatformIO project
records this with a relative `core_dir` in its `platformio.ini`; the local
recipes therefore do not depend on a particular machine username or checkout
root.
