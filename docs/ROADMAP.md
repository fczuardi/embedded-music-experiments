# Roadmap

This roadmap tracks small experiments across `embedded-music-experiments`,
`midi-receiver`, and `monophonic-instrument`. It favors hardware evidence and
reversible probes over feature accumulation.

## Stable Baseline: Two-Hardware BLE MIDI Instrument

The current baseline turns MIDI events into audible monophonic performance on
two physical devices:

- M5StickC Plus2 built-in buzzer;
- M5Stack Core Gray built-in speaker.

Both showcases compose versioned `firmware-contracts`, `ble-midi-input`,
`monophonic-instrument`, and `m5-tone-output` packages. Hardware validation
covers Note On/Off, last-note fallback, velocity, pitch bend, local panic,
disconnect cleanup, and reconnection. Native tests and CI cover the pure policy,
package consumers, and both firmware builds.

The baseline is tagged as `two-hardware-showcases-v0.1.0`. Package milestones
are tagged independently in their owning repositories.

**Status: complete.**

## Why Continue

The project does not need to outperform phone or desktop synthesizer apps to be
useful. Its current purpose is to explore how abandoned or modest embedded
gadgets can become physical musical objects with their own buttons, displays,
limitations, and playful character.

The Arturia MicroLab currently reaches the devices through an Android USB MIDI
to BLE MIDI bridge. A phone could synthesize the sound itself, so the current
composition is not yet an autonomous product. It remains a valid learning and
hardware-reuse experiment while exposing two independent directions:

1. remove the Android bridge;
2. make the physical devices capable of richer sound.

## Active Direction: Existing Audio Engines

The current bench already has working input, contracts, two ESP32 devices, and
two audio outputs. The next low-friction direction is to evaluate mature Open
Source audio engines rather than reimplementing synthesis techniques already
explored by other projects.

