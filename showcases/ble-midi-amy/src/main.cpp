#include <Arduino.h>
#include <M5Unified.h>

#include "AmyM5MonophonicSynth.h"
#include "BleMidiInput.h"

namespace {
constexpr AmyM5MonophonicSynthConfiguration SYNTH_CONFIGURATION{
    .synthId = 1,
    .voiceCount = 1,
    .patches = {
        0, 9, 18, 24,
        32, 40, 49, 54,
        64, 73, 80, 89,
        96, 105, 114, 120,
    },
};

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

  amySynth.begin(SYNTH_CONFIGURATION);
  amySynth.configureJunoPerformanceModulation();

  bleMidiInput.setInstrumentEventSink(&amySynth);
  bleMidiInput.begin();

  Serial.println("BLE MIDI AMY showcase");
  Serial.printf(
      "amy: synth_id=%u voices=%u channel_patches=%u\n",
      SYNTH_CONFIGURATION.synthId,
      SYNTH_CONFIGURATION.voiceCount,
      AMY_M5_MIDI_CHANNEL_COUNT);
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
