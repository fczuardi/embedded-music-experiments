# Roadmap

This roadmap orders small experiments across the embedded-music repositories. It
is organized by reusable capabilities rather than by development board. Hardware
showcases provide evidence; the lasting result is a set of modules and semantic
boundaries that can be recombined.

The project remains an open-ended maker and learning effort. A useful outcome can
be a self-contained instrument, a controller, a sequencer, a sound module, or
simply a documented hardware limit.

## Current Foundation

The ecosystem already demonstrates three complete compositions:

- BLE MIDI to the M5StickC Plus2 buzzer;
- BLE MIDI to the M5Stack Core Gray speaker;
- BLE MIDI to AMY synthesis through the Core Gray speaker.

The proven package set includes shared firmware contracts, BLE MIDI input,
global last-note-priority monophonic policy, simple M5 tone outputs, and an AMY
facade. Note On/Off, velocity, pitch bend, panic, disconnect cleanup, fallback,
CC1 modulation, patch selection, packaging, CI, and hardware validation have
all been exercised in at least one real composition.

The AMY facade now accepts a fixed table of 16 patches, one for each zero-based
MIDI event channel. The instrument remains one globally monophonic AMY slot:
the channels select timbres; they do not create 16 voices or a multitimbral
engine.

The AMY package milestone is published as `amy-synth-m5@0.3.1`, and its
16-channel API and audited patch table are propagated into the umbrella
Showcase 3 with Core Gray hardware validation.

