#include "MonophonicInstrument.h"

int main() {
  MonophonicInstrument instrument;
  const VoiceAction startAction = instrument.noteOn(69, 100);

  if (startAction.type != VoiceActionType::StartNote) {
    return 1;
  }

  if (startAction.midiNote != 69) {
    return 2;
  }

  return 0;
}
