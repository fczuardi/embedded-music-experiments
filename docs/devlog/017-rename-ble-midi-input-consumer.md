# Slice 017: Rename BLE MIDI Input Consumer

The `midi-receiver` reusable package was renamed from the temporary
`EmbeddedMusicBleMidiInput` name to `BleMidiInput`.

Showcase 1 now consumes the renamed package from the `midi-receiver` commit that
introduced the new package identity. Current architecture docs were updated to
use `BleMidiInput` for the BLE MIDI input package name.

Validation targets:

```bash
just showcase-build 1
```

Older devlog entries keep the historical package names they used at the time.
