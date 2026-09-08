# Slice 013: Short Package Names

The first monophonic package archive probe used the name
`EmbeddedMusicMonophonic`, matching the earlier `EmbeddedMusic...` package
style. During the repository reorganization, that naming started to feel too
heavy because `embedded-music` is still a provisional umbrella name rather than
a settled namespace.

This slice updates the umbrella probe to consume the renamed package archive:

```ini
lib_deps =
  monophonic-instrument=file:///home/fcz/dev/m5stick/.tmp/monophonic-instrument-0.1.0.tar.gz
```

The dependency still uses an explicit local alias so the showcase documents the
expected installed package name for the archive. Longer-term namespacing can
come from PlatformIO Registry ownership, such as `fczuardi/monophonic-instrument`,
if these packages are published there later.

This is only a naming cleanup. It does not change the BLE MIDI buzzer showcase
or move any hardware output backend.

Validation sequence:

```bash
cd /home/fcz/dev/m5stick/monophonic-instrument
pio pkg pack packages/monophonic-instrument --output /home/fcz/dev/m5stick/.tmp

cd /home/fcz/dev/m5stick/embedded-music-experiments
just showcase-build 2
```
