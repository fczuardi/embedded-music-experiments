# Rename Firmware Contracts Consumers

## Goal

Finish the package rename slice across the active showcase dependency graph:
`EmbeddedMusicFirmwareContracts` is now `firmware-contracts`.

## Design

The umbrella repo owns the renamed `firmware-contracts` package. Downstream
packages were updated first:

- `midi-receiver` now publishes `ble-midi-input` with a dependency on
  `firmware-contracts` at umbrella commit `c9bde598cff9`.
- `monophonic-instrument` now publishes `monophonic-instrument` with the same
  renamed dependency.

Showcase 1 now pins `ble-midi-input` to receiver commit `a58c1119`, the commit
that consumes the renamed package. It also uses the current local
`m5-tone-output-0.1.2.tar.gz` archive while continuing to consume the refreshed
`monophonic-instrument-0.1.1.tar.gz` archive.

The C++ type names and include paths were not changed in this slice.

## Verification

Command run:

```bash
just showcase-build 1
```

The showcase build passed after clearing stale PlatformIO `libdeps`. The
dependency graph showed `ble-midi-input@0.1.1+sha.a58c111`,
`firmware-contracts@0.1.0+sha.c9bde59`, `monophonic-instrument@0.1.1`, and
`m5-tone-output@0.1.2`.

No hardware upload is required for this package-name plumbing slice.
