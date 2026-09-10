# pioarduino platform policy

The workspace now uses pioarduino for every ESP32 environment. The only
exception is `platformio/native` for host-side tests, which does not build
firmware or use the ESP32 framework.

This closes the earlier partial migration. Keeping both pioarduino and the
official ESP32 platform in the shared PlatformIO cache allowed incompatible
`tool-esptoolpy` versions to replace one another during builds. A single ESP32
platform family removes that source of cache instability while preserving the
validated Core Gray upload speed of `460800` and Plus2 speed of `1500000`.

No new hardware validation was performed by this documentation and platform
configuration slice.
