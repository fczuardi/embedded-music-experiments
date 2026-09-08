# Two-Hardware Showcase Milestone

The `monophonic-instrument` repository migration is complete, and the umbrella
now contains two executable BLE MIDI compositions using its extracted packages.

The M5StickC Plus2 showcase renders the shared monophonic policy through
`M5BuzzerToneOutput`. The M5Stack Core Gray showcase keeps the same input,
contracts, policy, sink, pitch bend range, and panic path while replacing the
board configuration, volume calibration, and output with
`M5CoreGrayToneOutput`.

Initial Core Gray hardware validation confirmed BLE connection, note playback,
audible pitch bend, and better low-note reproduction than the Plus2 buzzer.
Local panic, disconnect cleanup, reconnect, and deliberate velocity comparison
remain explicit follow-up checks rather than being claimed as complete.

This slice only updates the repository status and CI description in the root
README. It does not change either showcase or package.
