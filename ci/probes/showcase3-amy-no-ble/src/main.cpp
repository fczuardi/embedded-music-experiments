#include <Arduino.h>
#include <M5Unified.h>

#include "AmyM5MonophonicSynth.h"

namespace {
constexpr uint8_t AMY_SYNTH_ID = 1;
constexpr uint8_t AMY_VOICE_COUNT = 1;
constexpr uint8_t AMY_PATCH = 19;

AmyM5MonophonicSynth amySynth;
}  // namespace

void setup() {
  auto config = M5.config();
  config.internal_spk = true;
  config.internal_mic = false;
  M5.begin(config);

  amySynth.begin(AMY_SYNTH_ID, AMY_VOICE_COUNT, AMY_PATCH);
}

void loop() {
  M5.update();
  amySynth.update();
}
