# Slice 012: Monophonic Package Archive Probe

The `monophonic-instrument` repository now contains
`packages/monophonic-instrument`, a first subpackage extracted from the old
buzzer instrument. Local folder consumption with `file://` proved that the
subpackage has a valid `library.json`, but it did not prove the distribution
shape that published showcases will need.

This slice adds a tiny native showcase probe:

```text
showcases/package-archive-probe/
```

The probe consumes the packed `monophonic-instrument` tarball through
PlatformIO `lib_deps`:

```ini
lib_deps =
  monophonic-instrument=file:///home/fcz/dev/m5stick/.tmp/monophonic-instrument-0.1.0.tar.gz
```

That deliberately mirrors the future remote-release form:

```ini
lib_deps =
  monophonic-instrument=https://github.com/fczuardi/monophonic-instrument/releases/download/v0.1.0/monophonic-instrument-0.1.0.tar.gz
```

The probe is intentionally not a firmware showcase. It only verifies that an
external PlatformIO project can install the archive, include
`MonophonicInstrument.h`, compile the package sources, and link a minimal
consumer.

Validation sequence:

```bash
cd /home/fcz/dev/m5stick/monophonic-instrument
pio pkg pack packages/monophonic-instrument --output /home/fcz/dev/m5stick/.tmp

cd /home/fcz/dev/m5stick/embedded-music-experiments
just showcase-build 2
```

Verified result: `just showcase-build 2` installed `monophonic-instrument` from the local tarball, compiled the package sources, linked the native probe, and passed. The probe uses `-pipe` because this workspace has already hit `/tmp` quota limits during PlatformIO builds.

This closes the local archive part of the packaging risk. The next packaging
slice should attach the same tarball shape to a GitHub Release and switch this
probe from `file:///home/fcz/dev/m5stick/.tmp/...` to the release URL before
the real BLE showcases depend on the new packages.
