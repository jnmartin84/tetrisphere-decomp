# Connections clarified by batches 010–012

Read-only synthesis, 2026-09-13; local published source at ce93c6c, clean.
No source edits or remote operations. Findings below were checked against current
source; they combine earlier observations with newly explicit names.

## Drop work and the deferred win transition

AllocDropPiece (game2.c:5455) increments player-state +0x25CA and initializes an
entry in the 64-slot, 0x14-byte-stride table at +0x25CC. The frame driver calls
PlacePieceGame on due slots at line 26563; its result becomes the next delay.
The release helper func_80092238 at line 5469 deactivates the record and decrements
the active count, with the existing sentinel behavior preserved.

PlayerWon (line 13162) calls Begin_WinAnim. Begin_WinAnim (22326) refuses to begin
while +0x25CA is nonzero, and its diagnostic explicitly says drop pieces are
still happening. It arms +0x23B4 and sets +0x23B6 to 0x1E. The frame driver at
26416–26425 counts this timer down when the pending-action field +0x24A6 is zero
and func_800B9090 returns zero; expiration calls PlayerWon again. Pending action
can extend the timer to 0x3C. This supports deferred/retried win initiation until
gameplay work settles, not an unconditional immediate transition on detection.
The exact domain of func_800B9090 is still untraced in this study.

This also distinguishes the active drop-operation count +0x25CA from the separately
printed DropPieces value +0x25C6 and PiecesLeft value +0x25C4.

## Audio startup gates visual advancement

code_4D170.c:2068 computes the advancement argument for LWPlayAnimation using
gAnimPlayer +0x1594. When this byte and D_801026C2 are both zero, it passes zero
advancement; otherwise it computes the visual counter delta. Preserve the
LWPlayAnimation zero-step initialization special case: this is not a blanket
claim that zero means no work at all.

audio_engine.c:646 identifies +0x1594 in its BMgr view as wbFlag. At lines 793–799,
the audio consumer reads a byte from its ring, advances counters, sets this flag
on the first such consumption, and calls osWritebackDCacheAll. loadsong clears
the field before preparation (audio.c:279). This connects a consumer-started/cache
flag with the visual advancement gate. It supports startup coordination, not
proof of sample-accurate continuous synchronization or hardware audio output.
The bypass D_801026C2 and full timing contract remain unresolved.

The visual completion path at code_4D170.c:2069–2093 stops the animation-audio
manager, resets state, and loads audio ID 0x140 through loadsong. Thus these renamed
symbols make an actual cross-subsystem handoff legible.

## End-sequence visual runtime versus audio manager

Begin_WinAnim's ordinary branch calls func_800C3AD8 (game2.c:22376).
That helper conditionally starts gAnimPlayer, aligns the game-owned arena,
constructs an LW runtime with LWAllocateMemory, and stores its address in
D_80130A20 (line 22392). It advances the arena cursor by the returned byte count.
func_800C3C10 passes D_80130A20 to LWPlayAnimation (22411) and uses completion to
advance phase flags in one branch. Together with the literal 'Starting win/lose
animation', this strongly identifies D_80130A20 as the end-sequence LW runtime
instance and clarifies the two neighboring helpers' setup/playback roles.
Their full mode gates are retained; the setup helper has a two-player early exit.

## Earlier math helpers now sit in a named lighting path

LWPlayAnimation calls func_80030EB4. At code_8170.c:1372–1386, that helper reads
the animation light count and +0x10 lightinfo entries (named by ROM diagnostics),
rotates the vector (0,0,120) through rotateVectorZXYDegrees and
rotateVectorYXZDegrees, and writes signed-byte directions to the selected
lights[0]/lights[1] storage. It enables G_LIGHTING when the count is nonzero and
clears it otherwise. This strengthens the role of func_80030EB4 as constructing
the current animation's light directions and configuring lighting. Exact rotation
field names and coordinate-space terminology require further tracing.

The paired light storage follows the selector at +0x3D, which LWPlayAnimation
toggles. This is concrete producer evidence supporting alternating light buffers;
do not generalize that conclusion to every paired runtime field without its uses.

## Next candidates, not applied

D_80130A20 and the end-sequence setup/playback helpers now have stronger semantic
evidence. func_80030EB4 is a strong light-direction helper candidate. The player
counter/timer offsets and audio +0x1594 are useful data notes, but exact naming
should preserve the distinctions above. No new names were applied in this walk.
