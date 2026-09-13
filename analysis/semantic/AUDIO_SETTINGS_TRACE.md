# AUDIO settings -> live audio -> EEPROM -> gameplay

2026-09-13. Baseline 823ca10873a7eafde7d68951087cdaf9d3095dfd;
batch 008 extends semantic HEAD 123b082. Source line numbers are unchanged.
This is a source/data trace, not an emulator or hardware observation.

## Entry and the actual return path

`func_80054098` -> **updateAndDrawAudioMenu** (src/main.c:6127-6454).
It is shared by the front menu (4489-4492) and the pause handler (1870-1873).
Pause's AUDIO selection sets D_800E122A to 2 and D_800E1228 to 0 after
its closing transition, then clears the screen clocks (1940-1943).
On the next build, updateAndDrawPauseMenu delegates to this screen.

Initialization waits for old graphics tasks, resets allocation to the common
screen-resource endpoint and loads audio-screen images/animations. It copies
the current main music player's song ID D_8010880C into D_800E0B24, then
uses the shared snapshot/transition initializer (6127-6181). Merely opening
this screen copies the current ID to the selector; it does not itself save
that copied value. Drawing/input are staged behind screen-clock and opacity
gates, including a 60-count gate before the settings controls.

This screen uses D_800DFD98, the combined press/repeat mask, rather than
pause's owner-port mask. func_8003E724 ORs all four controller words before
edge detection and adds direction repeats (main.c:1269-1377). Thus AUDIO
is not restricted to the controller that opened pause. Down/up wrap rows
0..2; left/right change the selected setting.

**Closing AUDIO from pause resumes gameplay directly.** A/Z/Start or B
request the closing transition (6436-6453). When it reaches state zero,
the handler sets D_800E1228=-1 and clears D_800E122A if nonnegative
(6188-6198). The pause handler returns immediately after the call; the outer
updateAndBuildFrame sees negative selection and clears D_8013FAD0 in the
same build (12817-12829). Gameplay's resource-resume path runs on a later
build. There is no intervening redraw of the pause menu. Earlier notes
proposed tracing a return to pause; this establishes the actual behavior.

The front-menu context has separate exits: with D_800E122A negative,
A/Z/Start clear the screen clocks, selection and D_800E1220 immediately;
B requests the closing transition plus func_8003F8D8. The containing front
menu resumes once its audio selection is negative. Do not collapse these
context-dependent paths into a single generic back action.

## Settings and immediate effects

| Row | State | Behavior |
|---|---|---|
| 0 | D_800E0B1C, range 0..12 | Thirteen-position effects/music balance; left/right clamp at endpoints |
| 1 | D_800E0B20, range 0..2 | AUTO / RANDOM / CHOOSE, wrapping in either direction |
| 2 | D_800E0B24 | Selects and immediately starts a song; selection wraps |

Mode strings are data-backed: BAAB0.data.s:3182-3185 points to
D_800ECB10/18/20, whose C7340.data.s:1340-1354 strings are AUTO, RANDOM,
CHOOSE. The track-name table at D_800E0B28 begins with song 0,
PROPHETIC - TITLE, then song 1, AZULE LUX (C7340.data.s:812-820).
The mode is music selection policy, not stereo/mono output. At gameplay
music selection, mode 1 chooses a random ID in 1..D_800E28E4 and mode 2
uses D_800E0B24 (game2.c:5061-5067). Other screens choose their usual song
unless CHOOSE is active (for example main.c:2324-2329).

For balance value n, row 0 supplies min(n*0x1556, 0x7FFF) to
func_80079BD4 and min(0xA008-n*0xD56, 0x4FFF) to func_80079B80 for the
main music player. The first rebuilds a 256-entry effects-volume lookup:
D_80104910[i] = sqrt(i)*gain/16 (audio_engine.c:55-67), consumed by the
effects player at 1845-1847/2020. The second sets a player volume and dirty
flag, with the existing +0x2000 adjustment for song IDs 14..99 preserved
(audio_engine.c:34-44). Therefore the slider increases effects gain while
reducing music gain; it is not a master-volume control. At n=6 both base
gains have reached their respective caps. These formulas describe engine
values, not measured loudness. The game-owned square-root table builder is
a further math naming candidate; no audio-engine source changes this batch.

