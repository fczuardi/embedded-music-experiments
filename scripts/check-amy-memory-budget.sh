#!/usr/bin/env bash

set -euo pipefail

showcase_path="showcases/ble-midi-amy"
build_log="$(mktemp)"
trap 'rm -f "$build_log"' EXIT

if ! pio run -d "$showcase_path" >"$build_log" 2>&1; then
  cat "$build_log"
  exit 1
fi

cat "$build_log"

elf_path="$showcase_path/.pio/build/m5stack-core-gray/firmware.elf"
binary_path="$showcase_path/.pio/build/m5stack-core-gray/firmware.bin"
size_report="$(cd "$showcase_path" && pio pkg exec \
  --package toolchain-xtensa-esp-elf -- \
  xtensa-esp32-elf-size -A .pio/build/m5stack-core-gray/firmware.elf)"

iram_used="$(printf '%s\n' "$size_report" | awk \
  '$1 == ".iram0.vectors" || $1 == ".iram0.text" {sum += $2} END {print sum}')"
dram_used="$(printf '%s\n' "$size_report" | awk \
  '$1 == ".dram0.data" || $1 == ".dram0.bss" {sum += $2} END {print sum}')"
flash_used="$(wc -c < "$binary_path")"

if [[ ! -f "$elf_path" || ! -f "$binary_path" || -z "$iram_used" ||
      -z "$dram_used" || -z "$flash_used" ]]; then
  printf 'Could not extract the Showcase 3 memory report.\n' >&2
  exit 1
fi

readonly iram_budget=130971
readonly dram_budget=65536
readonly flash_budget=1300000

printf 'AMY Showcase 3 memory budget:\n'
printf '  IRAM:  %s / %s bytes\n' "$iram_used" "$iram_budget"
printf '  DRAM:  %s / %s bytes\n' "$dram_used" "$dram_budget"
printf '  image: %s / %s bytes\n' "$flash_used" "$flash_budget"

failed=0
if (( iram_used > iram_budget )); then
  printf 'IRAM budget exceeded.\n' >&2
  failed=1
fi
if (( dram_used > dram_budget )); then
  printf 'DRAM budget exceeded.\n' >&2
  failed=1
fi
if (( flash_used > flash_budget )); then
  printf 'Flash image budget exceeded.\n' >&2
  failed=1
fi

exit "$failed"
