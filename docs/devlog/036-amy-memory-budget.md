# 036. AMY memory budget

## Goal

Turn the Core Gray AMY resource observation into a concrete guard before
adding more engine features.

## Baseline

The published Showcase 3 build currently measures:

| Region | Used | Budget | Remaining budget |
| --- | ---: | ---: | ---: |
| IRAM | 129811 bytes | 130048 bytes | 237 bytes |
| DRAM | 60808 bytes | 65536 bytes | 4728 bytes |
| Firmware image | 1219040 bytes | 1300000 bytes | 80960 bytes |

The IRAM budget preserves at least 1 KiB below the ESP32 IRAM capacity. The
DRAM and image limits leave useful room for ordinary maintenance while making
large dependency or feature additions visible in CI.

## Enforcement

`scripts/check-amy-memory-budget.sh` builds Showcase 3, extracts the PlatformIO
memory report, prints the measured values, and fails if a limit is exceeded.
The GitHub Actions Showcase 3 job uses this check instead of an unbounded build.

## Verification

```sh
just showcase-budget
```

The check passed locally after resolving `fcz2/amy-synth-m5@0.1.2` and
`fcz2/ble-midi-input@0.3.0` from the PlatformIO Registry. No hardware behavior
was changed or revalidated in this documentation and tooling slice.
