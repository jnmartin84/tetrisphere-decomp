# Startup, threads, and frame boundary — read-only semantic findings

Recorded 2026-09-13. No source edits or renames performed.

Follow-up: [One input sample to board geometry](INPUT_SAMPLE_TRACE.md) traces
D-pad Left through buffering, processed-button history, repeat timing,
coordinate smoothing, and vertex emission. It establishes that the current
input fill row is excluded from consumption and that `func_800CD3B8` combines
gameplay-state progression with rendering.

## Scope and evidence

Read `SESSION_RESTART.md` first. Source references below are relative to
`/Users/jnmartin/landed_tsphere`, the preserved portable snapshot. Its provenance
records commit `823ca10873a7eafde7d68951087cdaf9d3095dfd`; a live canonical check
of `wr64vm:~/claude_tetrisphere` returned that same HEAD and only these tracked
changes:

```text
 D pending/session_8EEA4/.cm.txt
 M pending/session_97e3c/probe97.sh
```

`python3 /Users/jnmartin/landed_tsphere/check-package.py` passed: 1,032 files,
contents and executable modes intact. This pass analyzes source behavior; it
does not claim runtime timing, a new compilation, or a new linked-ROM match.
The current handoff supersedes old memory describing 857E8 as unfinished.

## Startup backbone

```text
tetrisphere.ld .entry -> asm/1000.s entrypoint
  clear BSS; set initial stack; jump to main
  main (boot.c:15)
    osInitialize; 16 raw PI reads
    create/start idleThread -> idle (boot.c:63)
      create PI manager and fault queue
      create/start faultThread -> fault
      create/start mainThread -> mainproc (boot.c:267)
        initialize asset cursor and two graphics-buffer pointer sets
        initScheduler (boot.c:435)
          VI manager; DMA and main queues
          osCreateScheduler -> create AND start thread 4 (__scMain)
          register main queue as scheduler client; retain command queue
          create SI/EEPROM queues
          create thread 5 (func_80029938), WITHOUT starting it
          initialize controllers
          initialize audio -> create/start thread 3 (func_8007EBDC)
          DMA graphics setup data; configure VI/framebuffer messages
          select context 1 through func_800AF09C
        clear EEPROM mirror and dirty flags; probe EEPROM
        start thread 5
        func_8007ACFC(first audio manager), then main message loop
      idle lowers itself to priority 0 and spins
```

- `tetrisphere.ld:34-40` links `build/asm/1000.o` at `0x80025C50`.
  `asm/1000.s:12-29` clears `0x72E20` bytes starting at `main_BSS_START`,
  sets `$sp` to the address named `mainThreadStack`, and jumps to `main`.
  This initial stack address is distinct from the later thread's stack-top
  argument `mainThreadStack + 0x2000`; preserve that distinction.
- `boot.c:19-27` clears the reset/readiness state, calls the real
  `osInitialize`, and reads 16 words from PI addresses `0xFFB000..0xFFB03C`
  into a local buffer. No later use of those words occurs in this function;
  their purpose remains unresolved.
- `boot.c:272-277` establishes asset allocation cursors at `D_80166F20`
  and buffer pointers in `D_800FACC0`. See persistent state below.
- `boot.c:442-471` clears `0x25800` halfwords beginning at `D_803B5000`,
  chooses PAL/NTSC/MPAL scheduler modes from `osTvType`, registers clients,
  initializes input and audio, and loads ROM ranges
  `[D_CD3F0,D_CD570)` and `[D_CD570,D_CD7C0)`.
- `boot.c:480-498` installs completion message type 2 and framebuffer
  pointers for both graphics slots, chooses an additional VI mode and
  applies features `0x42`. Exact meaning of the loaded setup data is deferred.
- `game2.c:14720-14753`: `func_800AF09C(1)` saves current context pointers
  and selects the first of two state/resource pointer sets. This is a context
  selection operation, not evidence that startup enters a named game mode.

## Threads

Priorities are the values passed by the source; stack arguments are recorded
literally rather than inferred from historical symbol names.

