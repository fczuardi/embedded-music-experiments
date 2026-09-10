# Relative workspace paths

## Goal

Make umbrella development commands portable across checkout locations and
remove the remaining `/home/fcz` assumptions from operational files.

## Design

The showcase archive script derives the workspace root from the umbrella
checkout and still accepts `WORKSPACE_ROOT` for an intentionally different
layout. Generated archives remain in the repository-local `.tmp/` directory
through `ARCHIVE_DIR`.

The board probe remains in this repository as the canonical workspace tool;
`midi-receiver` consumes it through `M5_WORKSPACE_TOOLS_DIR` instead of carrying
a duplicate copy.

Paths embedded in older devlogs are historical commands and are preserved as
experiment records. Current scripts, recipes, and README instructions no
longer require a particular machine username or checkout root.

## Verification

- `bash -n scripts/prepare-showcase-archives.sh scripts/probe-esp32-board.sh`
- `just showcase-archives`
- `rg` audit for machine-specific paths in operational files

Hardware behavior is unchanged and was not revalidated by this documentation
and tooling slice.
