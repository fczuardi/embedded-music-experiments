#pragma once

#include <cstdint>

// Typed MIDI control-change event shared by MIDI producers and instruments.
// Channel, controller, and value preserve the raw zero-based MIDI ranges.
struct ControlChangeEvent {
  uint8_t channel;
  uint8_t controller;
  uint8_t value;
};