| Owner / ID | Entry | Priority | Creation/start and stack evidence |
|---|---|---:|---|
| `idleThread` / 1 | `idle` | 10, later 0 | `boot.c:26-27,70`; `idleThreadStack + 0x2000` |
| `faultThread` / 2 | `fault` | 50 | `boot.c:66-67`; `faultThreadStack + 0x400` (reserved BSS is larger) |
| `mainThread` / 6 | `mainproc` | 10 | `boot.c:68-69`; `mainThreadStack + 0x2000` |
| `D_800FDEF0.thread` / 4 | `__scMain` | 13 | `boot.c:449-456`, `sched.c:80-81`; `D_800FE180 + 0x2000`; starts within constructor |
| `schedThread` / 5 | `func_80029938` | 11 | Created `boot.c:464`, started `boot.c:291`; `schedThreadStack + 0x2000` |
| `D_80104CD0.thread` / 3 | `func_8007EBDC` | 12 | `audio.c:91`, `audiomgr.c:86-87`; stack argument `D_80106F58` |
| PI manager (SDK) | `__osDevMgrMain` | 150 | `boot.c:64`, `libultra/io/pimgr.c:74-75` |
| VI manager (SDK) | `viMgrMain` | 254 | `boot.c:446`, `sched.c:71`, `libultra/io/vimgr.c:64-66`; constant in `include/PR/os_thread.h:101` |

`schedThread` is an SI/controller/EEPROM service thread. The RSP/RDP scheduler
is the separate thread embedded in `D_800FDEF0`. SDK conditional auxiliary
paths were not audited as additional application threads.

`fault` binds `OS_EVENT_FAULT` to its queue, retrieves the faulted thread,
calls `func_8002B348` and `func_800D045C`, then spins (`boot.c:36-50`). Those
diagnostic helpers are outside this startup map.

## Queues and events

| Queue / capacity | Producers and payloads | Consumer / consequence |
|---|---|---|
| `D_800FAB68` / 200 | PI-manager requests | SDK PI manager; created in `idle` |
| `D_800FAB80` / 8 | Completion of DMA using `D_800F2298` | `dmaReady`, `dmaRomToRam`; `boot.c:385-410,447` |
| `D_80102340` / 1 | FAULT event, literal `0x10` | `fault`; `boot.c:39-46,65` |
| `D_800FDEF0.interruptQ` / 8 | VI 666, SP 667, DP 668, PRENMI 669 | `__scMain`; `sched.c:65-81,128-164` |
| `D_800FDEF0.cmdQ` / 8 (`D_800FE178`) | Graphics and audio `OSScTask *` | Scheduler drains it on retrace; `sched.c:120-122,181-183` |
| `D_800F22C8` / 8 | Scheduler retrace type 1, PRENMI type 4; graphics completion type 2 | `mainproc`, `func_8002A140`, `func_8002A218` |
| `D_800FABB8` / 16 | Scheduler retrace/PRENMI; SI completion pointer `&D_80102360` (type 3) | Thread 5; EEPROM probe also uses it before thread start |
| `D_800FAC10` / 16 | Temporarily redirected SI, `&D_80102380` (type 5); temporarily redirected scheduler-client notifications | Synchronous EEPROM operations inside thread 5 |
| `D_800FAC68` / 16 | Pointer to `D_800F2048`, request type 1 write or 2 read | Thread 5 polls once after each blocking receive on `D_800FABB8` |
| `D_80104CD0.frameMsgQ` (`D_80104E98`) / 8 | Scheduler retrace/PRENMI | Audio thread; `audiomgr.c:83-87,155-174` |
| `D_80104CD0.replyMsgQ` (`D_80104ED0`) / 8 | Audio task completion | Audio thread waits after successful task generation; `audiomgr.c:162-166,239-240` |

Message numbers are queue-specific. In particular, type 3 on the SI queue is
the application's controller-read completion message, despite an SDK macro
also assigning 3 to `OS_SC_RDP_DONE_MSG`. Event ID 5 is `OS_EVENT_SI`
(`include/PR/os_message.h:89`), not a thread or application message type.

Controller cycle (`boot.c:158-239`, `controller.c:15-55`):

1. Initialization uses a temporary SI queue for `osContInit`. It records
   connected ports in `D_800DF770` and returns `-1` upon finding a connected
   responsive controller; otherwise it returns the mask. Startup assigns that
   result to `D_801023A0`, used as the read-start gate.
2. On retrace, thread 5 clears a nonzero gate and calls `osContStartReadData`.
3. SI completion type 3 calls `func_8002AE0C`: retrieve pad data, and, when
   enabled, dispatch each connected port's buttons to `func_8006DF3C`.
   Error cases synthesize 0 or `0x1000` according to `D_800DFD5C`.
4. The worker sets the gate to 1 to permit another read.

