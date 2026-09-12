# Repin All Active MIDI Consumers

## Finding

The receiver repository had published `ble-midi-input@0.3.0`, which uses the
direct NimBLE-Arduino backend. The umbrella Showcase 3 had already consumed
that package, but the buzzer and Core Gray speaker showcases still referenced
the old `lathoub/BLE-MIDI` based commit `c40e71bf`.

The AMY repository had the same stale dependency in both its one-channel app
and its new two-channel probe. This was a cross-repository migration gap, not
an intentional compatibility choice.

## Change

All active application manifests now use:

```ini
fcz2/ble-midi-input@0.3.0
```

Historical devlog references remain unchanged because they describe the
experiments that produced the migration.

## Verification

The buzzer and Core Gray speaker showcases built successfully with the
published NimBLE-based package. Showcase 3 also built successfully. The AMY
one-channel and two-channel applications were rebuilt separately in their
own repository; the two-channel application now has the published package in
its dependency graph.

Physical validation is still required for the repinned buzzer and Core Gray
showcases, and for confirming that AMY disconnect cleanup now follows the
behavior observed in the current receiver firmware.
