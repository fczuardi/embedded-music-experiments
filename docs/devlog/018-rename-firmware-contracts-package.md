# Slice 018: Rename Firmware Contracts Package

The shared header-only PlatformIO package no longer uses the temporary
`EmbeddedMusic` prefix. Its package name now matches the directory:

- `firmware-contracts`

The public C++ headers and types remain unchanged:

- `NoteEvent.h`
- `PitchBendEvent.h`
- `InstrumentEventSink.h`

This keeps package names in `lib_deps` consistent with the existing kebab-case
package convention used by `ble-midi-input`, `monophonic-instrument`, and
`m5-tone-output`.

Validation targets:

```bash
pio pkg pack . --output /home/fcz/dev/m5stick/.tmp
just showcase-build 1
```

Downstream repositories must pin this commit and consume
`firmware-contracts=...` instead of `EmbeddedMusicFirmwareContracts=...`.
