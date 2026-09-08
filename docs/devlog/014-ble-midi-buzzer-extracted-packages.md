# Slice 014: BLE MIDI Buzzer Extracted Packages

The first BLE MIDI buzzer showcase was still consuming the legacy combined
`EmbeddedMusicBuzzerInstrument` package. That package bundled the shared
monophonic policy and the M5StickC Plus2 buzzer output backend together.

The `monophonic-instrument` repository now publishes those pieces as separate
archives:

- `monophonic-instrument`
- `m5-buzzer-output`

This slice updates `showcases/ble-midi-buzzer` to consume both archives
explicitly while keeping the existing BLE MIDI input package unchanged. The
firmware source did not need structural changes because it already composed the
same runtime objects:

```text
BleMidiInput -> MonophonicInstrumentSink -> SpeakerToneOutput
```

The local archive paths are intentional for this migration stage:

```ini
lib_deps =
  EmbeddedMusicBleMidiInput=https://github.com/fczuardi/midi-receiver.git#60fce82734d3a81f659c15de2f8ee0b7d97c20ff
  monophonic-instrument=file:///home/fcz/dev/m5stick/.tmp/monophonic-instrument-0.1.0.tar.gz
  m5-buzzer-output=file:///home/fcz/dev/m5stick/.tmp/m5-buzzer-output-0.1.0.tar.gz
```

Consumers list both packages explicitly because local and archive package
dependencies cannot yet rely on a stable registry or release URL for the shared
policy package.

Validation sequence:

```bash
cd /home/fcz/dev/m5stick/monophonic-instrument
pio pkg pack packages/monophonic-instrument --output /home/fcz/dev/m5stick/.tmp
pio pkg pack packages/m5-buzzer-output --output /home/fcz/dev/m5stick/.tmp

cd /home/fcz/dev/m5stick/embedded-music-experiments
just showcase-build 1
```

Verified result: `just showcase-build 1` passed. PlatformIO installed
`monophonic-instrument@0.1.0` and `m5-buzzer-output@0.1.0` from the local
archives, compiled `libmonophonic-instrument.a` and `libm5-buzzer-output.a`,
and linked the M5StickC Plus2 showcase firmware successfully.
