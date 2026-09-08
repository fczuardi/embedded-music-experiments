# Slice 022: Core Gray Stability Checklist

## Goal

Turn the initial Core Gray BLE MIDI success into a deliberate parity checklist
against the M5StickC Plus2 showcase baseline.

## Design Choices

The code path is unchanged in this slice. The showcase already composes
`ble-midi-input`, `monophonic-instrument`, and `m5-tone-output`; this slice only
records the remaining behavioral checks that need physical observation on the
M5Stack Core Gray.

The checklist lives next to the showcase README so future hardware sessions can
validate the exact firmware being exercised:

- local panic through Button A;
- silence on BLE disconnect;
- reconnection without reflashing or power cycling;
- fallback between overlapping held notes;
- audible velocity response in the configured Core Gray volume range.

## Limits

These checks could not be completed by command-line tests alone because they
depended on a BLE route, a controller or SynthBridge input surface, and audible
speaker behavior on the physical Core Gray.

## Verification Commands

```bash
just showcase-build 2
```

## Hardware Observations

Passed on the M5Stack Core Gray with this route:

```text
Arturia controller -> Android SynthBridge app -> M5Stack Core Gray
```

Observed behaviors:

- Button A panic silenced held notes.
- BLE disconnect silenced active sound.
- BLE reconnection worked without reflashing or resetting the device.
- Multiple-key fallback returned to the previous held note and respected the
  velocity preserved for that note.
- Velocity influenced speaker volume audibly in the configured showcase range.
