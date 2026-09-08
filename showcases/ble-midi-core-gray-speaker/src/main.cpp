#include <Arduino.h>
#include <M5Unified.h>

#include "BleMidiInput.h"
#include "M5CoreGrayToneOutput.h"
#include "MonophonicInstrument.h"
#include "MonophonicInstrumentSink.h"

namespace {
constexpr uint32_t UPTIME_LOG_INTERVAL_MS = 1000;
// custom volume limits for velocity mapping, the Core Gray defaults are 1-35
constexpr VelocityVolumeRange SHOWCASE_VELOCITY_VOLUME_RANGE = {5, 35};
// custom pitch bend range in semitones, the package default is 2.0
constexpr float SHOWCASE_PITCH_BEND_RANGE_SEMITONES = 4.0f;

class LoggingInstrumentEventSink : public InstrumentEventSink {
public:
  explicit LoggingInstrumentEventSink(InstrumentEventSink& innerSink)
      : innerSink_(innerSink) {
  }

  void onNoteEvent(const NoteEvent& event) override {
    innerSink_.onNoteEvent(event);
  }

  void onPitchBendEvent(const PitchBendEvent& event) override {
    Serial.printf(
        "pitch_bend: channel=%u value=%d\n",
        event.channel,
        event.value);
    innerSink_.onPitchBendEvent(event);
  }

  void onDisconnected() override {
    innerSink_.onDisconnected();
  }

private:
  InstrumentEventSink& innerSink_;
};

MonophonicInstrument instrument;
M5CoreGrayToneOutput speakerToneOutput;
MonophonicInstrumentSink instrumentSink(instrument, speakerToneOutput);
LoggingInstrumentEventSink loggingInstrumentSink(instrumentSink);
BleMidiInput bleMidiInput;
uint32_t lastUptimeLogAtMs = 0;

void configureM5StackCoreGray() {
  auto config = M5.config();
  config.internal_spk = true;
  config.internal_mic = false;
  M5.begin(config);
}

void drawStaticScreen() {
  M5.Display.fillScreen(TFT_BLACK);
  M5.Display.setRotation(1);
  M5.Display.setBrightness(96);
  M5.Display.setCursor(0, 0);
  M5.Display.setTextColor(TFT_GREEN, TFT_BLACK);
  M5.Display.setTextSize(2);
  M5.Display.println("BLE MIDI");
  M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Display.setTextSize(1);
  M5.Display.println("Core Gray speaker");
  M5.Display.println();
  M5.Display.println("Connect BLE MIDI");
  M5.Display.println("Play notes");
  M5.Display.println("BtnA: panic");
}
}

void setup() {
  configureM5StackCoreGray();

  Serial.begin(115200);
  delay(200);

  speakerToneOutput.begin();
  instrument.setPitchBendRangeSemitones(SHOWCASE_PITCH_BEND_RANGE_SEMITONES);
  speakerToneOutput.setVelocityVolumeRange(SHOWCASE_VELOCITY_VOLUME_RANGE);
  speakerToneOutput.setWaveform(instrument.waveform());

  bleMidiInput.setInstrumentEventSink(&loggingInstrumentSink);
  bleMidiInput.begin();

  Serial.println();
  Serial.println("BLE MIDI Core Gray speaker showcase");
  Serial.printf("board_id=%d\n", static_cast<int>(M5.getBoard()));
  Serial.printf(
      "speaker: backend=m5speaker waveform=%s velocity_volume_min=%u velocity_volume_max=%u pitch_bend_range_semitones=%.2f\n",
      speakerToneOutput.waveformName(),
      SHOWCASE_VELOCITY_VOLUME_RANGE.minimum,
      SHOWCASE_VELOCITY_VOLUME_RANGE.maximum,
      SHOWCASE_PITCH_BEND_RANGE_SEMITONES);

  drawStaticScreen();
}

void loop() {
  M5.update();
  bleMidiInput.update();

  if (M5.BtnA.wasPressed()) {
    instrumentSink.panic();
    Serial.println("panic: local button");
  }

  const uint32_t nowMs = millis();
  if (nowMs - lastUptimeLogAtMs >= UPTIME_LOG_INTERVAL_MS) {
    lastUptimeLogAtMs = nowMs;
    Serial.printf(
        "uptime=%lu playing=%s\n",
        nowMs / 1000,
        speakerToneOutput.isPlaying() ? "true" : "false");
  }
}
