#pragma once

#include <Arduino.h>
#include <M5Unified.h>

#include "BleMidiInput.h"
#include "InstrumentEventSink.h"
#include "M5ToneOutputCore.h"
#include "MonophonicInstrument.h"
#include "MonophonicInstrumentSink.h"

struct BleMidiInstrumentShowcaseConfig {
  const char* serialTitle;
  const char* displayTitle;
  const char* displaySubtitle;
  const char* outputLabel;
  VelocityVolumeRange velocityVolumeRange;
  float pitchBendRangeSemitones;
};

template <typename ToneOutput>
class BleMidiInstrumentShowcase {
public:
  explicit BleMidiInstrumentShowcase(
      const BleMidiInstrumentShowcaseConfig& config)
      : config_(config),
        instrumentSink_(instrument_, toneOutput_),
        loggingInstrumentSink_(instrumentSink_) {
  }

  void begin() {
    toneOutput_.begin();
    instrument_.setPitchBendRangeSemitones(config_.pitchBendRangeSemitones);
    toneOutput_.setVelocityVolumeRange(config_.velocityVolumeRange);
    toneOutput_.setWaveform(instrument_.waveform());

    bleMidiInput_.setInstrumentEventSink(&loggingInstrumentSink_);
    bleMidiInput_.begin();

    Serial.println();
    Serial.println(config_.serialTitle);
    Serial.printf("board_id=%d\n", static_cast<int>(M5.getBoard()));
    Serial.printf(
        "%s: backend=m5speaker waveform=%s velocity_volume_min=%u velocity_volume_max=%u pitch_bend_range_semitones=%.2f\n",
        config_.outputLabel,
        toneOutput_.waveformName(),
        config_.velocityVolumeRange.minimum,
        config_.velocityVolumeRange.maximum,
        config_.pitchBendRangeSemitones);

    drawStaticScreen();
  }

  void update() {
    bleMidiInput_.update();

    if (M5.BtnA.wasPressed()) {
      instrumentSink_.panic();
      Serial.println("panic: local button");
    }

    const uint32_t nowMs = millis();
    if (nowMs - lastUptimeLogAtMs_ >= UPTIME_LOG_INTERVAL_MS) {
      lastUptimeLogAtMs_ = nowMs;
      Serial.printf(
          "uptime=%lu playing=%s\n",
          nowMs / 1000,
          toneOutput_.isPlaying() ? "true" : "false");
    }
  }

private:
  static constexpr uint32_t UPTIME_LOG_INTERVAL_MS = 1000;

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

  void drawStaticScreen() {
    M5.Display.fillScreen(TFT_BLACK);
    M5.Display.setRotation(1);
    M5.Display.setBrightness(96);
    M5.Display.setCursor(0, 0);
    M5.Display.setTextColor(TFT_GREEN, TFT_BLACK);
    M5.Display.setTextSize(2);
    M5.Display.println(config_.displayTitle);
    M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Display.setTextSize(1);
    M5.Display.println(config_.displaySubtitle);
    M5.Display.println();
    M5.Display.println("Connect BLE MIDI");
    M5.Display.println("Play notes");
    M5.Display.println("BtnA: panic");
  }

  const BleMidiInstrumentShowcaseConfig& config_;
  MonophonicInstrument instrument_;
  ToneOutput toneOutput_;
  MonophonicInstrumentSink instrumentSink_;
  LoggingInstrumentEventSink loggingInstrumentSink_;
  BleMidiInput bleMidiInput_;
  uint32_t lastUptimeLogAtMs_ = 0;
};
