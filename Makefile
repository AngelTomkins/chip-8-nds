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
