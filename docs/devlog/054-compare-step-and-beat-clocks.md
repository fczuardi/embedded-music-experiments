# Compare the Calculator StepClock and Metronome BeatClock

## Question

The [Calculator drum sequencer](https://github.com/fczuardi/calculator-face-input)
and [M5StickC Plus2 metronome](https://github.com/fczuardi/metronome) now provide
two working timing implementations. What, if anything, can they share?

This is a comparison of the code at this checkpoint, not a proposal to extract
a package. Differences may be expedient choices made while getting each device
working. They do not establish distinct requirements for sequencers and
metronomes.

## Observed behavior

| Concern | Calculator `StepClock` | Metronome `BeatClock` |
| --- | --- | --- |
| Input and stored state | `nowMs`, interval in integer ms, next deadline, started flag | Same |
| First deadline | `begin(nowMs)` schedules `nowMs + intervalMs` | Same |
| Poll result | `uint8_t elapsedSteps(nowMs)` | `uint32_t elapsedBeats(nowMs)` |
| Poll before `begin()` | Starts at poll time, returns zero | Returns zero without starting |
| Late poll | Advances deadline once per missed period; return count saturates at 255 | Computes missed periods arithmetically and advances deadline by that count |
| Interval change | `setInterval(intervalMs)` retains the existing next deadline | `setIntervalMs(nowMs, intervalMs)` scales remaining time to preserve the fraction of the period when the deadline is in the future |
| Zero interval | No guard; polling at or past deadline can loop forever | Zero is rejected by the setter; polling returns zero if constructed with zero |
| Musical concepts inside clock | No BPM, meter, pattern, position, audio, or display | No BPM, meter, pattern, position, audio, or display |

Both use `millis()`-style unsigned deadlines and signed subtraction to test
whether a deadline is due. Their intended interval and polling horizon must
stay within the usual signed 32-bit comparison window around wraparound.

The application supplies meaning to the counts. Calculator advances its
`PatternEditorState` once per reported step, then triggers only the current
step and updates the playhead. Metronome advances `MetronomeState` by the
reported beat count, then plays only the current click and updates the display.
Neither replays every missed sound. Calculator's capped return means an
exceptionally long pause can leave its musical position behind even though
its clock deadline has advanced past the pause; this is a numerical limitation,
not evidence of a desired sequencer policy.

The metronome plays a click immediately at startup; the Calculator does not
trigger the initial step in setup. This is application behavior, separate from
the clocks' first scheduled deadline.

## What the comparison supports

Both implementations independently use a periodic deadline and report elapsed
periods. Neither owns musical position or translates BPM internally. BPM to
interval conversion lives in each application: beats in the metronome and
sixteenth notes in the Calculator. The consumers currently share the broad
policy of catching up position while emitting at most one current audible
event per poll.

The code does **not** tell us why their startup, arithmetic, count types, or
tempo-change behavior differ. In particular, retaining the next deadline in
Calculator and scaling its remaining time in Metronome are observed behaviors,
not established requirements tied to steps or beats. No inherent clock-level
difference between a step and a beat has been demonstrated yet.

## Open decisions and useful probes

1. **Tempo change:** Should an adjustment retain the next deadline, preserve
   the fractional phase, restart the period now, or take effect after the next
   tick? Try the same candidate behavior on both devices and listen/observe,
   including changes near a deadline. The existing metronome calculation clamps
   an overdue deadline's remaining time to zero; test changes during a delayed
   loop separately.
2. **Start and transport:** Decide whether an explicit `begin` is required,
   whether starting emits an immediate event, and what stop/continue mean to
   the application before putting transport in a shared clock.
3. **Late polls:** Test a delayed loop spanning multiple periods. Specify how
   many periods the clock reports and what each consumer does with that count.
   Distinguish deadline accounting, musical position, and audible output.
4. **Arithmetic:** Bound valid intervals and maximum lateness; handle zero,
   wraparound, and large counts deliberately. These are correctness questions
   regardless of the musical policy chosen.

A possible small shared mechanism is a periodic deadline accumulator receiving
`nowMs` and returning elapsed ticks. `PeriodicClock` is a working name, not an
API decision. Keep BPM, subdivision, meter, position, sound, and display at the
application boundary unless another experiment demonstrates a common contract.

## Next slice

First record a few tempo-change and delayed-loop scenarios with expected
deadlines and positions. Then implement one candidate tempo-change policy in
both applications and test it on hardware. Compare the results before
extracting or renaming a shared class. The timing implementation may remain
local if the shared contract does not prove useful.

Sources inspected: `apps/drum-step-sequencer/src/{StepClock.h,StepClock.cpp,main.cpp}`
in Calculator and `src/{BeatClock.h,BeatClock.cpp,main.cpp}` in Metronome.
