/*
 * Scheduler — based on SDK libultra/sched/sched.c, adapted to the older
 * version Tetrisphere shipped with (plus H2O customizations: retrace
 * audio hook, PRE-NMI gating, RDP watchdog globals, boot thread destroy).
 */
#include <assert.h>
#include <PR/ultralog.h>
#include <PR/sched.h>

static OSScTask *__scTaskReady(OSScTask *t);
static s32      __scTaskComplete(OSSched *sc, OSScTask *t);
static void     __scAppendList(OSSched *sc, OSScTask *t);
static void     __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp);
static void     __scYield(OSSched *sc);
static s32      __scSchedule(OSSched *sc, OSScTask **sp, OSScTask **dp,
                             s32 availRCP);
void __scMain(void *arg);
void __scHandleRetrace(OSSched *sc);
void __scHandleRSP(OSSched *sc);
void __scHandleRDP(OSSched *sc);

#define VIDEO_MSG       666
#define RSP_DONE_MSG    667
#define RDP_DONE_MSG    668
#define PRE_NMI_MSG     669

#define OS_SC_DP                0x0001  /* set if still needs dp        */
#define OS_SC_SP                0x0002  /* set if still needs sp        */
#define OS_SC_YIELD             0x0010  /* set if yield requested       */
#define OS_SC_YIELDED           0x0020  /* set if yield completed       */

#define OS_SC_DRAM_DLIST        0x0004

#define OS_SC_XBUS      (OS_SC_SP | OS_SC_DP)
#define OS_SC_DRAM      (OS_SC_SP | OS_SC_DP | OS_SC_DRAM_DLIST)
#define OS_SC_DP_XBUS   (OS_SC_SP)
#define OS_SC_DP_DRAM   (OS_SC_SP | OS_SC_DRAM_DLIST)
#define OS_SC_SP_XBUS   (OS_SC_DP)
#define OS_SC_SP_DRAM   (OS_SC_DP | OS_SC_DRAM_DLIST)

void updateScreenTimersOnRetrace(void);
extern u8  D_800DF72C;
extern s32 D_800DF728;
extern s32 D_800DF70C;
extern s32 D_800DF704;
extern s32 D_800DF708;

/***********************************************************************
 * Scheduler API
 **********************************************************************/
void osCreateScheduler(OSSched *sc, void *stack, OSPri priority,
                       u8 mode, u8 numFields)
{
    sc->curRSPTask      = 0;
    sc->curRDPTask      = 0;
    sc->clientList      = 0;
    sc->frameCount      = 0;
    sc->audioListHead   = 0;
    sc->gfxListHead     = 0;
    sc->audioListTail   = 0;
    sc->gfxListTail     = 0;
    sc->retraceMsg.type = OS_SC_RETRACE_MSG;  /* sent to apps */
    sc->prenmiMsg.type  = OS_SC_PRE_NMI_MSG;

    osCreateMesgQueue(&sc->interruptQ, sc->intBuf, OS_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->cmdQ, sc->cmdMsgBuf, OS_SC_MAX_MESGS);

    /*
     * Set up video manager, listen for Video, RSP, and RDP interrupts
     */
    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeTable[mode]);
    osViBlack(TRUE);
    osSetEventMesg(OS_EVENT_SP, &sc->interruptQ, (OSMesg)RSP_DONE_MSG);
    osSetEventMesg(OS_EVENT_DP, &sc->interruptQ, (OSMesg)RDP_DONE_MSG);
    osSetEventMesg(OS_EVENT_PRENMI, &sc->interruptQ, (OSMesg)PRE_NMI_MSG);

    osViSetEvent(&sc->interruptQ, (OSMesg)VIDEO_MSG, numFields);

    osCreateThread(&sc->thread, 4, __scMain, (void *)sc, stack, priority);
    osStartThread(&sc->thread);
}

void osScAddClient(OSSched *sc, OSScClient *c, OSMesgQueue *msgQ)
{
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);

    c->msgQ = msgQ;
    c->next = sc->clientList;
    sc->clientList = c;

    osSetIntMask(mask);
}

void osScRemoveClient(OSSched *sc, OSScClient *c)
{
    OSScClient *client = sc->clientList;
    OSScClient *prev   = 0;
    OSIntMask  mask;

    mask = osSetIntMask(OS_IM_NONE);

    while (client != 0) {
        if (client == c) {
            if (prev)
                prev->next = c->next;
            else
                sc->clientList = c->next;
            break;
        }
        prev = client;
        client = client->next;
    }

    osSetIntMask(mask);
}

