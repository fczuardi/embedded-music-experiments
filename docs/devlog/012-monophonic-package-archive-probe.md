# Slice 012: Monophonic Package Archive Probe

The `monophonic-instrument` repository now contains
`packages/embedded-music-monophonic`, a first subpackage extracted from the old
buzzer instrument. Local folder consumption with `file://` proved that the
subpackage has a valid `library.json`, but it did not prove the distribution
shape that published showcases will need.

This slice adds a tiny native showcase probe:

```text
showcases/package-archive-probe/
```

The probe consumes the packed `EmbeddedMusicMonophonic` tarball through
PlatformIO `lib_deps`:

```ini
lib_deps =
  EmbeddedMusicMonophonic=file:///tmp/EmbeddedMusicMonophonic-0.1.0.tar.gz
```

That deliberately mirrors the future remote-release form:

```ini
lib_deps =
  EmbeddedMusicMonophonic=https://github.com/fczuardi/monophonic-instrument/releases/download/v0.1.0/EmbeddedMusicMonophonic-0.1.0.tar.gz
```

The probe is intentionally not a firmware showcase. It only verifies that an
external PlatformIO project can install the archive, include
`MonophonicInstrument.h`, compile the package sources, and link a minimal
consumer.

Validation sequence:

```bash
cd /home/fcz/dev/m5stick/monophonic-instrument
pio pkg pack packages/embedded-music-monophonic --output /tmp

cd /home/fcz/dev/m5stick/embedded-music-experiments
just showcase-build 2
```

Verified result: `just showcase-build 2` installed `EmbeddedMusicMonophonic` from the local tarball, compiled the package sources, linked the native probe, and passed. The probe uses `-pipe` because this workspace has already hit `/tmp` quota limits during PlatformIO builds.

This closes the local archive part of the packaging risk. The next packaging
slice should attach the same tarball shape to a GitHub Release and switch this
probe from `file:///tmp/...` to the release URL before the real BLE showcases
depend on the new packages.
