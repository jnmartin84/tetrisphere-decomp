# Audio data names: batch 012

Diagnostics identify five sample-metadata members and two animation-audio player
instances. This batch applies 179 identifier substitutions against e56cdd8 in
seven C files and the two corresponding BSS dlabels. All other production bytes,
including layout directives, comments, whitespace and expressions, are preserved.

| Previous identifier | New identifier | Scope |
| --- | --- | --- |
| unk0 | sampleLength | StructE784 only, +0x00 |
| unk4 | loopBegin | StructE784 only, +0x04 |
| unk8 | loopEnd | StructE784 only, +0x08 |
| unkC | flags | StructE784 only, +0x0C |
| unkE | sampleId | StructE784 only, +0x0E |
| D_80108828 | gAnimPlayer | All active C uses and BSS definition |
| D_80109DC0 | gAnimPlayer2 | All active C uses and BSS definition |

The member spellings normalize diagnostic vocabulary; they are not a claim of
exact original C spelling. The globals correspond to ANIMPLAYER and ANIMPLAYER2
in direct address comparisons. They are audio managers, separate from LWInfo.
Sample-length units, flag bits and the full metadata format remain unverified.
The retained diagnostic printer has no located incoming C call, and its output
sink is empty. We preserved its behavior and did not infer another record layout.
Other structs' similarly spelled unk fields are unchanged. Player-state offsets,
blank-piece structure recovery and the less direct flag candidates remain notes.

The existing file-wide guard cannot safely rename shared unk member spellings or
BSS dlabels. A separate scoped guard therefore validates each reviewed token at
its baseline byte offset, rejects edits to comments/literals/non-label assembly,
and verifies inverse restoration. It also checks all 995 production inputs and
preserves the prior guards unchanged. Four targeted tests cover selected scopes,
protected text, assembly labels, and variable-length/overlapping edits; all 28
existing and new guard tests pass. The ledger is not a C binding/type checker:
the selected StructE784 declaration and printer accesses were reviewed directly.

Both pristine and renamed builds returned FULL MATCH; full cmp includes the
64-byte header. All 8,388,608 ROM bytes match. gAnimPlayer remains at 0x80108828,
and gAnimPlayer2 remains at 0x80109DC0. See batch_012_verification.json.
DATA_STRING_SEMANTICS.md preserves the earlier research snapshot; this landing
supersedes its notes-only status for the seven names in the table.

Recheck on the provisioned macOS host:

```sh
python3 tools/semantic/scoped_identifier_renames.py --ledger analysis/semantic/batch_012.json
PATH=/opt/homebrew/bin:$PATH ./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
```

No binary artifacts belong in the commit. User handles GitHub pushes; remote
state was not queried or changed for this local landing.
