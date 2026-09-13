# Pause EXIT -> ranked records -> front menu

2026-09-13. Baseline 823ca10873a7eafde7d68951087cdaf9d3095dfd;
batch 009 extends semantic HEAD 5d0ea38. All source references below are
src/main.c unless stated. Source line numbers remain unchanged.

## Correcting the proposed save-prompt interpretation

The previous restart point proposed a save prompt at func_8005C978.
Its code instead displays four top-five record tables. There is no Yes/No
save confirmation on this path. In eligible single-player modes, pause
EXIT first calls the ranked insertion helper. A qualifying result is
inserted and persistence requested before the records screen opens.
A nonqualifying result, other modes, and multiplayer bypass this screen.

updateAndDrawPauseMenu (2033-2065) handles EXIT selection 3 as follows:

| Game mode | Record page | Label | Ranking |
|---|---|---|---|
| 1 | 0 | RESCUE | Higher score first |
| 5 | 1 | HIDE&SEEK | Higher score first |
| 4 | 2 | PUZZLE | Lower elapsed time first; not inserted by pause EXIT |
| 2 | 3 | TIME TRIAL | Higher score first |

The page labels are verified from D_800E10CC, asm/data/BAAB0.data.s:
3099-3103, and pointed-to strings in C7340.data.s:1082-1102.
Puzzle insertion is reached by a results path which supplies
D_80112D2C/60 (6857-6860), not by pause EXIT. Other callers share the same
ranked insertion helper, including default-record initialization.

EXIT uses the current player's existing name and D_80112D18. If insertion
returns 1, it selects the relevant page, clears screen clocks and sets
D_800E0760=0x4B0 (1200) for timed dismissal. No new-name prompt occurs here.
It returns before the ordinary pause closing animation. A later build sees
D_800E122C nonnegative and delegates to the records screen.

## Ranked insertion and persistence

`func_800658A8` -> **insertRankedRecord** (10354-10421).
It clears D_800E0764, maps the mode to a five-entry base, and scans past
strictly better existing values. Unsupported modes or falling beyond
fifth place return 0. Equal values qualify and are inserted before existing
equals; there is no name-based duplicate rejection in this helper.
Comparisons are unsigned u32. The fourth argument is unused and retained.

Lower ranks shift down from the bottom. For each entry it moves a six-byte
packed name and one u32 value, dropping the old fifth entry. It encodes the
new name, stores the result, sets D_800E0764=base+rank for highlighting,
and calls requestSaveDataWrite when D_800E1608 is nonzero. Return 1 means
insertion into RAM, not verified EEPROM completion. The checksum and
asynchronous block-write boundary are documented in AUDIO_SETTINGS_TRACE.md.

The record layout occupies the start of the 512-byte save image:

| Offset from D_80102918 | Contents |
|---|---|
| 0x004..0x07B | Twenty packed names, six bytes each |
| 0x07C..0x0CB | Twenty u32 score/time values |

Initialization (10818-10833) seeds high-score tables with zero and the
low-time table with 1,000,000, disables D_800E1608 around twenty calls that
insert built-in records, then reenables it. Default save initialization
later issues the shared save request. Therefore the insertion name must
not imply that every call immediately queues a write.

## Display and return to front menu

`func_8005C978` -> **updateAndDrawRecordsMenu** (8232-8393).
Initialization waits for graphics completion, loads display resources,
selects ordinary menu music unless CHOOSE overrides it, and starts the
shared captured-frame transition. It renders five names and values for
the chosen page. The current inserted index pulses in the highlight color.

For PUZZLE, values are rendered as minutes and two-digit seconds. Other
pages append a decimal zero and group digits with spaces, so the displayed
score is ten times the stored integer (8310-8340). Keep this display scaling
separate from the sorting values.

Like AUDIO, the records screen uses combined-controller D_800DFD98.
Left/right wrap pages 0..3 and disable timed dismissal. A/Z/Start dismiss
immediately by making page/selection negative and clearing clocks and
highlight. A positive timer expires by the sampled difference between
screen counters, then uses the same dismissal path. It is initialized to
1200 counter units, not 1200 rendered frames. Counting only happens after
the opening/drawing gates; no exact wall-clock duration is asserted.
B requests the shared closing transition and disables the timer; the page
becomes negative when transition state reaches zero (8268-8276).
These inputs never roll back an inserted record.

On return, pause's subordinate branch (1857-1869) restores the remembered
front-menu selection D_800E0754[0] into D_800E121C and clears subordinate
selections and screen clocks. The outer dispatcher clears D_8013FAD0 when
pause selection becomes negative. On the next build, D_800E121C's front-menu
branch wins ahead of gameplay (12812-12816). Its initialization clears the
two player runtime blocks (4501-4509); this path is an exit, not a resume.

If no record qualified, ordinary pause closing instead sets D_800E121C
and clears submenu selections when the transition finishes (1920-1927),
then makes pause selection negative. It reaches the same front-menu branch.
The records menu is also directly callable from the front-menu dispatcher
(4485-4488) and other results screens; its name is not pause-specific.

## Eight-character names in six bytes

`func_800651E4` -> **packPlayerName** (10204-10261).
It reads exactly eight source bytes, converting characters to codes by
subtracting 0x20, with NUL represented by 0x3F. From the first 0x3F code
onward all slots are padded to 0x3F. Four six-bit slots become three bytes,
low bits first; two such groups store the eight-character name in six bytes.
Underscore maps to the padding code too. The representable nonpadding range
is 0x20..0x5E; there is no arbitrary-text validation or clamping here.

`func_800654C8` -> **unpackPlayerName** (10263-10296).
It extracts eight six-bit codes, adds 0x20 and converts resulting underscore
bytes to NUL. It writes exactly eight bytes, not a ninth terminator; the
record-screen caller explicitly sets byte 8 to zero (8347-8348). Unlike the
packer, the decoder does not propagate padding through later slots in an
arbitrary malformed packed input. Preserve these bounded-buffer contracts.

These helpers also store/load the remembered name at save offset 0x1A4,
the eight player-name choices beginning at 0x1AC, and names in the separate
progress-slot area (10304-10344, 6564-6568). That caller evidence supports
player-name naming rather than a generic string-compression claim.

## Boundary and continuation

The eight named progress slots are a separate structure beginning near
save offset 0x0CC, with names at 0x0D0 and a 0x14-byte stride.
func_800660B8 finds or allocates a slot by packed name and changes progress
fields; it is not called by pause EXIT's ranked-insertion branch. Its
mode-dependent fields and exact progression rules need a separate audit.
No resumable board snapshot is established by this EXIT trace.

Next bounded path: func_800660B8 progress updates and their readback through
func_80055A80 and func_80065EDC. Confirm further readback targets
before assigning broad save/load names. Shared fields remain unchanged.

Batch 009 adds four function names and 49 identifier tokens, all in main.c.
Cumulative: 26 function names and 138 substitutions across six source files.
All 997 production inputs were inventoried; one historical comment retains
its original identifier spelling. See batch_009.json and accompanying
lexical/linked-ROM evidence. No emulator or hardware session was run.
