# Slice 031: Showcases Use PlatformIO Registry Packages

## Goal

Stop requiring local tarball archives for the packages already published to the
PlatformIO Registry.

## Change

Both current showcases now consume:

```ini
fcz2/monophonic-instrument@0.1.2
fcz2/m5-tone-output@0.1.2
```

instead of:

```ini
monophonic-instrument=file://../../.tmp/monophonic-instrument-0.1.1.tar.gz
m5-tone-output=file://../../.tmp/m5-tone-output-0.1.2.tar.gz
```

The normal `just showcase-build` and `just showcase-upload` paths no longer run
`scripts/prepare-showcase-archives.sh`, and CI no longer prepares local
archives before building showcases.

## Rationale

The registry dependency path is closer to the intended plug-and-play package
ecosystem:

```text
showcase
-> PlatformIO Registry packages
-> package manifests and normal dependency resolution
```

This keeps the umbrella focused on compositions instead of rebuilding sibling
package tarballs as part of every showcase build.

## Verification

```sh
just showcase-build 1
just showcase-build 2
```

No new hardware verification was performed in this slice. The firmware behavior
should match the previously validated showcase builds because the Registry
packages contain the same versions that were already being consumed locally.

## Limits

`ble-midi-input` still comes from the `midi-receiver` Git repository by pinned
commit. Publishing that package to the PlatformIO Registry is the next cleanup
step in this dependency chain.
