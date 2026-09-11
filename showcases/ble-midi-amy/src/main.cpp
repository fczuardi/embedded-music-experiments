#include <Arduino.h>
#include <M5Unified.h>

#include "AmyM5MonophonicSynth.h"
#include "BleMidiInput.h"

namespace {
constexpr uint8_t AMY_SYNTH_ID = 1;
constexpr uint8_t AMY_VOICE_COUNT = 1;
constexpr uint8_t AMY_PATCH = 19;

AmyM5MonophonicSynth amySynth;
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

  amySynth.begin(AMY_SYNTH_ID, AMY_VOICE_COUNT, AMY_PATCH);

  bleMidiInput.setInstrumentEventSink(&amySynth);
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
  amySynth.update();

  if (M5.BtnA.wasPressed()) {
    amySynth.panic();
    Serial.println("amy: panic button");
  }
}