EEPROM writes compare 64 blocks of 8 bytes against the 512-byte mirror
`D_800F2050`; `D_800F2250` marks changed blocks (`boot.c:88-108`). Reads load
all 64 blocks and refresh the mirror (`boot.c:188-207`). Requests use shared
globals for type and buffer pointer, not independent copied request objects.

Two exact details must remain visible in future analysis:

- `D_800FAC10` and `D_800FAC68` use the same `D_800FAC28` message array
  (`boot.c:462-463`). Record this literally; no correction is proposed.
- `D_8010018C` is the second word of the `OSScClient` at `D_80100188`:
  `asm/data/game_bss.bss.s:136-140`, `include/PR/sched.h:84-87`.
  Assigning it during EEPROM operations changes the scheduler client's queue
  as well as redirecting SI through `osSetEventMesg`. Restore/queue-manipulation
  code at `boot.c:183-186,203-206` is preserved as observed. Its broader
  concurrency behavior is not established here.

The service-loop guard is literally `readPending == 0 || writePending == 0`
under the current anonymous identifiers (`boot.c:213`); do not silently read
it as an AND. Case 10 only sets a local flag that is never tested. PRENMI type
4 has no explicit worker case. These observations are not invitations to fix
the shipped behavior.

## Persistent state encountered

| State | Established responsibility and evidence |
|---|---|
| `D_800F22C0`, `D_800F22C4` | Current asset allocation cursor and retained startup cursor. `boot.c:272-273,538-566`; mode loading restores the cursor in `main.c:12555,12586`. |
| `D_800FACC0` | Two graphics frame records, stride `0x1918`; task header, working area, list pointer, reply message, framebuffer pointer. `game2.c:26251-26321`. BSS labels split these records; labels are not whole-object size definitions. |
| `D_800E2AC0` | Graphics slot selector, toggled with XOR 1 after each build. `game2.c:26266,26309`. |
| `D_800DF720` | Outstanding graphics-task accounting: incremented when built; decremented when completion type 2 is consumed. Thus includes tasks whose completion may already be queued. `game2.c:26310`, `boot.c:303-305`. |
| `D_800DF710`, `D_800DF714` | Cumulative built-task / consumed-completion counts. Both start at 0 (`asm/data/BAAB0.data.s:19-23`); `util.c:18-21` waits until completed catches built. |
| `D_800DF718`, `D_800DF71C` | Last observed completion count and retraces without progress; diagnostic threshold `0x258`. `boot.c:215-224`. |
| `D_800F2050`, `D_800F2250`, `D_800DF754` | EEPROM mirror, dirty-block flags, probe result. `boot.c:280-287,88-108,169-207`. |
| `D_800F2048`, `D_800F204C`, `D_800DF740`, `D_800DF744` | Shared EEPROM request type, buffer, read pending, write pending. `boot.c:103-118,167-207`. |
| `D_800DF72C` | Enables scheduler PRENMI broadcast after thread 5 starts. `boot.c:20,161`, `sched.c:155-161`. |
| `leomecha_bss_0004` / `D_800DF728` | Same address `0x800DF728`, used as reset/PRENMI state. Assembly label in `BAAB0.data.s:35-36`; alias in `undefined_syms.txt:30`. Historical `type:func` metadata in `symbol_addrs.txt:236` is not behavioral evidence. Defer rename until alias scope is handled. |
| `D_800DF770`, `D_80102580`, `D_80102590`, `D_800DF778` | Controller mask, status array, pad data, dispatch enable. `controller.c:15-55`. |
| `D_800E1720`, `D_800E1CC0`, `D_800E1710`, `D_800E1714` | 180-entry, four-port current/previous button history and consumer/producer indices. `main.c:12150-12165,12292-12307`. |
| `D_800F2328`, `D_80104CD0`, three managers at `D_80107290`, `D_80108828`, `D_80109DC0` | Audio heap descriptor, task/thread/queue owner, persistent higher-level audio managers. Heap begins `D_802A2000`, size `0x113000`; `audio.c:71-118`, `audiomgr.c:49-87`. |

## Boundary of a normal cycle

The confirmed outer boundary is **one graphics-task build followed by
asynchronous execution and completion accounting**. It is not a guarantee of
one simulation update per retrace or per main-loop receive.

