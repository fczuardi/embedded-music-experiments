# Slice 027: PlatformIO Esptool Python Repair

## Goal

Make showcase uploads resilient to a local PlatformIO cache issue where the
generated `tool-esptoolpy/esptool.py` entrypoint runs with system Python instead
of the shared PlatformIO virtual environment.

## Problem

`just showcase-upload 1` packed the local showcase dependencies successfully,
then failed before flashing:

```text
ModuleNotFoundError: No module named 'rich_click'
```

The firmware build was not the problem. The generated PlatformIO script at
`/home/fcz/dev/m5stick/.platformio-home/packages/tool-esptoolpy/esptool.py`
used this shebang:

```text
#!/usr/bin/env python
```

That resolves to the system Python in this workspace, which does not have
PlatformIO's `rich_click` dependency. The shared PlatformIO environment already
has the dependency under:

```text
/home/fcz/dev/m5stick/.platformio-home/penv/bin/python
```

## Design

Add `scripts/repair-platformio-esptool-python.sh`, a small local toolchain
repair script used by showcase uploads before probing or flashing hardware. It
rewrites the shebangs for the generated esptool scripts to the shared
PlatformIO Python interpreter, then verifies that `esptool.py version` runs.

The script derives the cache path from the workspace layout and still supports
overrides through:

- `PLATFORMIO_CORE_DIR`
- `PLATFORMIO_PYTHON`
- `PLATFORMIO_ESPTOOL_REPAIR`

`scripts/probe-esp32-board.sh` was also updated to derive its esptool Python
path from the shared cache instead of an older pipx PlatformIO path.

## Verification

```bash
scripts/repair-platformio-esptool-python.sh
just showcase-build 1
just showcase-upload 1
```

The upload command is expected to proceed past the previous Python import
failure. Hardware flashing still depends on a visible serial device.

## Hardware Observation

No firmware behavior changed in this slice. This is upload tooling only.
