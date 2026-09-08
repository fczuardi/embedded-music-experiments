#include <Arduino.h>
#include <M5Unified.h>

#include "../../common/BleMidiInstrumentShowcase.h"
#include "M5CoreGrayToneOutput.h"

namespace {
// custom volume limits for velocity mapping, the Core Gray defaults are 1-35
constexpr VelocityVolumeRange SHOWCASE_VELOCITY_VOLUME_RANGE = {5, 35};
// custom pitch bend range in semitones, the package default is 2.0
constexpr float SHOWCASE_PITCH_BEND_RANGE_SEMITONES = 4.0f;

constexpr BleMidiInstrumentShowcaseConfig SHOWCASE_CONFIG = {
    "BLE MIDI Core Gray speaker showcase",
    "BLE MIDI",
    "Core Gray speaker",
    "speaker",
    SHOWCASE_VELOCITY_VOLUME_RANGE,
    SHOWCASE_PITCH_BEND_RANGE_SEMITONES,
};

BleMidiInstrumentShowcase<M5CoreGrayToneOutput> showcase(SHOWCASE_CONFIG);

void configureM5StackCoreGray() {
  auto config = M5.config();
  config.internal_spk = true;
  config.internal_mic = false;
  M5.begin(config);
}
}

void setup() {
  configureM5StackCoreGray();

  Serial.begin(115200);
  delay(200);

  showcase.begin();
}

void loop() {
  M5.update();
  showcase.update();
}
