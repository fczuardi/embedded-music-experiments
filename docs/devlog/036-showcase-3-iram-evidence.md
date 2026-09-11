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
