#pragma once

#include "ControlChangeEvent.h"
#include "NoteEvent.h"
#include "PitchBendEvent.h"

// Boundary for code that produces instrument events.
//
// A receiver, test harness, or local button adapter can target this interface
// without depending on the concrete instrument state or speaker implementation.
class InstrumentEventSink {
public:
  virtual ~InstrumentEventSink() = default;

  virtual void onNoteEvent(const NoteEvent& event) = 0;
  virtual void onPitchBendEvent(const PitchBendEvent& event) = 0;
  // Optional continuous performance control. Consumers that do not use
  // control changes can inherit the no-op implementation.
  virtual void onControlChangeEvent(const ControlChangeEvent&) {
  }
  virtual void onDisconnected() = 0;
};
