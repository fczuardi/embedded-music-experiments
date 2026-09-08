# Slice 015: Remove Package Archive Probe

The native `showcases/package-archive-probe` project was useful while the
package archive path was still unproven. It validated that
`monophonic-instrument` could be packed and consumed before the hardware
showcase depended on that package shape.

The BLE MIDI buzzer showcase now consumes the extracted
`monophonic-instrument` and `m5-buzzer-output` archives directly, and the
`monophonic-instrument` repository has its own package consumer checks. Keeping
the extra native probe in this umbrella repo no longer adds useful coverage.

This slice removes the probe showcase and drops showcase id `2` from the
`justfile`. Historical devlog chapters remain as the record of why the probe
existed.

Validation targets:

```bash
just showcase-list
just showcase-build 1
```

Verified result: `just showcase-list` now reports only
`1	ble-midi-buzzer	showcases/ble-midi-buzzer`, and `just showcase-build 1`
passed with the existing split package dependency graph:
`EmbeddedMusicBleMidiInput`, `monophonic-instrument`, `m5-buzzer-output`, and
`M5Unified`.
