# Adapted from the Wave Race 64 decomp Makefile (mkst/sssv lineage)
BASENAME  = tetrisphere
VERSION  := us

NO_COL  := \033[0m
GREEN   := \033[0;32m
PINK    := \033[0;35m
CYAN    := \033[0;36m

BUILD_DIR = build
TOOLS_DIR = tools
HOST_CC ?= gcc

ASM_DIRS   := $(shell find asm -type d -not -path "asm/nonmatchings*" 2>/dev/null)
SRC_DIRS   := $(shell find src -type d 2>/dev/null)
ASSET_DIRS := $(shell find assets -type d 2>/dev/null)

S_FILES   = $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
C_FILES   = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
BIN_FILES = assets/ipl3.bin assets/CD3F0.bin

O_FILES := $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \
           $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o)) \
           $(foreach file,$(BIN_FILES),$(BUILD_DIR)/$(file:.bin=.o))

CROSS   := mips-linux-gnu-
AS       = $(CROSS)as
LD       = $(CROSS)ld
OBJCOPY  = $(CROSS)objcopy
PYTHON   = python3
SPLAT    = .venv/bin/splat

# Pinned upstream IDO 5.3; setup downloads only when the host cache is missing or invalid.
IDO_CC := $(shell $(PYTHON) tools/setup_ido.py --cc-path)
CC = $(IDO_CC)
# 7.1 matched everywhere except -g boolean-op machinery (&&,!,%) which parks
# intermediates in s0 via or-moves under 5.3 only => whole ROM is IDO 5.3.

# The first rule in this file would otherwise claim the default goal (the
# libc/ll.o prerequisite rule below did), making bare `make` build one object
# and silently skip `verify` -- i.e. the ROM match gate never ran.
.DEFAULT_GOAL := default

OPT_FLAGS = -O1
GFLAG = -g

# game2 (ROM 0x5D240+) is a separate original TU: IDO 5.3 -O2 -g0 -mips1
# code_4D170 (main-segment game code) is -O2 -g0 -mips1 like game2, NOT the -O1 -g
# default -- proven by filled delay slots + K&R param homing in the ROM.
$(BUILD_DIR)/src/code_8170.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src/code_8170.o: GFLAG := -g0
$(BUILD_DIR)/src/code_4D170.o: OPT_FLAGS := -O2 -Wo,-loopunroll,1
$(BUILD_DIR)/src/code_4D170.o: GFLAG := -g0
# code_54150 (func_80078DA0, ROM 0x54150) is its own TU: plain -O2 with loop unrolling ON.
# code_4D170 carries -loopunroll,1 only for func_800750C8; this function needs the default.
$(BUILD_DIR)/src/code_54150.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src/code_54150.o: GFLAG := -g0
$(BUILD_DIR)/src/game2.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src/game2.o: GFLAG := -g0
# audiomgr.c (ROM 0x59BB0, SDK-demo audiomgr.c layer) is IDO 5.3 -O2 -g0 like game2
$(BUILD_DIR)/src/audiomgr.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src/audiomgr.o: GFLAG := -g0
$(BUILD_DIR)/src/audio_engine.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src/audio_engine.o: GFLAG := -g0
# game2 .rodata must land 4-aligned at 0xCC214 (retail link packed it at vaddr ...E64); GNU ld honors the section alignment attr, so drop it from 16 to 4
$(BUILD_DIR)/src/game2.o: RODATA_ALIGN4 := 1

### Per-file flag overrides
MIPSISET  = -mips1 -32

INCLUDE_CFLAGS = -I . -I include -I include/libc

### libultra 2.0H farm (tools/ultralib source): verified pilot flags -O1 -mips2 -g0
$(BUILD_DIR)/src/libultra/%.o: GFLAG := -g0
$(BUILD_DIR)/src/libultra/%.o: MIPSISET := -mips2 -32
$(BUILD_DIR)/src/libultra/%.o: INCLUDE_CFLAGS := -I $(TOOLS_DIR)/ultralib/include -I $(TOOLS_DIR)/ultralib/include/PR
$(BUILD_DIR)/src/libultra/%.o: DEFINES := -D_LANGUAGE_C -D_FINALROM -DNDEBUG -DBUILD_VERSION=VERSION_H
# gu math files were compiled -O2 (proven by byte-match; -O1 mismatches all of them)
$(BUILD_DIR)/src/libultra/gu/%.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src/libultra/gu/%.o: INCLUDE_CFLAGS := -I $(TOOLS_DIR)/ultralib/include -I $(TOOLS_DIR)/ultralib/include/PR -I $(TOOLS_DIR)/ultralib/src/gu
# ...except these three, which only match at -O3
$(BUILD_DIR)/src/libultra/gu/translate.o: OPT_FLAGS := -O3
$(BUILD_DIR)/src/libultra/gu/mtxcatf.o: OPT_FLAGS := -O3
$(BUILD_DIR)/src/libultra/gu/lookat.o: OPT_FLAGS := -O3
$(BUILD_DIR)/src/libultra/gu/rotaterpy.o: OPT_FLAGS := -O3
$(BUILD_DIR)/src/libultra/gu/scale.o: OPT_FLAGS := -O3
$(BUILD_DIR)/src/libultra/gu/ortho.o: OPT_FLAGS := -O3
$(BUILD_DIR)/src/libultra/gu/rotate.o: OPT_FLAGS := -O3
# ...and these three only match under IDO 5.3 (lib mixes compiler versions)
$(BUILD_DIR)/src/libultra/gu/sinf.o: CC = $(IDO_CC)
$(BUILD_DIR)/src/libultra/gu/sins.o: CC = $(IDO_CC)
$(BUILD_DIR)/src/libultra/gu/coss.o: CC = $(IDO_CC)
# libc files need stdlib.h/stdarg.h/string.h, absent from ultralib's include tree
$(BUILD_DIR)/src/libultra/libc/%.o: INCLUDE_CFLAGS := -I $(TOOLS_DIR)/ultralib/include -I $(TOOLS_DIR)/ultralib/include/PR -I include/libc -I $(TOOLS_DIR)/ultralib/src/libc
# audio (classic libaudio) files were compiled -O2; a few only match under IDO 5.3
$(BUILD_DIR)/src/libultra/audio/%.o: OPT_FLAGS := -O2
$(BUILD_DIR)/src/libultra/audio/%.o: INCLUDE_CFLAGS := -I $(TOOLS_DIR)/ultralib/include -I $(TOOLS_DIR)/ultralib/include/PR -I $(TOOLS_DIR)/ultralib/src/audio -I include/libc
$(BUILD_DIR)/src/libultra/audio/synstartvoiceparam.o: CC = $(IDO_CC)
$(BUILD_DIR)/src/libultra/audio/heapalloc.o: CC = $(IDO_CC)
# n_audio = the game's early libaudio copy: IDO 5.3 -O3 -mips2 -g0. IDO -O3 emits an 8-byte
# out-of-line dead copy (jr ra; nop) of a fully-inlined static as LEADING .text; that stub is
# REAL ROM content. synthesizer.o's leading stub lives at 0xAB950 (its .text start), with
# _timeToSamples at 0xAB958 -- so sl.o is a clean 0xC0 (4 fns, no stub) ending at 0xAB950 and
# NO strip is needed (the old synth_strip_deadstub.py masked a mis-drawn segment boundary).
$(BUILD_DIR)/src/n_audio/%.o: CC = $(IDO_CC)
$(BUILD_DIR)/src/n_audio/%.o: OPT_FLAGS := -O3
$(BUILD_DIR)/src/n_audio/%.o: GFLAG := -g0
$(BUILD_DIR)/src/n_audio/%.o: MIPSISET := -mips2 -32
$(BUILD_DIR)/src/n_audio/%.o: INCLUDE_CFLAGS := -I $(TOOLS_DIR)/ultralib/include -I $(TOOLS_DIR)/ultralib/include/PR -I $(TOOLS_DIR)/ultralib/src/audio -I include/libc
$(BUILD_DIR)/src/n_audio/%.o: DEFINES := -D_LANGUAGE_C -D_FINALROM -DNDEBUG -DBUILD_VERSION=VERSION_H
# n_audio/env = libaudio env.c (the ROM's "drvrnew" segment @0x2160). Built MIPS I with
# asserts ACTIVE (load-delay nops + assert() bounds-checks are visible in the ROM), unlike
# the -mips2 -g0 -DNDEBUG synthesizer/sl. Flags pinned via matchdiff.
$(BUILD_DIR)/src/n_audio/env.o: OPT_FLAGS := -O1
$(BUILD_DIR)/src/n_audio/env.o: GFLAG := -g
$(BUILD_DIR)/src/n_audio/env.o: MIPSISET := -mips1 -32
$(BUILD_DIR)/src/n_audio/env.o: DEFINES := -D_LANGUAGE_C -D_FINALROM -DBUILD_VERSION=VERSION_H
AUDIO_53_O3 := drvrnew synallocfx synallocvoice mainbus resample auxbus save load reverb
$(foreach f,$(AUDIO_53_O3),$(eval $(BUILD_DIR)/src/libultra/audio/$(f).o: CC = $(IDO_CC)))
$(foreach f,$(AUDIO_53_O3),$(eval $(BUILD_DIR)/src/libultra/audio/$(f).o: OPT_FLAGS := -O3))

# these io files only match under IDO 5.3 (still -O1)
$(BUILD_DIR)/src/libultra/io/aisetfreq.o: CC = $(IDO_CC)
$(BUILD_DIR)/src/libultra/os/initialize.o: CC = $(IDO_CC)
$(BUILD_DIR)/src/libultra/io/devmgr.o: CC = $(IDO_CC)

# the libc core (printf machinery, ldiv) only matches under IDO 5.3 -O3
LIBC_53_O3 := xprintf xlitob xldtob ldiv string sprintf
$(foreach f,$(LIBC_53_O3),$(eval $(BUILD_DIR)/src/libultra/libc/$(f).o: CC = $(IDO_CC)))
$(foreach f,$(LIBC_53_O3),$(eval $(BUILD_DIR)/src/libultra/libc/$(f).o: OPT_FLAGS := -O3))
# sptask.c: retail lib built with the GBI microcode define (OS_YIELD_DATA_SIZE 0xC00)
$(BUILD_DIR)/src/libultra/io/sptask.o: DEFINES := -D_LANGUAGE_C -D_FINALROM -DNDEBUG -DBUILD_VERSION=VERSION_H -DF3DEX_GBI
# ll.c was compiled -mips3 in the retail lib (64-bit ld/dmultu in ROM).
# GNU ld refuses ARCH_3 objects in a 32-bit link, so patch e_flags to ARCH_2
# after compiling; the encoded instructions are untouched.
$(BUILD_DIR)/src/libultra/libc/ll.o: MIPSISET := -mips3 -32
$(BUILD_DIR)/src/libultra/libc/ll.o: src/libultra/libc/ll.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
	@$(PYTHON) -c "import struct;p='$@';d=bytearray(open(p,'rb').read());d[0x24:0x28]=struct.pack('>I',(struct.unpack('>I',d[0x24:0x28])[0]&0x0FFFFFFF)|0x10000000);open(p,'wb').write(d)"
	@printf "[ IDO -mips3, e_flags patched to mips2 ]  $<\n"

ASFLAGS      = -EB -mtune=vr4300 -march=vr4300 -mabi=32 -I include
OBJCOPYFLAGS = -O binary

DEFINES := -D_LANGUAGE_C -D_FINALROM -DTARGET_N64

CFLAGS = -Wab,-r4300_mul -non_shared -G 0 -Xcpluscomm -fullwarn -nostdinc $(GFLAG)
CFLAGS += $(DEFINES)
CFLAGS += -woff 624,649,838,712,516,513,596,564,594,709,807
CFLAGS += $(INCLUDE_CFLAGS)
CFLAGS += $(EXTRA_CFLAGS)

TARGET    = $(BUILD_DIR)/$(BASENAME).$(VERSION)
LD_SCRIPT = $(BASENAME).ld

LD_FLAGS  = -T $(LD_SCRIPT) -T hardware_regs.ld -T undefined_syms.txt -T undefined_funcs_auto.txt -T undefined_syms_auto.txt
LD_FLAGS += -Map $(TARGET).map --no-check-sections

### Targets

default: verify

progress:
	@python3 tools/scripts/progress.py

verify: $(TARGET).z64
	@$(PYTHON) tools/rom.py verify

setup-ido:
	@$(PYTHON) tools/setup_ido.py

tools: setup-ido $(BUILD_DIR)/tools/n64crc

$(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o)): | tools

assets: tools/rom.py
	@$(PYTHON) tools/rom.py extract

$(BIN_FILES): | assets

verify-assets:
	@$(PYTHON) tools/asset_recreate/verify_736C50.py

dirs:
	$(foreach dir,$(ASM_DIRS) $(SRC_DIRS) $(ASSET_DIRS),$(shell mkdir -p $(BUILD_DIR)/$(dir)))

extract: assets

# Full splat regeneration is a research operation, not part of normal setup.
resplit:
	$(SPLAT) split $(BASENAME).yaml

clean:
	rm -rf build

distclean: clean
	rm -f $(BIN_FILES)

### Recipes

$(TARGET).elf: dirs $(LD_SCRIPT) $(O_FILES)
	@rm -f $(TARGET).z64 $(TARGET).bin $@
	@$(LD) $(LD_FLAGS) -o $@
	@printf "[$(PINK) GNU Linker $(NO_COL)]  $@\n"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
	$(if $(RODATA_ALIGN4),@$(OBJCOPY) --set-section-alignment .rodata=4 $@)
	@printf "[$(GREEN) IDO 5.3 $(NO_COL)]  $<\n"

# the two data blobs flanking the game2 .rodata carve (0xCC214, 4-aligned) must keep
# exact (unpadded) sizes and 4-align so the carve tiles; see session-9 notes
CARVE_NEIGHBORS := $(BUILD_DIR)/asm/data/C6370.data.o $(BUILD_DIR)/asm/data/C7340.data.o $(BUILD_DIR)/asm/data/C9230.data.o $(BUILD_DIR)/asm/data/CC244.data.o $(BUILD_DIR)/asm/data/CC3A4.data.o $(BUILD_DIR)/asm/data/CC3A8.data.o $(BUILD_DIR)/asm/data/C9AFC.data.o $(BUILD_DIR)/asm/data/B8880.data.o $(BUILD_DIR)/asm/data/BAAB0.data.o $(BUILD_DIR)/asm/data/C9450.data.o
$(CARVE_NEIGHBORS): ASFLAGS += -no-pad-sections

# n_audio/sl (asm tail of sl.c before the synthesizer C object) must keep its exact
# 0xC8 .text size (no 16-byte pad) so synthesizer.o tiles at 0xAB958
SL_NOPAD := $(BUILD_DIR)/asm/n_audio/sl.o
$(SL_NOPAD): ASFLAGS += -no-pad-sections

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	@$(AS) $(ASFLAGS) -o $@ $<
	$(if $(filter $@,$(CARVE_NEIGHBORS)),@$(OBJCOPY) --set-section-alignment .data=4 $@)
	$(if $(filter $@,$(SL_NOPAD)),@$(OBJCOPY) --set-section-alignment .text=4 $@)
	@printf "[$(GREEN) MIPS GNU Assembler $(NO_COL)]  $<\n"

$(BUILD_DIR)/%.o: %.bin
	@mkdir -p $(dir $@)
	@$(LD) -r -b binary -o $@ $<
	@printf "[$(PINK) Binary blob $(NO_COL)]  $<\n"

$(TARGET).bin: $(TARGET).elf
	@$(OBJCOPY) $(OBJCOPYFLAGS) $< $@
	@printf "[$(CYAN) GNU Objcopy $(NO_COL)]  $<\n"

# n64crc was committed as an aarch64 BINARY with NO SOURCE, so this repo only built on
# aarch64 -- on x86 it died with "cannot execute binary file: Exec format error". The
# source (Parasyte's snesrc CRC tool, using uCON64's N64 algorithm) is now tracked and
# built per-arch. Proven equivalent: corrupt the real ROM's CRC words at 0x10 and both
# the old committed binary and a fresh build restore tetrisphere.z64 byte-for-byte.
$(BUILD_DIR)/tools/n64crc: $(TOOLS_DIR)/n64crc.c
	@mkdir -p $(dir $@)
	@$(HOST_CC) -O2 -o $@ $<
	@printf "[$(CYAN) HOST CC $(NO_COL)]  $@\n"

$(TARGET).z64: $(TARGET).bin $(BUILD_DIR)/tools/n64crc
	@cp $< $@
	@$(BUILD_DIR)/tools/n64crc $@
	@printf "[$(CYAN) ROM built $(NO_COL)]  $@\n"

### Settings
.SECONDARY:
.PHONY: all clean default dirs distclean extract resplit verify verify-assets tools setup-ido assets
SHELL = /bin/bash -e -o pipefail