```text
main queue receive
  if outstanding < 2: func_800CCE7C(frameRecords)
    repeat builds until local slot count reaches 2
      select slot; capture/reset accumulated update count
      func_80070118(workingArea, frameRecord)
        drain buffered input -> func_8006E98C
          func_8006E418 per connected port/history entry
            conditionally func_800ACB94 for active player state
        prepare display list -> func_800CCB78
        refresh button snapshots -> func_8003E724
        dispatch current application state
          ordinary fallthrough: func_8006F52C; ...; func_800CD3B8
      append full-sync and end-list; build graphics task
      toggle slot; increment outstanding/built counts
    write back cache; enqueue each newly built task
  THEN handle received type (2 decrements outstanding; 4 handles PRENMI)

scheduler retrace -> drain command queue -> schedule RSP/RDP
SP/DP events -> clear task needs bits -> __scTaskComplete
  send completion pointer to main queue
  request framebuffer swap for final graphics task
```

Evidence: `boot.c:295-314`, `game2.c:26261-26321`,
`sched.c:167-249,270-288`. Completion message send precedes swap request in
the source; a VI swap request is not proof of when the image becomes visible.
Graphics submissions are nonblocking and their return values are ignored
(`game2.c:26317`), so the accounting description assumes successful enqueue.

`func_80070118` begins at `main.c:12758`. Its early-return paths include calls
to `func_8005C410`, `func_80064EBC`, `func_800685FC`, `func_8004C7E8`, and
`func_8003FE3C` under explicit state guards (`12768-12829`). Their precise
screen/mode names remain unassigned. After further transition branches, the
ordinary fallthrough calls `func_8006F52C` (`13222`) and then
`func_800CD3B8` (`13268`) before fade overlays. `func_8006F52C` can drain old
tasks and reload assets on state changes (`12539-12599`). Thus even this
fallthrough is not always a lightweight steady-state tick.

The buffered-input path is material to simulation: `func_8006E98C` snapshots
the producer index, drains history through `func_8006E418`, and the latter
conditionally invokes `func_800ACB94` on player state (`main.c:12274-12307`).
That function increments `D_800E4484` for context 1
(`game2.c:13577-13579`); the graphics builder captures and resets this value
BEFORE draining the next batch (`26268-26275`). Do not name it a VI counter:
initialization also writes it (`game2.c:26100`). A complete fixed-step timing
interpretation is deferred.

Independent retrace work occurs in scheduler context: `func_8006DC48`
updates countdowns, counters and interpolated values (`main.c:12033-12057`)
before scheduler task/client processing. Despite the scheduler file's opening
comment calling this an audio hook, the inspected body establishes timer and
transition-state work; it contains no direct audio call.

Audio runs independently: retrace -> `func_8007ED88` -> `alAudioFrame` ->
scheduler command queue -> reply wait (`audiomgr.c:155-166,211-258`). The
previous completed buffer is passed to `osAiSetNextBuffer` while preparing
the next task (`225-226`). Higher-level audio command/acknowledgment semantics
of `func_8007ACFC` remain a separate subsystem task.

## Next bounded investigation

1. Trace one active-player sample through `func_8006E418 -> func_800ACB94`,
   then relate its state writes to `func_800CD3B8` rendering. Preserve a
   distinction between input samples, simulation work, built tasks and retraces.
2. Establish the first post-startup screen using initialized state and the
   early guards in `func_80070118`, before assigning mode/screen names.
3. Resolve direct helper responsibilities and audio command acknowledgments
   only as that backbone reaches them. Leave allocator/SDK internals bounded.

## First rename candidates — all unapplied

| Old identifier | Proposed identifier | Confidence | Affected snapshot files |
|---|---|---|---|
| `func_80029938` | `controllerEepromThreadMain` | High | `src/boot.c` |
| `func_8002AD20` | `initControllers` | High | `src/boot.c`, `src/controller.c` |
| `func_8002AE0C` | `readAndDispatchControllerData` | High | `src/boot.c`, `src/controller.c` |
| `func_8006E98C` | `processBufferedControllerSamples` | High | `src/main.c` |
| `D_800DF720` | `pendingGfxTaskCount` | High | `src/boot.c`, `src/game2.c`, `asm/data/BAAB0.data.s` |

Meanings, evidence, exact occurrence lines, baseline file hashes, and reverse
old/new mappings are in [RENAME_CANDIDATES.json](RENAME_CANDIDATES.json).
No candidate-name collision or suffixed alias was found in the snapshot text
scan. No direct configuration/linker symbol-input occurrence was found for
these five names; repeat the inventory in the eventual isolated build.
Comments and strings in occurrence results are evidence, never substitution
targets. Preserve the differing signed/unsigned declarations of `D_800DF720`.

No source-edit worktree, rename validator, build, or matching experiment was
started. Existing useful names such as `mainproc` and `dmaRomToRam` can stay.