The sibling
[`calculator-face-input`](https://github.com/fczuardi/calculator-face-input)
repository now also provides a self-contained instrument baseline: a
hardware-validated four-track, sixteen-step drum sequencer for the Calculator
Face and Core Gray. It runs continuously, triggers AMY drums, supports live
step editing, exposes volume and tempo through a Core A modifier layer, and
assigns one of twenty curated drum sounds to each track through a Core B layer.
It deliberately remains a single volatile pattern; mute, copy, variation,
pattern storage, and chains are later experiments.

## Capability Model

The reusable ecosystem can be understood as four families:

| Family | Current examples | Candidate additions |
| --- | --- | --- |
| Input | BLE MIDI | USB MIDI host, M5 Faces, buttons, MIDI files |
| Semantics | notes, velocity, pitch bend, CC, lifecycle | transport clock, program change, timed events |
| Processing | monophonic priority, patch selection | metronome, arpeggiator, sequencer, tracker, router |
| Output | buzzer, Core Gray speaker, AMY PCM | I2S DAC, MIDI OUT, other synth engines and sound chips |

The intended direction is:

```text
physical or protocol input
        -> semantic musical events
        -> musical policy or transformation
        -> sound engine, hardware output, or another transport
```

BLE, USB, a local keyboard, and a sequencer should be able to express the same
musical intention. AMY, the tone backends, and future outputs should not need to
know where that intention originated.

## Hardware on the Bench

| Hardware | Useful question |
| --- | --- |
| Two M5Stack Core Gray units | How far can AMY and coordinated physical instruments go? |
| 36-key Keyboard Face | Can the ecosystem become a self-contained playable instrument without MIDI or a phone? |
| 20-key Calculator Face | Validated for direct track selection, 16-step editing, tempo/volume commands, and per-track sound assignment |
| Game-style Face | Can a small directional pad and action buttons provide useful transport and performance control? |
| M5StickC | How portable are the modules across older M5 hardware? |
| M5StickC Plus2 | What is the smallest useful buzzer instrument and control surface? |
| M5Stick S3 | Can USB MIDI host remove the Android bridge while preserving the event boundary? |
| LilyGo T-Display-S3 | Can a compact display-oriented board host a useful musical UI or sequencer? |
| Heltec ESP32 LoRa boards, including V4 | Which sparse musical or orchestration messages tolerate a long-range radio transport? |

A board does not automatically deserve a dedicated module or repository. It
becomes a useful target when it answers one of these questions with a working
composition.

## Ordered Roadmap

### 0. Completed: Stabilize and Propagate the 16-Channel AMY Baseline

The validated `amy-synth-m5@0.3.1` release is published. Umbrella Showcase 3
consumes its fixed 16-channel configuration, preserves the audited Juno patch
table, builds within the established IRAM budget, and has been revalidated on
the Core Gray.

This closes the current line before a new input source is introduced.

### 1. Self-Contained Instrument: Keyboard Face to Core Gray AMY

Use the 36-key Keyboard Face as the first non-MIDI producer:

```text
Keyboard Face
    -> local key mapping
    -> NoteEvent
    -> monophonic policy
    -> AMY
    -> Core Gray speaker
```

The first slice should only prove key press, key release, note mapping, and safe
cleanup. Octave changes, patch selection, sustain, and modulation can follow as
separate slices.

This experiment unlocks:

- a playable device without BLE, USB MIDI, or Android;
- the first producer that proves `NoteEvent` is independent of MIDI transport;
- an empirical boundary between physical key scanning and musical mapping;
- a foundation for using the same Face later as step-entry hardware.

The local input must not pretend that physical keys are raw MIDI. A small
mapping component should translate hardware actions into the existing semantic
contracts.

### 2. Direct USB MIDI Host on M5Stick S3

Connect the Arturia MicroLab directly to the S3 and translate USB MIDI into the
same event vocabulary:

```text
Arturia USB MIDI
    -> USB host transport
    -> shared events
    -> existing instrument consumer
```

Proceed in this order:

1. establish USB host power and enumerate the Arturia;
2. log raw MIDI messages;
3. translate Note On/Off only;
4. add pitch bend, CC1, channels, and cleanup;
5. extract `usb-midi-input` only after the working path reveals its boundary;
6. compare latency and failure cleanup with the Android BLE bridge.

A powered hub or power bank is a composition detail. USB parsing must remain
independent from AMY or any other engine.

This experiment removes the phone while retaining the full external keyboard.
Together with the Keyboard Face experiment, it gives the ecosystem three real
input sources: BLE MIDI, USB MIDI, and local keys.

### 3. Local Control Surfaces and Musical UI

Use the available Faces and displays according to their physical strengths:

| Input surface | Initial role |
| --- | --- |
| Keyboard Face | notes, octave, chord or step entry |
| Calculator Face | Validated for track/step editing and modal settings/sound commands; patterns and numeric entry remain open |
| Game Face | navigation, play/stop, pattern change, mute and performance actions |
| Core/S3/T-Display screens | state display and editing feedback |

Keep performance events separate from interface commands. A Start button is not
a fake MIDI note. UI actions may later become transport commands, editor
commands, or configuration changes.

Do not create a universal UI framework from the first Face. Build one small
working interaction, then extract only the repeated boundary.

### 4. Next Timing Experiment: a Minimal M5StickC Plus2 Metronome

Create a focused sibling `metronome` repository for the smallest second
experiment that needs musical time:

```text
internal clock
    -> metronome tick
    -> display and/or sound
```

Target the M5StickC Plus2, its two buttons, small display, and onboard buzzer.
Let that experiment determine the initial semantics for start, continue, stop,
tempo, meter, downbeats, and clock ticks. MIDI Clock, monotonic live time, and
Standard MIDI File ticks are related but not identical and should not be
collapsed prematurely.

A local `StepClock` already drives the Calculator sequencer, but one consumer is
not enough evidence for extraction. Compare it with the metronome implementation
before introducing a transport or beat-clock package. The umbrella should only
gain a metronome showcase after the application becomes a thin composition of
proven packages.

### 5. Completed Drum Baseline, Then Melodic and Pattern Exploration

The Calculator experiment exceeded the original one-track proposal with a
validated baseline:

- 16 steps;
- four boolean drum tracks;
- continuous playback with visible playhead;
- live tempo and volume changes;
- twenty directly selectable AMY drum sounds per track;
- fixed-size state and no allocation in the event or audio paths.

The app currently calls AMY directly at its output edge. That is acceptable for
the focused experiment, but trigger semantics and a generic sequencer output
must not be claimed from this single consumer.

The next sequencer slices may:

1. add mute, clear, copy, variation, pattern navigation, and chains locally;
2. keep playing, editing, and queued pattern identities distinct;
3. build a complementary melodic sequencer before extracting generic pattern
   or sequencer contracts;
4. use the Keyboard Face for melodic note entry or the Game Face for navigation
   and transport only when a concrete composition needs them;
5. add rests, velocity, ties, automation, and tracker concepts only as
   independent slices.

### 6. Routing and Coordination Between Gadgets

A router becomes justified only after multiple useful sources and destinations
exist. Candidate compositions include:

- local keyboard playing AMY and a second device;
- one gadget acting as clock master;
- a sequencer distributing channels across two Core Gray instruments;
- one device providing UI while another provides sound;
- channel, patch, or scene routing between physical objects.

The router should preserve semantic events and lifecycle cleanup. It should not
be introduced as a generic event bus before one of these compositions requires
it.

### 7. Additional Physical Transports

Evaluate transports in increasing order of uncertainty:

1. USB MIDI host;
2. UART MIDI through DIN or TRS hardware;
3. Wi-Fi or ESP-NOW between nearby gadgets;
4. LoRa for sparse, latency-tolerant orchestration.

LoRa is promising for installations, remote scene changes, coarse
synchronization, and playful distributed objects. It is not assumed to be
appropriate for every Note On/Off or tight musical clock because latency and
jitter must be measured first.

## Parallel Audio Track

Input, sequencing, and sound generation should evolve independently. The
existing tone outputs and AMY remain useful baselines while other engines are
tested beside them.

| Candidate | Question |
| --- | --- |
| PCM5102 or another I2S DAC | Can an existing PCM engine gain useful line output without changing musical contracts? |
| ESP32Synth | Can its polyphonic engine coexist with M5 hardware and current inputs? |
| Mozzi | Is it a useful educational/custom synthesis backend? |
| TinySoundFont | Can useful SoundFont banks fit or stream on available hardware? |
| Faust-generated DSP | Can generated code become a reproducible embedded package? |
| FM engines | Can an existing implementation provide a distinct voice without duplicating mature DSP work? |
| External synth or PSG hardware | Can semantic events drive dedicated sound chips or modules cleanly? |

A mature synth engine may consume `InstrumentEventSink` directly. It should
not be forced behind the simple frequency-oriented `VoiceOutput` abstraction
if that would discard patches, envelopes, polyphony, effects, or native voice
allocation.

New engines begin as isolated sound probes. Only after producing useful audio
should they receive adapters for shared events and enter a showcase.

## Deferred Platform Investigations

Rust/esp-rs and native ESP-IDF remain useful architecture probes, but they are
not near-term replacements for the working PlatformIO/Arduino modules.

A future receiver probe may:

1. boot on the alternative framework;
2. advertise BLE MIDI;
3. receive and log raw packets;
4. parse Note On/Off;
5. compare component boundaries and resource use with `ble-midi-input`.

Only framework-independent protocol or semantic code should be considered for
sharing. Transport implementations and applications may remain
framework-specific.

## Module and Repository Rules

- A new logical role does not automatically require a new repository.
- A small executable composition normally belongs under `showcases/`.
- Extract a package after a working experiment reveals a reusable boundary.
- Create a sibling repository when the module has independent value and a
  credible lifecycle of its own.
- Keep board initialization, pins, calibration, buttons, and display layout at
  the hardware or composition edge.
- Prefer fixed-size state and explicit resource limits in firmware paths.
- Preserve negative results and abandoned attempts in devlogs.

## Prioritization Rules

Prefer a slice that:

- can finish in one short session;
- produces observable hardware evidence;
- unlocks more than one later composition;
- tests an existing boundary from a new direction;
- integrates mature Open Source work rather than reimplementing it;
- keeps transport, semantics, policy, engine, and physical output replaceable;
- records memory, latency, cleanup behavior, and hardware limitations;
- leaves proven showcases working while an experiment fails safely beside them.

## Current Next Steps

1. Preserve the Calculator drum sequencer as the current playable checkpoint.
2. Start the M5StickC Plus2 metronome in a focused sibling repository.
3. Compare its timing and tempo-change behavior with the Calculator
   `StepClock`; extract nothing until the comparison reveals a stable contract.
4. Return to Calculator mute, pattern variation, and chaining as independent
   hardware-testable slices.
5. Use a later melodic sequencer as the second consumer for any proposed
   pattern-storage or sequencer-core boundary.

## North Star

The goal is not to choose one final instrument early. It is to create a terrain
where physical controls, MIDI transports, clocks, sequencers, synth engines,
simple transducers, external audio hardware, and multiple small gadgets can
participate through clear, tested boundaries.

**The unit of progress remains a working experiment. The unit of architecture
is a boundary that stays clear when a second producer, consumer, transport, or
hardware device appears.**
