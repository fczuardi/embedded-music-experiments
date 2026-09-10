#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
workspace_root="${WORKSPACE_ROOT:-$(cd "$repo_root/.." && pwd)}"
archive_dir="${ARCHIVE_DIR:-$repo_root/.tmp}"
monophonic_repo="${MONOPHONIC_INSTRUMENT_REPO:-$workspace_root/monophonic-instrument}"
monophonic_commit="${MONOPHONIC_INSTRUMENT_COMMIT:-e8d6ca63fcf2}"
pio_bin="${PIO:-pio}"

export PLATFORMIO_SETTING_ENABLE_TELEMETRY="${PLATFORMIO_SETTING_ENABLE_TELEMETRY:-no}"

if [[ ! -d "$monophonic_repo/.jj" && ! -d "$monophonic_repo/.git" ]]; then
  monophonic_repo="$(mktemp -d)"
  git clone https://github.com/fczuardi/monophonic-instrument.git "$monophonic_repo"
  git -C "$monophonic_repo" checkout "$monophonic_commit"
fi

mkdir -p "$archive_dir"

"$pio_bin" pkg pack \
  "$monophonic_repo/packages/monophonic-instrument" \
  --output "$archive_dir"

"$pio_bin" pkg pack \
  "$monophonic_repo/packages/m5-tone-output" \
  --output "$archive_dir"
