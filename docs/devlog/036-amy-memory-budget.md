# 036. AMY memory budget

## Goal

Turn the Core Gray AMY resource observation into a concrete guard before
adding more engine features.

## Baseline

The published Showcase 3 build using `amy-synth-m5@0.2.8` currently measures:

| Region | Used | Budget | Remaining budget |
| --- | ---: | ---: | ---: |
| IRAM | 130971 bytes | 130971 bytes | 0 bytes |
| DRAM | 62864 bytes | 65536 bytes | 2672 bytes |
| Firmware image | 1230944 bytes | 1300000 bytes | 69056 bytes |

The IRAM budget is the exact measured size of the validated BLE composition:
there is no capacity for IRAM growth in this configuration. The DRAM and image
limits leave useful room for ordinary maintenance while making large
dependency or feature additions visible in CI.

## Enforcement

`scripts/check-amy-memory-budget.sh` builds Showcase 3, extracts the PlatformIO
memory report, prints the measured values, and fails if a limit is exceeded.
The GitHub Actions Showcase 3 job uses this check instead of an unbounded build.

## Verification

```sh
just showcase-budget
```

The check passed locally after resolving `fcz2/amy-synth-m5@0.2.8` and
`fcz2/ble-midi-input@0.3.0` from the PlatformIO Registry. No hardware behavior
was changed or revalidated in this documentation and tooling slice.
