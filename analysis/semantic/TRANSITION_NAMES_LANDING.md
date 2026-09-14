# Transition gates and effect names: batch 014

Five names from TRANSITION_GATE_TRACE.md are now applied. This is a descriptive
semantic batch against 0a913fa: 24 identifier replacements across game2.c and
main.c, preserving every other source byte, including comments and expressions.

| Old identifier | New identifier | Supported meaning |
| --- | --- | --- |
| func_800C2EF4 | updateEndSequenceState | Countdown, gated accumulator update and phase dispatch |
| func_800C3058 | updateAndDrawEndSequenceFade | Per-player fade drawing plus threshold-related state changes |
| func_800C5CFC | startTornadoEffect | Diagnostic names tornado size; sets variant and creates effect animation |
| D_80139E68 | gEndSequenceDelay | Shared end-sequence progression delay, not a per-player field |
| func_800B9134 | hasPauseBlockingPlayerEffects | Current-mode player effect/transition checks used by Start/pause admission |

These names describe observed roles, not recovered original C spelling.
The pause predicate checks player 1, adds player 2 in two-player mode, and
includes the single-player heart/skull animation flag. It is not the whole pause
policy. The end-sequence updater preserves separate phase tests and re-reads, the
phase-5 special path, and the existing progression flag. Delay units are not
asserted. The fade helper's state writes remain intact. Tornado variants 1 and 3
are both used by current callers.

The narrower func_800B9090 and progression flag D_80130A26 remain unchanged;
neither has been mislabeled as active-drop count or animation completion.
No active assembly/linker inputs needed edits. Historical evidence and comments
retain their earlier identifiers. The trace document preserves the pre-rename
research snapshot; this landing supersedes its notes-only status for these five.

Validation: pristine and candidate FULL MATCH; independent cmp of all 8,388,608
ROM bytes including the header; all five linked addresses unchanged. The lexical
guard verifies inverse source restoration and 995 production inputs. The existing
guard is unchanged, so no additional tests were needed. Detailed evidence is in
batch_014.json, batch_014_validation.json and batch_014_verification.json.

```sh
python3 tools/semantic/identifier_renames.py --ledger analysis/semantic/batch_014.json
PATH=/opt/homebrew/bin:$PATH ./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
```

Source and text evidence only; no binary artifacts are staged. The user manages
GitHub pushes. No remote state was queried or modified for this local batch.
