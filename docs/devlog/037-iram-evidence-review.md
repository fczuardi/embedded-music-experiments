# 037. IRAM evidence review

## Context

The `ci/showcase3-iram-evidence` branch measured the linked Showcase 3 ELF and
performed temporary CI-only ablation probes. The final branch state contains no
temporary probe environments; only the report instrumentation, its workflow
integration, and the resulting documentation remain there.

This review does not replace the current memory-budget guard or change the
published packages or firmware. It records the conclusions that are useful for
the roadmap.

## Measurements

The published BLE MIDI composition uses 129811 of 131072 IRAM bytes, leaving
1261 bytes free. Removing the complete BLE receiver path from an otherwise
equivalent AMY + M5 build used 79447 bytes, recovering 50364 bytes.

Reducing NimBLE-Arduino to the roles needed by this receiver and one connection
recovered only 256 bytes. Defining
`CONFIG_BT_NIMBLE_LOW_SPEED_MODE=1` changed neither IRAM nor flash in the
Arduino/pioarduino build for the original ESP32.

These results indicate that most of the BLE cost is below the application-level
NimBLE role configuration, in the ESP32 controller and required BLE support.
Recovering meaningful space would require a custom ESP-IDF/framework build or a
different transport, followed by physical BLE and audio regression testing.

## Decision

Treat the current firmware as a constrained, reproducible Core Gray BLE Juno
composition. Keep the existing static memory budget and measure every future
change. Small additions using already-linked M5Unified facilities, buttons, or
GPIO polling can be considered in isolated slices. New interrupt handlers,
drivers, and subsystems require stronger evidence before adoption.

No package boundary or firmware behavior changed in this review. The existing
hardware validation remains the evidence for MIDI, audio, reconnect, disconnect
cleanup, pitch bend, panic, and idle gating.
