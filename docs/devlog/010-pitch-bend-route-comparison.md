# Slice 010: Pitch Bend Route Comparison

The previous pitch bend slice was paused because the showcase felt like it was
replaying old bend positions before processing Note Off. At that point, the
observed route was:

```text
Arturia USB OTG -> Android My MIDI Hub -> BLE MIDI -> showcase
```

After rolling back diagnostic experiments, we repeated the test with three
routes:

- Arturia USB OTG -> Android My MIDI Hub -> BLE MIDI -> showcase;
- Android SynthBridge -> BLE MIDI -> showcase;
- Arturia USB OTG -> Android SynthBridge Pro Trial -> BLE MIDI -> showcase.

The My MIDI Hub route still delayed Note Off when the Arturia pitch strip was
used. Both SynthBridge routes stopped notes immediately, even with pitch bend
activity and the serial monitor enabled.

This is a useful correction. The issue is not pitch bend as a shared contract,
not the Arturia strip by itself, not Android USB OTG by itself, and not BLE MIDI
in general. The likely problem is My MIDI Hub's USB-to-BLE forwarding behavior
under dense pitch bend traffic.

The next audible pitch bend slice should use SynthBridge as the primary
validation route and keep My MIDI Hub documented as a known-problem bridge for
this specific test.
