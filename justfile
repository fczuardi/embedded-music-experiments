set dotenv-load := false
set shell := ["bash", "-eu", "-o", "pipefail", "-c"]

# Show available commands.
default:
    @just --list

# List available showcase ids.
showcase-list:
    @printf '1\tble-midi-buzzer\tshowcases/ble-midi-buzzer\n'

_showcase-path id:
    @case "{{id}}" in \
      1) printf '%s\n' 'showcases/ble-midi-buzzer' ;; \
      *) printf 'Unknown showcase id: %s\n' "{{id}}" >&2; exit 2 ;; \
    esac

# Build a showcase firmware. Defaults to showcase 1.
showcase-build id="1":
    @showcase="$(just _showcase-path {{id}})"; \
      pio run -d "$showcase"

# Upload a showcase firmware to the connected device. Defaults to showcase 1.
showcase-upload id="1":
    @showcase="$(just _showcase-path {{id}})"; \
      pio run -d "$showcase" --target upload

# Open a showcase serial monitor. Defaults to showcase 1.
showcase-monitor id="1":
    @showcase="$(just _showcase-path {{id}})"; \
      pio device monitor -d "$showcase"
