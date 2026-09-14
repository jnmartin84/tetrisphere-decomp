# Animation connections: batch 013

This batch makes the end-sequence setup/playback relationship and the animation
lighting path visible in source names. It applies 17 identifier substitutions
against ce93c6c across src/game2.c and src/code_8170.c. Every other source byte is
preserved. These are evidence-supported descriptive names, not recovered original
C spellings. The earlier POST_RENAME_CONNECTIONS.md records the supporting trace.

| Old identifier | New identifier | Evidence |
| --- | --- | --- |
| D_80130A20 | gEndSequenceAnimation | Receives LWAllocateMemory result in end-sequence setup; consumed by LWPlayAnimation; cleared in reset |
| func_800C3AD8 | startEndSequenceAnimation | Conditionally starts animation audio, creates visual instance, advances arena cursor and sets sequence delay |
| func_800C3C10 | updateAndDrawEndSequenceAnimation | Main graphics path invokes it; calls LWPlayAnimation and responds to phase-6 completion |
| func_80030EB4 | buildAnimationLightDirections | Reads lightinfo rotations, writes selected lights buffer and sets/clears G_LIGHTING |

The start helper has callers from both winning and losing paths, including the
'Killing player' path at game2.c:22205. Its existing two-player early return and
mode gates are preserved. The global retains its s32 declaration even though it
stores an address. Neither helper is generalized beyond its observed mode gates.
The lighting helper's name does not imply a proven world/view coordinate space.

Useful source reading points after the rename:

- game2.c:22374: Begin_WinAnim calls startEndSequenceAnimation.
- game2.c:22392: startEndSequenceAnimation assigns gEndSequenceAnimation.
- game2.c:22411: updateAndDrawEndSequenceAnimation plays that same instance.
- game2.c:27084: the frame graphics path invokes the playback helper.
- code_8170.c:442: LWPlayAnimation calls buildAnimationLightDirections.

No active assembler/linker symbol inputs required edits; the global is defined
in C. Historical comments and evidence keep old names. Player-state offsets,
the audio startup flag and other uncertain data names remain research notes.

Pristine and candidate builds both returned FULL MATCH. Independent full-ROM cmp
includes the 64-byte header, and all four linked addresses are unchanged. The
identifier guard verifies inverse source restoration and all 995 input hashes.
See batch_013.json, batch_013_validation.json and batch_013_verification.json.
No new tests are needed for the unchanged, already-tested guard.

```sh
python3 tools/semantic/identifier_renames.py --ledger analysis/semantic/batch_013.json
PATH=/opt/homebrew/bin:$PATH ./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
```

This is a local source-and-text-evidence landing. No binary artifacts are staged.
The user manages GitHub pushes; this batch does not query or change remote state.
