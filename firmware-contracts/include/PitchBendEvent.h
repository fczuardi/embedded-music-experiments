#pragma once

#include <cstdint>

// Typed pitch bend event shared by MIDI producers and instrument policy.
//
// This contract contains the normalized MIDI pitch bend value only. It does not
// define how an instrument maps the value to semitones, frequency, or timbre.
//
// Producers are responsible for validating raw MIDI data before creating this
// event. Channel is deliberately the raw zero-based MIDI status nibble:
// - channel uses the range 0-15 (physical MIDI channels 1-16);
// - value uses the centered MIDI pitch bend range -8192..8191.
struct PitchBendEvent {
  uint8_t channel;
  int16_t value;
};
