# Showcase 3: sixteen selectable AMY patches

## Goal

Propagate the hardware-validated 16-channel facade from published
`amy-synth-m5@0.3.1` into the umbrella Showcase 3.

## Design

The showcase remains a small composition of published packages:

```text
ble-midi-input -> AmyM5MonophonicSynth -> Core Gray speaker
```

It now supplies the facade's fixed configuration with exactly 16 patches:

```text
MIDI channel:  1  2   3   4   5   6   7   8   9   10  11  12  13  14   15   16
AMY patch:     0  9  18  24  32  40  49  54  64  73  80  89  96  105  114  120
```

This table is the initial demo bank selected with the Arturia controller in
the AMY repository. Patch 54 on channel 8 is the accepted replacement after
hardware trials of patches 58 and 62.

The facade still owns one AMY slot with one voice and a global last-note
priority policy. The 16 channels select timbres; they do not create a
multitimbral synth. CC1 continues to install one compound Juno mapping per
channel.

Version `0.3.1` also normalizes the controller's near-center Pitch Bend value
to zero while idle, preventing a released bend from leaking into the next
note. High-rate logging remains outside the showcase's musical event path.

## Verification

Run:

```sh
just showcase-build 3
just showcase-budget
```

The build must resolve `fcz2/amy-synth-m5@0.3.1` and remain within the existing
IRAM, DRAM, and firmware-image budgets.

The local budget check resolved the published `0.3.1` package and passed with:

- IRAM: `130971 / 130971` bytes budgeted (`101` bytes physically free);
- DRAM: `62904 / 65536` bytes budgeted;
- firmware image: `1231184 / 1300000` bytes budgeted.

For hardware validation, upload Showcase 3 to the Core Gray and use all 16
Arturia channel shortcuts. Confirm the patch table above, Note On/Off,
velocity, CC1, Pitch Bend, panic, and cross-channel monophonic fallback. Also
repeat the Pitch Bend regression: release a note while bent, center the strip,
then play another note; the new note must start unbent.

## Hardware result

Showcase 3 was uploaded to the Core Gray and validated with the Arturia
controller. The 16 channel shortcuts selected the expected patch bank, and the
performance controls remained functional. The Pitch Bend regression also
passed: after releasing a bent note and centering the strip, the next note
started at center pitch.

This closes the propagation from the AMY probe repository: the umbrella now
consumes the published `amy-synth-m5@0.3.1` API rather than continuing the
package investigation through local source paths.
