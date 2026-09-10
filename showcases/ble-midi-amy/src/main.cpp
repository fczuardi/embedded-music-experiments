#include <Arduino.h>
#include <M5Unified.h>

#include "AmyAudioActivityGate.h"
#include "AmyM5SpeakerBridge.h"
#include "AmyMonophonicInstrumentSink.h"
#include "AmyRuntime.h"
#include "AmySynthSlot.h"
#include "BleMidiInput.h"

namespace {
constexpr uint8_t AMY_SYNTH_ID = 1;
constexpr uint8_t AMY_VOICE_COUNT = 1;
constexpr uint8_t AMY_PATCH = 19;

AmyM5SpeakerBridge amyBridge;
AmyAudioActivityGate audioGate(amyBridge);
AmyRuntime amyRuntime;
AmySynthSlot amySlot;
AmyMonophonicInstrumentSink amyInstrument(
    amyRuntime,
    amySlot,
    audioGate);
BleMidiInput bleMidiInput;

void configureCoreGray() {
  auto config = M5.config();
  config.internal_spk = true;
  config.internal_mic = false;
  M5.begin(config);
}
}  // namespace

void setup() {
  Serial.begin(115200);
  delay(200);
  configureCoreGray();

  amyBridge.begin();
  amyRuntime.begin(AMY_SYNTH_ID);
  amySlot.begin(AMY_SYNTH_ID, AMY_VOICE_COUNT, AMY_PATCH);

  bleMidiInput.setInstrumentEventSink(&amyInstrument);
  bleMidiInput.begin();

  Serial.println("BLE MIDI AMY showcase");
  Serial.printf(
      "amy: synth_id=%u voices=%u patch=%u\n",
      AMY_SYNTH_ID,
      AMY_VOICE_COUNT,
      AMY_PATCH);
}

void loop() {
  M5.update();
  bleMidiInput.update();
  audioGate.update(amyInstrument.noteActive());

  if (M5.BtnA.wasPressed()) {
    amyInstrument.panic();
    Serial.println("amy: panic button");
  }
}
