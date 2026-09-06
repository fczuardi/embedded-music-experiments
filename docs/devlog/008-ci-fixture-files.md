# Slice 008: CI Fixture Files

The contracts CI used to generate small C++ programs inside the workflow YAML.
That was acceptable as a smoke test, but it made the contract checks harder to
read and easier to forget when the interface changed.

This slice moves those snippets into versioned files:

```text
firmware-contracts/test/check_note_event.cpp
firmware-contracts/test/check_instrument_event_sink.cpp
```

The workflow now only compiles and runs those files with `g++`. The checks still
prove the same contract behavior: note events can be constructed, and a consumer
can implement `InstrumentEventSink` with note, pitch bend, and disconnect
handlers.

Keeping the fixtures in the repository gives us syntax highlighting, ordinary
diffs, and a clearer place to extend contract tests as more event types appear.
