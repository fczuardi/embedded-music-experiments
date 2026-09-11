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

The showcase consumes exact PlatformIO Registry versions:
`fcz2/ble-midi-input@0.3.0` and `fcz2/amy-synth-m5@0.1.2`. Their transitive
dependencies resolve the shared contracts, monophonic note policy, AMY, and
M5Unified. The CI job therefore needs no sibling repository checkout.

## Verification

The showcase build passed for the Core Gray. The firmware was then validated
on the physical Core Gray with an Android BLE MIDI bridge and USB MIDI
controller: the advertised name was correct, connection and reconnection
worked, notes and velocity reached the AMY patch, pitch bend was audible,
disconnect cleanup worked, the idle gate was responsive, and the local panic
action stopped held sound.

This confirms the complete composition path on hardware. The same package
versions are now consumed from the PlatformIO Registry by local builds and CI.
