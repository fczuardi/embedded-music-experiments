#include <Arduino.h>
#include <M5Unified.h>

#include "BleMidiInput.h"
#include "MonophonicInstrument.h"
#include "MonophonicInstrumentSink.h"
#include "SpeakerToneOutput.h"

namespace {
constexpr uint32_t UPTIME_LOG_INTERVAL_MS = 1000;

MonophonicInstrument instrument;
SpeakerToneOutput speakerToneOutput;
MonophonicInstrumentSink instrumentSink(instrument, speakerToneOutput);
BleMidiInput bleMidiInput;
uint32_t lastUptimeLogAtMs = 0;

void configureM5Stick() {
  auto config = M5.config();
  config.internal_spk = true;
  config.internal_mic = false;
  config.fallback_board = m5::board_t::board_M5StickCPlus2;
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
  M5.Display.println("Buzzer showcase");
  M5.Display.println();
  M5.Display.println("Connect BLE MIDI");
  M5.Display.println("Play notes");
}
}

void setup() {
  configureM5Stick();

  Serial.begin(115200);
  delay(200);

  speakerToneOutput.begin();
  speakerToneOutput.setWaveform(instrument.waveform());

  bleMidiInput.setInstrumentEventSink(&instrumentSink);
  bleMidiInput.begin();

  Serial.println();
  Serial.println("BLE MIDI buzzer showcase");
  Serial.printf("board_id=%d\n", static_cast<int>(M5.getBoard()));
  Serial.printf(
      "buzzer: backend=m5speaker waveform=%s\n",
      speakerToneOutput.waveformName());

  drawStaticScreen();
}

void loop() {
  M5.update();
  bleMidiInput.update();

  const uint32_t nowMs = millis();
  if (nowMs - lastUptimeLogAtMs >= UPTIME_LOG_INTERVAL_MS) {
    lastUptimeLogAtMs = nowMs;
    Serial.printf(
        "uptime=%lu playing=%s\n",
        nowMs / 1000,
        speakerToneOutput.isPlaying() ? "true" : "false");
  }
}