| Candidate | Role to probe | Main question |
| --- | --- | --- |
| [AMY](https://github.com/shorepine/amy) | Complete polyphonic synth engine | Can its PCM or I²S path coexist with M5 hardware and later consume our events? |
| [ESP32Synth](https://github.com/danilogcrf2-oss/ESP32Synth) | ESP32-optimized polyphonic engine | Do its direct task and peripheral choices coexist with M5Unified and BLE? |
| [esp32_fm_synth](https://github.com/marcel-licence/esp32_fm_synth) and [successor](https://github.com/marcel-licence/ml_synth_fm_example) | FM synth reference implementation | Can the newer GPL-3.0 code be isolated, built on the current toolchain, and redistributed under clear terms? |
| [TinySoundFont](https://github.com/schellingb/TinySoundFont) | SoundFont 2 renderer | Can useful banks fit or stream while buffers reach an M5 or I²S output reliably? |
| [Mozzi](https://github.com/sensorium/Mozzi) | Synthesis toolkit | Is it a useful educational/custom voice beside the complete engines? |
| [Faust](https://faust.grame.fr/) | DSP language and code generator | Can generated DSP become a reproducible PlatformIO package or showcase backend? |

These are alternatives with different purposes, not a queue that must all be
integrated.

### Suggested Next Micro-Slices

1. **AMY dependency and build probe**
   Add no shared abstraction. Compile the smallest isolated Arduino/PlatformIO
   program for the Core Gray target and record flash, RAM, toolchain, and package
   friction.

2. **AMY local sound probe**
   Without BLE, start the engine and produce one preset note on the Core Gray
   speaker or precisely document why its output path needs adaptation.

3. **AMY local polyphony probe**
   Trigger and release a small chord using buttons or a deterministic sequence.
   Confirm cleanup and listen for underruns or conflicts before involving BLE.

4. **Event adapter probe**
   If local audio works, adapt `NoteEvent`, `PitchBendEvent`, and disconnection to
   the engine. A mature polyphonic engine may implement `InstrumentEventSink`
   directly instead of pretending to be the current single `VoiceOutput`.

5. **Third composition showcase**
   Only after the adapter works, combine `ble-midi-input` with the engine and
   compare it with the two baseline showcases.

At every step record latency, simultaneous notes, CPU/RAM/flash cost, audible
artifacts, BLE coexistence, output hardware, license, and adapter size. Failure
to fit or coexist is useful evidence and does not require changing the baseline.

## Deferred Direction: Rust Receiver Platform Probe

After the current PlatformIO/C++ package ecosystem is stable, published, and
validated through the existing showcases, start a separate `esp-rs`
investigation for the BLE MIDI receiver.

This should not replace `ble-midi-input` during the current stabilization work.
Treat it as a fresh platform probe, likely in a sibling repository such as
`ble-midi-input-rs` or `midi-receiver-rs-probe`, with a deliberately narrow
first milestone:

1. boot an ESP32 firmware with the Rust toolchain;
2. advertise a BLE MIDI service with an observable device name;
3. receive raw BLE characteristic writes and log packet bytes;
4. parse Note On/Off only after raw packet reception is proven;
5. compare the resulting module boundary with the current PlatformIO package.

The value is architectural contrast: learn what a Rust-first receiver module
could look like outside pioarduino, while keeping the working PlatformIO modules
available for compositions.

## Deferred Direction: Autonomous MIDI Input

Removing Android remains desirable, but it is not the immediate track.

The cleanest likely experiment is a future ESP32-S3 device with usable USB OTG,
such as an M5StickS3, acting as USB MIDI host for the Arturia. That hardware is
not currently on the bench.

Available Heltec boards may also participate in an autonomous route, but would
likely require more than one board or an additional audio device. That makes the
probe a larger weekend-scale composition rather than a small continuation of
the current setup.

When hardware and time align, proceed in this order:

1. enumerate the Arturia as a USB MIDI device;
2. translate input into the existing semantic contracts;
3. create `usb-midi-input` only after the event path works;
4. reuse an existing instrument or engine without changing its MIDI semantics;
5. compare latency and cleanup with the Android BLE bridge.

Do not tie USB parsing to a particular synth engine. Input autonomy and sound
generation must remain independently replaceable.

## Contract Guidance for Future Engines

The current `VoiceOutput` describes one simple voice and should remain the
boundary used by `MonophonicInstrumentSink`. Do not force a polyphonic engine
behind it if that would discard native voice allocation, envelopes, patches,
effects, channels, or multitimbral behavior.

A future engine adapter may consume `InstrumentEventSink` directly. If several
engines expose PCM blocks, their real implementations may later justify a
separate render-source/audio-sink boundary. Do not design that abstraction
before the first working probe.

Support for MIDI channels is therefore not a goal by itself. Add channel-based
patches, routing, or multitimbrality when a selected engine provides a concrete
behavior worth exposing.

## Later Audio and Hardware Options

- Compare a second engine only after the first integration teaches us what to
  measure and where the real boundary lies.
- Explore a PCM5102 I²S line output when an engine can already produce continuous
  PCM; keep board-specific pins at the composition edge.
- Explore a physical AY-3-8910, AY-3-8912, or YM2149 only as a separate hardware
  experiment. The `AY3891x` library needs the external PSG, its clock, a wide
  GPIO bus, and an analog audio path; it is not another speaker backend for the
  current M5 devices.
- Keep the existing buzzer and Core Gray outputs as small, proven baselines.
  Richer engines supplement them and do not need to replace them.
- Revisit modulation, sustain, program change, CC120/CC123, sequencing, and
  arpeggiation when an active composition needs them.
- Keep raw BLE-MIDI parser research deferred unless the SynthBridge-compatible
  route develops a reproducible transport problem.

## Prioritization Rules

- Prefer a probe that can finish in one short session.
- Prefer integration over reimplementation when mature Open Source work exists.
- Start audio engines without BLE, then add semantic events, then compose.
- Add contracts only after a producer and a real consumer need them.
- Keep transport, contracts, musical policy, engine, and physical output
  independently replaceable.
- Preserve license notices and upstream contribution policies.
- Keep proven showcases working while experiments fail safely beside them.
- Record negative findings instead of hiding or architecting around them.