Selecting a track calls func_8007F720 followed by func_8007ACFC, temporarily
setting D_800DFE84. The former loads/prepares the requested song, with early
out cases (audio.c:224 onward); the latter requests player start and waits
for its audio-thread acknowledgement where needed (audio_engine.c:415-440).
The menu then sets a 15-handler-call input delay, not a retrace countdown.
Do not infer that every track change requires a reload when the current
song already matches. Screen timers can freeze during these operations.

Pause's selector excludes song zero: it wraps within 1..D_800E28E4.
The front-menu selector permits zero only when mode is not CHOOSE.
Switching mode to CHOOSE while the selector is zero forces song 1, starts
it and saves that selection (main.c:6357-6386).

## Immediate persistence request, deferred physical write

Each accepted left/right adjustment updates the save buffer and calls
**requestSaveDataWrite** (`func_80066E6C`). Balance and music mode share
byte D_80102918[0x1F0]: low nibble balance, high nibble mode. Song choice is
byte [0x1F1]. There is no Apply action or rollback on B. The menu requests
persistence at the point of change, before exit (main.c:6310-6433).

**computeSaveDataChecksum** (`func_80066DB8`, main.c:10744-10755) starts
at 0x25 and visits 127 native big-endian u32 words, computing
`sum = word + rotate_left_32(sum, 3)` modulo 2^32. These are the first
508 bytes of the 512-byte image. The wrapper stores the checksum at
D_80102B14, exactly image offset 0x1FC, then calls the EEPROM requester
(10767-10770). This is a rotate/add checksum, not a CRC.
The wrapper is shared with other saved-state edits, including deletion of
a saved slot (10734-10740); it is not specific to audio settings.

**requestEepromWrite** (`func_80029780`, boot.c:88-109) compares 64 blocks
of 8 bytes against the RAM shadow D_800F2050, marks each differing block
in D_800F2250, then copies all 512 bytes to that shadow. If EEPROM was
detected by the startup probe, it installs the supplied pointer and type-1
request in shared state, sets the busy flag and sends a nonblocking message
to D_800FAC68. It does not wait for storage completion or check send success.
The shadow represents the requested contents; it is not proof of a durable
write. Dirty flags are accumulated, not cleared for equal blocks here.

controllerEepromThreadMain processes that queue after waking on its regular
event queue (boot.c:165-193). It redirects SI events, walks marked blocks,
clears each mark before osEepromWrite, waits for SI completion after a
successful call, then clears the busy flag and restores SI routing. The
worker reads the shared supplied pointer, not an immutable queued copy.
An EEPROM error breaks the loop; the existing error/queue semantics are
preserved. The names describe a request, not guaranteed successful storage.

Startup verification (main.c:10890-10943) checks the checksum and H2O
signature, then restores the saved balance/mode/track and reapplies the
same volume formulas. Default initialization stores balance 6, AUTO mode
and song 0 (10850-10872). This completes the settings-to-save-to-load path
without auditing every record field or claiming hardware acceptance.

## Batch and next direction

Four names, 33 new identifier tokens: 32 in main.c, one in boot.c.
Cumulative: 22 function names, 89 tokens across six source files.
All 997 production inputs were inventoried; the only extra substring hits
are historical comments, which remain byte-identical. No aliases or build
configuration changes are needed. See batch_008.json and its validation
and whole-ROM evidence for acceptance.

Next main-loop path: pause EXIT -> func_8005C978 and its saved-game prompt,
now with the persistence request boundary established. The effects-volume
square-root lookup remains an optional game-owned math follow-up. Shared
menu globals, record layouts and audio-player signatures remain unrenamed.
