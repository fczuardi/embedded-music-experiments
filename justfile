set dotenv-load := false
set shell := ["bash", "-eu", "-o", "pipefail", "-c"]

showcase_archives := "scripts/prepare-showcase-archives.sh"

# Show available commands.
default:
    @just --list

# List available showcase ids.
showcase-list:
    @printf '1\tble-midi-buzzer\tshowcases/ble-midi-buzzer\n'
    @printf '2\tble-midi-core-gray-speaker\tshowcases/ble-midi-core-gray-speaker\n'
    @printf '3\tble-midi-amy\tshowcases/ble-midi-amy\n'

_showcase-path id:
    @case "{{id}}" in \
      1) printf '%s\n' 'showcases/ble-midi-buzzer' ;; \
      2) printf '%s\n' 'showcases/ble-midi-core-gray-speaker' ;; \
      3) printf '%s\n' 'showcases/ble-midi-amy' ;; \
      *) printf 'Unknown showcase id: %s\n' "{{id}}" >&2; exit 2 ;; \
    esac

_showcase-env id:
    @case "{{id}}" in \
      1) printf '%s\n' 'm5stick-cplus2' ;; \
      2) printf '%s\n' 'm5stack-core-gray' ;; \
      3) printf '%s\n' 'm5stack-core-gray' ;; \
      *) printf 'Unknown showcase id: %s\n' "{{id}}" >&2; exit 2 ;; \
    esac

_showcase-board id:
    @case "{{id}}" in \
      1) printf '%s\n' 'm5stick-cplus2' ;; \
      2) printf '%s\n' 'm5stack-core-gray' ;; \
      3) printf '%s\n' 'm5stack-core-gray' ;; \
      *) printf 'Unknown showcase id: %s\n' "{{id}}" >&2; exit 2 ;; \
    esac

# Build a showcase firmware. Defaults to showcase 1.
showcase-build id="1":
    @showcase="$(just _showcase-path {{id}})"; \
      pio run -d "$showcase"

# Build Showcase 3 and enforce its measured memory budget.
showcase-budget:
    scripts/check-amy-memory-budget.sh

# Upload a showcase firmware to the connected device. Defaults to showcase 1.
showcase-upload id="1":
    @showcase="$(just _showcase-path {{id}})"; \
      env_name="$(just _showcase-env {{id}})"; \
      board="$(just _showcase-board {{id}})"; \
      scripts/upload-showcase.sh "$board" "$showcase" "$env_name"

# Open a showcase serial monitor. Defaults to showcase 1.
showcase-monitor id="1":
    @showcase="$(just _showcase-path {{id}})"; \
      env_name="$(just _showcase-env {{id}})"; \
      pio device monitor -d "$showcase" -e "$env_name"

# Detect the connected ESP32 board family.
probe-board:
    scripts/probe-esp32-board.sh detect

# Pack local package archives consumed by showcases.
showcase-archives:
    {{showcase_archives}}
