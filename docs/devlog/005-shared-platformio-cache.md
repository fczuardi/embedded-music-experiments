# Slice 005: Shared PlatformIO Cache

The Core Gray speaker experiment exposed a workspace-level problem rather than
a firmware problem. Each sibling repository had been using its own
`.platformio-home` directory. That made individual repos self-contained, but it
also duplicated the same ESP32 platform, toolchains, framework, and Python tool
packages across several small experiments.

While starting `m5-speaker-instrument`, the first PlatformIO build tried to
install another full copy of the ESP32 toolchain and failed during
`tool-esptoolpy` setup with `Disk quota exceeded`. The filesystem still had
space available, so the useful conclusion was that the experiment workflow
needed a shared PlatformIO cache before adding more hardware repos.

The chosen layout is a single parent cache:

```text
/home/fcz/dev/m5stick/.platformio-home
```

Each PlatformIO firmware project now points `core_dir` at that parent cache from
its own `platformio.ini`:

- `midi-receiver/platformio.ini`
- `buzzer-instrument/platformio.ini`
- `m5-speaker-instrument/platformio.ini`
- `embedded-music-experiments/showcases/ble-midi-buzzer/platformio.ini`

ESP32 firmware environments also pass `-pipe` through `build_flags`. This is a
small compiler setting, not a workspace discovery hook: it tells GCC to use
pipes between compilation stages where possible, reducing large temporary
assembler files in `/tmp` while compiling M5GFX.

The umbrella `justfile` no longer needs to know about the cache. It only calls
`pio run -d "$showcase"` or `pio device monitor -d "$showcase"`; the showcase's
own `platformio.ini` supplies the shared `core_dir`.

This does not make build outputs global. Per-project `.pio/` directories remain
local to the firmware project, while downloaded platforms, toolchains, and
library cache data are shared.

Verification target:

```bash
pio run
```

Result: after removing duplicate generated caches and using a workspace
temporary directory manually for the first dependency installation, the Core
Gray speaker firmware built successfully with the shared cache. Normal project
commands then built without exporting `PLATFORMIO_CORE_DIR`.

Verified commands:

```bash
cd /home/fcz/dev/m5stick/m5-speaker-instrument && pio run
cd /home/fcz/dev/m5stick/buzzer-instrument && pio run
cd /home/fcz/dev/m5stick/buzzer-instrument && pio test -e native
cd /home/fcz/dev/m5stick/midi-receiver && pio run
cd /home/fcz/dev/m5stick/midi-receiver && pio test -e native
cd /home/fcz/dev/m5stick/embedded-music-experiments && just showcase-build
```
