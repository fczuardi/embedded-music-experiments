# Slice 005: Showcase Volume Calibration

The buzzer package now exposes a configurable velocity-to-volume range. This
slice updates the BLE MIDI buzzer showcase to consume that package version and
sets the range locally in the showcase firmware, for example, we can change the
default values from 64-128 to something else like 96-136 with a line like this:

```cpp
constexpr VelocityVolumeRange SHOWCASE_VELOCITY_VOLUME_RANGE = {96, 136};
```

This keeps calibration fast. To try different limits, edit that constant and
run:

```bash
just showcase-upload
```

No package commit or SHA update is needed for each calibration attempt. The
range still belongs to `SpeakerToneOutput`; the showcase only chooses values for
this specific hardware test.

The firmware logs the selected minimum and maximum volume on boot so serial
captures can be tied back to the tested range.
