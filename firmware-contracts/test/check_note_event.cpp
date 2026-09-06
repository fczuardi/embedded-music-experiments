#include "NoteEvent.h"

int main() {
  const NoteEvent event = {NoteEventType::NoteOn, 1, 60, 100};
  return event.note == 60 ? 0 : 1;
}
