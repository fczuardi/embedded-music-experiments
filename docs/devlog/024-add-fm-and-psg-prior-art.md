# Add FM and Physical PSG Prior Art

Two additional projects expand the audio-engine survey without changing its
near-term priority.

`marcel-licence/esp32_fm_synth` is close to the desired behavior of a complete
ESP32 instrument: six-voice FM synthesis, four operators per voice, patches on
MIDI channels, envelopes, expression, effects, and voice stealing. The original
project is explicitly outdated and points to `ml_synth_fm_example`, whose public
documentation is still sparse. Toolchain compatibility and the combination of
GPL-3.0 with an additional commercial-use note must be understood before any
integration or redistribution.

`Andy4495/AY3891x` belongs to a different category. It controls a physical
AY-3-8910/8912 or compatible PSG rather than rendering samples for an existing
M5 speaker. The library is portable and MIT-licensed, but a working instrument
would also need the sound chip, clock, many GPIO connections, and analog audio
hardware.

The roadmap keeps AMY as the suggested first software-engine probe. The FM
projects remain lower-priority implementation references, while AY3891x opens a
future external vintage sound-chip track. This slice changes documentation only.
