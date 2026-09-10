#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_dir="$(cd "$script_dir/.." && pwd)"
workspace_dir="$(cd "$repo_dir/.." && pwd)"

pio_home="${PLATFORMIO_CORE_DIR:-$workspace_dir/.platformio-home}"
pio_python="${PLATFORMIO_PYTHON:-$pio_home/penv/bin/python}"
tool_dir="$pio_home/packages/tool-esptoolpy"

if [[ ! -x "$pio_python" ]]; then
  printf 'PlatformIO Python interpreter not found or not executable: %s\n' "$pio_python" >&2
  exit 69
fi

if [[ ! -d "$tool_dir" ]]; then
  printf 'PlatformIO esptool package directory not found: %s\n' "$tool_dir" >&2
  exit 69
fi

for tool in esptool.py espefuse.py espsecure.py esp_rfc2217_server.py; do
  tool_path="$tool_dir/$tool"

  if [[ -f "$tool_path" ]] && [[ "$(sed -n '1p' "$tool_path")" != "#!$pio_python" ]]; then
    tmp_path="${tool_path}.tmp"
    {
      printf '#!%s\n' "$pio_python"
      sed -n '2,$p' "$tool_path"
    } > "$tmp_path"
    chmod --reference="$tool_path" "$tmp_path"
    mv "$tmp_path" "$tool_path"
  fi
done

"$pio_python" "$tool_dir/esptool.py" version >/dev/null
