#pragma once

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
  virtual void onDisconnected() = 0;
};
