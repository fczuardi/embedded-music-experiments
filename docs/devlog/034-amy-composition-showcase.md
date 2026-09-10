# 034 AMY composition showcase

## Goal

Add a third umbrella composition that proves the AMY backend can be consumed
through its package boundary rather than through the original probe app.

## Composition

`showcases/ble-midi-amy` is intentionally small:

```text
BLE MIDI -> InstrumentEventSink -> AmyMonophonicInstrumentSink ->
AmyRuntime/AmySynthSlot -> AmyM5SpeakerBridge -> M5Stack Core Gray speaker
```

It uses one AMY slot and the validated patch 19. The showcase has no patch
browser, display policy, or duplicated AMY implementation. Button A remains a
small local panic action because it is useful when testing a physical MIDI
controller.

The current dependencies point to sibling package directories because the
current `ble-midi-input` and `amy-synth-m5` versions are not both available in
the PlatformIO Registry yet. The CI job checks out `amy-synth-m5` at commit
`699686a5` and `midi-receiver` at commit `a330801b`, so these paths are
deterministic and do not depend on the developer machine. After both packages
are published, the dependency origins should move to exact PlatformIO Registry
versions without changing the composition code.

## Verification

The showcase build is the next validation target. Hardware behavior still
needs confirmation on the Core Gray. This slice does not claim new hardware
validation.
