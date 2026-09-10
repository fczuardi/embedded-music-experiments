#!/usr/bin/env bash
set -euo pipefail

expected_board="${1:-}"
showcase_dir="${2:-}"
pio_env="${3:-}"

board_guard="${BOARD_GUARD:-scripts/probe-esp32-board.sh}"
pio_bin="${PIO:-pio}"

usage() {
  printf 'Usage: %s [m5stick-cplus2|m5stack-core-gray] [showcase-dir] [platformio-env]\n' "$0" >&2
}

if [[ -z "$expected_board" || -z "$showcase_dir" || -z "$pio_env" ]]; then
  usage
  exit 64
fi

if [[ "${M5_SKIP_BOARD_GUARD:-0}" == "1" ]]; then
  exec "$pio_bin" run -d "$showcase_dir" -e "$pio_env" --target upload
fi

port="$("$board_guard" --port-for "$expected_board")"
exec "$pio_bin" run -d "$showcase_dir" -e "$pio_env" --upload-port "$port" --target upload
