#include "InstrumentEventSink.h"

class CapturingSink : public InstrumentEventSink {
public:
  void onNoteEvent(const NoteEvent& event) override {
    lastEvent = event;
  }

  void onPitchBendEvent(const PitchBendEvent& event) override {
    lastPitchBendEvent = event;
  }

  void onControlChangeEvent(const ControlChangeEvent& event) override {
    lastControlChangeEvent = event;
  }

  void onDisconnected() override {
    disconnected = true;
  }

  NoteEvent lastEvent = {NoteEventType::NoteOff, 1, 0, 0};
  PitchBendEvent lastPitchBendEvent = {1, 0};
  ControlChangeEvent lastControlChangeEvent = {1, 0, 0};
  bool disconnected = false;
};

int main() {
  CapturingSink sink;
  sink.onNoteEvent({NoteEventType::NoteOn, 1, 60, 100});
  sink.onPitchBendEvent({1, -2048});
  sink.onControlChangeEvent({1, 1, 96});
  sink.onDisconnected();

  return sink.disconnected &&
                 sink.lastEvent.note == 60 &&
                 sink.lastPitchBendEvent.value == -2048 &&
                 sink.lastControlChangeEvent.controller == 1 &&
                 sink.lastControlChangeEvent.value == 96
             ? 0
             : 1;
}
