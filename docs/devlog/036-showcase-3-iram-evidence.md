# 036. Showcase 3 IRAM evidence

## Goal

Turn the Core Gray AMY IRAM limit into inspectable CI evidence without changing
the published package boundary or requiring connected hardware.

## Instrumentation

After the published Showcase 3 dependency build, CI now reads the linked ELF
and adds two tables to the GitHub Actions job summary:

- allocated IRAM sections and their exact byte counts;
- the largest linked symbols resident in those sections.

The job also uploads the ELF, GNU linker map, Markdown report, and machine-readable
JSON report as a 30-day artifact. The map preserves object and archive provenance
for deeper attribution, while JSON provides a stable input for a later regression
budget or run-to-run comparison.

This deliberately instruments the umbrella showcase rather than changing
`amy-synth-m5`: the baseline remains the real composition using the published
`ble-midi-input` and `amy-synth-m5` packages.

## Scope

This slice measures static linked IRAM only. Runtime heap, stack high-water marks,
DMA allocations, audio continuity, and BLE behavior still require target-side
instrumentation or hardware validation. No optimization is attempted until the
link evidence identifies realistic candidates.

## BLE ablation result

A temporary CI probe rebuilt the same Core Gray, M5Unified, AMY package, patch,
and monophonic voice composition without depending on or initializing
`ble-midi-input`.

| Composition | IRAM used | IRAM free |
|---|---:|---:|
| Published Showcase 3 | 129,811 bytes | 1,261 bytes |
| AMY-only probe | 79,447 bytes | 51,625 bytes |

Removing the BLE path reduced linked IRAM by 50,364 bytes. The result justifies
one focused follow-up experiment to determine whether a BLE-only controller
configuration can recover part of that cost. The temporary probe itself was
removed after its Actions artifacts and result were captured.

## BLE-only configuration result

NimBLE-Arduino 2.5.1 already defines `CONFIG_BTDM_CONTROLLER_MODE_BLE_ONLY`
for the original ESP32. A second temporary CI probe therefore targeted the
remaining source-level options that preserve this MIDI server: it disabled the
unused Central and Observer roles, retained Peripheral and Broadcaster, and
reduced the maximum connection count to one.

| BLE configuration | IRAM used | IRAM free |
|---|---:|---:|
| Current Showcase 3 | 129,811 bytes | 1,261 bytes |
| Minimal NimBLE roles | 129,555 bytes | 1,517 bytes |

The functional role reduction recovered only 256 bytes of IRAM. This is too
small to remove the practical limit. The roughly 50 KB BLE-path cost measured
by the ablation is therefore mostly below the application-facing NimBLE role
configuration, in the ESP32 controller and required BLE infrastructure. A
larger reduction would likely require rebuilding or replacing the precompiled
framework/controller rather than changing the published project packages.
