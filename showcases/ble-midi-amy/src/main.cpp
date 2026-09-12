#include <Arduino.h>
#include <M5Unified.h>

#include "AmyM5MonophonicSynth.h"
#include "BleMidiInput.h"

namespace {
constexpr uint8_t AMY_SYNTH_ID = 1;
constexpr uint8_t AMY_VOICE_COUNT = 1;
constexpr uint8_t FIRST_PATCH = 19;
constexpr uint8_t SECOND_PATCH = 24;

AmyM5MonophonicSynth amySynth;
BleMidiInput bleMidiInput;

void configureCoreGray() {
  auto config = M5.config();
  config.internal_spk = true;
  config.internal_mic = false;
  M5.begin(config);
}

void configureModWheelMappings() {
  const AmyMidiControlMapping firstChannel{
      .midiChannel = AmyM5MonophonicSynth::FIRST_MIDI_CHANNEL,
      .controller = 1,
      .targetOscillator = 3,
      .target = AmyModulationTarget::Frequency,
      .coefficientAtMinimum = 0.0f,
      .coefficientAtMaximum = 0.1f,
  };
  const AmyMidiControlMapping secondChannel{
      .midiChannel = AmyM5MonophonicSynth::SECOND_MIDI_CHANNEL,
      .controller = 1,
      .targetOscillator = 2,
      .target = AmyModulationTarget::Frequency,
      .coefficientAtMinimum = 0.0f,
      .coefficientAtMaximum = 0.1f,
  };

  amySynth.configureMidiControlMapping(firstChannel);
  amySynth.configureMidiControlMapping(secondChannel);
}
}  // namespace

void setup() {
  Serial.begin(115200);
  delay(200);
  configureCoreGray();

  amySynth.begin(
      AMY_SYNTH_ID, AMY_VOICE_COUNT, FIRST_PATCH, SECOND_PATCH);
  configureModWheelMappings();

  bleMidiInput.setInstrumentEventSink(&amySynth);
  bleMidiInput.begin();

  Serial.println("BLE MIDI AMY showcase");
  Serial.printf(
      "amy: synth_id=%u voices=%u patches=%u,%u\n",
      AMY_SYNTH_ID,
      AMY_VOICE_COUNT,
      FIRST_PATCH,
      SECOND_PATCH);
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
