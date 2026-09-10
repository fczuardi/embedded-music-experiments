# Slice 028: Remove Esptool Cache Repair

## Goal

Remove the automatic PlatformIO cache mutation added in slice 027 while keeping
the clean interpreter fix for repository-owned scripts.

## Design

`scripts/upload-showcase.sh` no longer rewrites generated files under
`.platformio-home/packages/tool-esptoolpy` before upload. That repair worked,
but it made a normal showcase command silently modify local toolchain cache
state, which is too surprising for the umbrella repository.

The board guard remains explicit and clean: `scripts/probe-esp32-board.sh`
derives the shared PlatformIO cache path and invokes:

```bash
"$esptool_python" "$esptool_py" --port "$port" chip_id
```

That solves the part we own without depending on `esptool.py`'s shebang.

## Open Toolchain Question

If `pio run --target upload` still invokes PlatformIO's generated `esptool.py`
with system Python on a refreshed cache, that should be handled as a
PlatformIO/toolchain configuration issue rather than hidden behind an automatic
repo repair. The next useful data point is the exact upload behavior after the
cache repair script has been removed.

## Verification Target

```bash
just showcase-build 1
just showcase-build 2
just showcase-upload 1
```

The upload command should either flash the connected board or expose the
remaining PlatformIO-owned upload failure directly.
