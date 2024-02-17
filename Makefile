BLOCKSDS	?= /opt/blocksds/core

# User config

NAME		:= chip_8_nds
GAME_TITLE	:= Chip 8 Emulator
GFXDIRS		:= gfx
NITROFSDIR	:= nitrofiles

GAME_SUBTITLE		:= 
GAME_AUTHOR		:= github.com/AngelTomkins/
GAME_ICON		:= gfx/icon.bmp

SOURCEDIRS := source include

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile

CFLAGS          += -std=gnu11 $(WARNFLAGS) $(DEFINES) $(ARCH) \
                   -mthumb -mthumb-interwork $(INCLUDEFLAGS) -O3 \
                   -ffunction-sections -fdata-sections \
                   -fomit-frame-pointer -g

CXXFLAGS        += -std=gnu++14 $(WARNFLAGS) $(DEFINES) $(ARCH) \
                   -mthumb -mthumb-interwork $(INCLUDEFLAGS) -O3 \
                   -ffunction-sections -fdata-sections \
                   -fno-exceptions -fno-rtti \
                   -fomit-frame-pointer -g

LDFLAGS         := -mthumb -mthumb-interwork $(LIBDIRSFLAGS) \
                   -Wl,-Map,$(MAP) -Wl,--gc-sections -nostdlib \
                   -T$(BLOCKSDS)/sys/crts/ds_arm9.mem \
                   -T$(BLOCKSDS)/sys/crts/ds_arm9.ld \
                   -Wl,--no-warn-rwx-segments \
                   -Wl,--start-group $(LIBS) -lgcc -Wl,--end-group