OSMesgQueue *osScGetCmdQ(OSSched *sc)
{
    return &sc->cmdQ;
}

/***********************************************************************
 * Scheduler thread
 **********************************************************************/
void __scMain(void *arg)
{
    OSMesg msg;
    OSSched *sc = (OSSched *)arg;
    OSScClient *client;

    while (1) {
        osRecvMesg(&sc->interruptQ, (OSMesg *)&msg, OS_MESG_BLOCK);

        switch ((int) msg) {
          case (VIDEO_MSG):
              updateScreenTimersOnRetrace();
              __scHandleRetrace(sc);
              break;

          case (RSP_DONE_MSG):
              __scHandleRSP(sc);
              break;

          case (RDP_DONE_MSG):
              __scHandleRDP(sc);
              break;

          case (PRE_NMI_MSG):
              /*
               * notify audio and graphics threads to fade out
               */
              if (D_800DF72C) {
                  D_800DF728 = 1;
                  for (client = sc->clientList; client != 0; client = client->next) {
                      osSendMesg(client->msgQ, (OSMesg) &sc->prenmiMsg,
                                 OS_MESG_NOBLOCK);
                  }
              }
              break;
        }
    }
}

void __scHandleRetrace(OSSched *sc)
{
    OSScTask    *t;
    OSScClient  *client;
    OSScTask    *rspTask;
    s32         state;
    OSScTask    *sp = 0;
    OSScTask    *dp = 0;

    sc->frameCount++;

    /*
     * pull new tasks off the command queue
     */
    while (osRecvMesg(&sc->cmdQ, (OSMesg *)&t, OS_MESG_NOBLOCK) != -1) {
        __scAppendList(sc, t);
    }

    if (sc->doAudio && sc->curRSPTask) {
        __scYield(sc);
    } else {
        state = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
        if (__scSchedule(sc, &sp, &dp, state) != state) {
            __scExec(sc, sp, dp);
        }
    }

    /*
     * notify clients of the retrace
     */
    for (client = sc->clientList; client != 0; client = client->next) {
        osSendMesg(client->msgQ, (OSMesg) &sc->retraceMsg, OS_MESG_NOBLOCK);
    }
}

void __scHandleRSP(OSSched *sc)
{
    OSScTask *t;
    OSScTask *sp = 0;
    OSScTask *dp = 0;
    s32 state;

    t = sc->curRSPTask;
    sc->curRSPTask = 0;

    if ((t->state & OS_SC_YIELD) && osSpTaskYielded(&t->list)) {
        t->state |= OS_SC_YIELDED;
        if ((t->flags & OS_SC_TYPE_MASK) == OS_SC_XBUS) {
            /* push the task back on the list */
            t->next = sc->gfxListHead;
            sc->gfxListHead = t;
            if (sc->gfxListTail == 0) {
                sc->gfxListTail = t;
            }
        }
    } else {
        t->state &= ~OS_SC_NEEDS_RSP;
        __scTaskComplete(sc, t);
    }

    state = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
    if (__scSchedule(sc, &sp, &dp, state) != state) {
        __scExec(sc, sp, dp);
    }
}

void __scHandleRDP(OSSched *sc)
{
    OSScTask *t;
    OSScTask *sp = 0;
    OSScTask *dp = 0;
    s32 state;

    t = sc->curRDPTask;
    sc->curRDPTask = 0;

    t->state &= ~OS_SC_NEEDS_RDP;
    __scTaskComplete(sc, t);

    state = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
    if (__scSchedule(sc, &sp, &dp, state) != state) {
        __scExec(sc, sp, dp);
    }
}

/*
 * check that a (gfx) task's framebuffer is not still being displayed
 */
static OSScTask *__scTaskReady(OSScTask *t)
{
    OSScTask *ret = 0;
    void *fb;
    void *nextFb;

    if (t) {
        if ((fb = osViGetCurrentFramebuffer()) != (nextFb = osViGetNextFramebuffer())) {
            return 0;
        }
        return t;
    }
    return 0;
}

static s32 __scTaskComplete(OSSched *sc, OSScTask *t)
{
    int rv;

    if ((t->state & OS_SC_RCP_MASK) == 0) { /* none of the needs bits set */
        rv = osSendMesg(t->msgQ, t->msg, OS_MESG_BLOCK);
        if (t->list.t.type == M_GFXTASK) {
            if ((t->flags & OS_SC_SWAPBUFFER) && (t->flags & OS_SC_LAST_TASK)) {
                if (D_800DF70C) {
                    osViBlack(0);
                    D_800DF70C = 0;
                }
                osViSwapBuffer(t->framebuffer);
            }
        }
        return 1;
    }

    return 0;
}

