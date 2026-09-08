# Roadmap After the Two-Hardware Baseline

## Context

The first project cycle proved that an Arturia controller can give musical
purpose to two previously unused ESP32 gadgets. The same packaged contracts,
BLE MIDI input, and monophonic policy now drive the M5StickC Plus2 buzzer and the
M5Stack Core Gray speaker.

The working route still uses Android to bridge the Arturia's USB-only MIDI
output to BLE MIDI. Since the phone could also synthesize sound itself, the
current system is not presented as a necessary consumer product. Its value is
physicality, reuse, playful limitation, and the learning produced by making
small hardware objects musical.

## Two Independent Directions

Input autonomy and sound generation are separate problems.

Direct USB MIDI host support remains desirable, but the smallest likely path
depends on future ESP32-S3 hardware that is not currently available. Using the
available Heltec boards would probably require a multi-board composition and a
larger block of project time. That direction is therefore deferred without
being abandoned.

The active bench is ready for audio-engine probes. Rather than rebuilding
well-known synthesis techniques, future slices may evaluate AMY, ESP32Synth,
TinySoundFont, Mozzi, and Faust as Open Source dependencies or generated DSP.
They serve different purposes and are not expected to share one adapter in
advance.

## Boundary Decision

The current `VoiceOutput` remains the intentionally small backend for
`MonophonicInstrumentSink`. A complete engine may instead implement
`InstrumentEventSink` directly so it can preserve native polyphony, voice
allocation, envelopes, patches, and effects.

No generic PCM interface is added in this slice. A real engine integration must
first expose whether a reusable render-source or audio-sink boundary is needed.

## Near-Term Direction

AMY is the suggested first probe because it provides a mature polyphonic engine,
presets, synthesis methods, effects, Arduino support, and access to rendered PCM
blocks. The proposal is intentionally incremental: compile it for the Core Gray,
produce local sound without BLE, test a small chord, and only then adapt shared
instrument events.

This slice changes documentation only. It consolidates direction after a stable
milestone and does not commit the project to AMY or any other engine.
