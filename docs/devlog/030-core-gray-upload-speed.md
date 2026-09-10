# Slice 030: Core Gray Upload Speed

## Goal

Make showcase 2 upload reliably to the original M5Stack Core Gray.

## Problem

`just showcase-upload 2` connected to the ESP32 and started the esptool stub,
but failed after switching to `1500000` baud:

```text
Changing baud rate to 1500000
A fatal error occurred: The chip stopped responding.
```

This matches the upload instability previously observed in the AMY Core Gray
app. The failure happens in the flashing transport after the baud-rate switch,
not in firmware build, BLE MIDI code, or the scan-response-name fix.

## Design

Lower only the Core Gray showcase upload speed:

```ini
upload_speed = 460800
```

The Plus2 showcase keeps its existing configuration. This is a board-specific
serial upload setting for the older Core Gray path.

## Verification Target

```bash
just showcase-build 2
just showcase-upload 2
```

Hardware follow-up should confirm that upload completes and that the BLE scan
name still appears as `M5 Gray Speaker`.
