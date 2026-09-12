# AMY 1.2.159 Package Propagation

## Goal

Move Showcase 3 from the earlier published packages to the validated
`amy-synth-m5@0.2.8` and `ble-midi-input@0.4.0`, which use AMY `1.2.159`, the
corrected `monophonic-instrument@0.1.5` dependency, and the current firmware
contracts.

## Distribution finding

The first AMY package publication attempt exposed a transitive dependency
problem. `monophonic-instrument@0.1.4` still selected the older
`firmware-contracts` package, which did not contain `ControlChangeEvent`.
The monophonic package was corrected and published as `0.1.5`; AMY was then
published as `0.2.8` with that dependency.

This keeps package consumption remote and reproducible. The umbrella does not
check out sibling repositories or use machine-local paths for Showcase 3.

## Resource decision

The AMY upgrade was already measured on the Core Gray BLE composition:

- IRAM: 130971 of 131072 bytes, 101 bytes physically free;
- DRAM: 62864 bytes;
- firmware image: 1230944 bytes.

The CI guard uses `130971` as the IRAM budget for this known-good firmware.
This is a zero-growth budget, so future AMY or BLE changes must first be
treated as measured experiments rather than ordinary feature additions.

## Verification

The AMY package native tests, isolated package consumer, and package
publication workflow passed. Showcase 3 now resolves the published AMY package
version in its PlatformIO manifest. No new hardware validation is claimed in
this propagation slice; the same AMY `1.2.159` dual-channel firmware was
previously validated on the physical Core Gray.