static void __scAppendList(OSSched *sc, OSScTask *t)
{
    s32 type = t->list.t.type;

    if (type != M_AUDTASK) {
    }
    if (type == M_AUDTASK) {
        if (sc->audioListTail) {
            sc->audioListTail->next = t;
        } else {
            sc->audioListHead = t;
        }
        sc->audioListTail = t;
        sc->doAudio = 1;
    } else {
        if (sc->gfxListTail) {
            sc->gfxListTail->next = t;
        } else {
            sc->gfxListHead = t;
        }
        sc->gfxListTail = t;
    }

    t->next = 0;
    t->state = t->flags & OS_SC_RCP_MASK;
}

static void __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp)
{
    s32 rv;

    if (sp) {
        if (sp->list.t.type == M_AUDTASK) {
            osWritebackDCacheAll();
        }
        sp->state &= ~(OS_SC_YIELD | OS_SC_YIELDED);
        osSpTaskLoad(&sp->list);
        osSpTaskStartGo(&sp->list);
        sc->curRSPTask = sp;
        if (sp == dp) {
            sc->curRDPTask = dp;
        }
    }

    if (dp && (dp != sp)) {
        rv = osDpSetNextBuffer(dp->list.t.output_buff,
                               *dp->list.t.output_buff_size);
        D_800DF704 = 1;
        D_800DF708 = 0;
        sc->curRDPTask = dp;
    }
}

static void __scYield(OSSched *sc)
{
    if (sc->curRSPTask->list.t.type == M_GFXTASK) {
        sc->curRSPTask->state |= OS_SC_YIELD;
        osSpTaskYield();
    } else {
    }
}

/*
 * Schedules the tasks to be run on the RCP
 */
static s32 __scSchedule(OSSched *sc, OSScTask **sp, OSScTask **dp, s32 availRCP)
{
    s32 avail = availRCP;
    OSScTask *gfx = sc->gfxListHead;
    OSScTask *audio = sc->audioListHead;

    if (sc->doAudio && (avail & OS_SC_SP)) {
        if (gfx && (gfx->flags & 0x10)) {
            *sp = gfx;
            avail &= ~OS_SC_SP;
        } else {
            *sp = audio;
            avail &= ~OS_SC_SP;
            sc->doAudio = 0;
            sc->audioListHead = sc->audioListHead->next;
            if (sc->audioListHead == NULL) {
                sc->audioListTail = NULL;
            }
        }
    } else if (__scTaskReady(gfx)) {
        switch (gfx->flags & OS_SC_TYPE_MASK) {
          case OS_SC_XBUS:
              if (gfx->state & OS_SC_YIELDED) {
                  if (avail & OS_SC_SP) {
                      *sp = gfx;
                      avail &= ~OS_SC_SP;
                      if (gfx->state & OS_SC_DP) {
                          *dp = gfx;
                          avail &= ~OS_SC_DP;
                          goto popgfx;
                      }
popgfx:
                      sc->gfxListHead = sc->gfxListHead->next;
                      if (sc->gfxListHead == NULL) {
                          sc->gfxListTail = NULL;
                      }
                  }
              } else if (avail == (OS_SC_SP | OS_SC_DP)) {
                  *dp = gfx;
                  *sp = *dp;
                  avail &= ~(OS_SC_SP | OS_SC_DP);
                  sc->gfxListHead = sc->gfxListHead->next;
                  if (sc->gfxListHead == NULL) {
                      sc->gfxListTail = NULL;
                  }
              }
              break;

          case OS_SC_DP_XBUS:
          case OS_SC_DP_DRAM:
          case OS_SC_DRAM:
              if (gfx->state & OS_SC_SP) {
                  if (avail & OS_SC_SP) {
                      *sp = gfx;
                      avail &= ~OS_SC_SP;
                  }
              } else if ((gfx->state & OS_SC_DP) && (avail & OS_SC_DP)) {
                  *dp = gfx;
                  avail &= ~OS_SC_DP;
                  sc->gfxListHead = sc->gfxListHead->next;
                  if (sc->gfxListHead == NULL) {
                      sc->gfxListTail = NULL;
                  }
              }
              break;

          case OS_SC_SP_XBUS:
          case OS_SC_SP_DRAM:
          case OS_SC_DRAM_DLIST:
          default:
              break;
        }
    }

    if (avail != availRCP) {
        avail = __scSchedule(sc, sp, dp, avail);
    }

    return avail;
}
