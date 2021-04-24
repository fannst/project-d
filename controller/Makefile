# Device Options
MCPU								:= cortex-m7

# Toolchain & Tools
TOOLCHAIN						?= arm-none-eabi
ST_FLASH						?= st-flash
GPP									:= $(TOOLCHAIN)-g++
GCC									:= $(TOOLCHAIN)-gcc
SIZE								:= $(TOOLCHAIN)-size
OBJCOPY							:= $(TOOLCHAIN)-objcopy
AS									:= $(TOOLCHAIN)-as

# General Files
LINKER_SCRIPT				:= ./linker/linker.ld
FIRMWARE_ELF				:= firmware.elf
FIRMWARE_BIN				:= firmware.bin

# ST_FLASH Arguments
ST_FLASH_ARGS				+= write
ST_FLASH_ARGS				+= $(FIRMWARE_BIN)
ST_FLASH_ARGS				+= 0x8000000

# GCC Arguments
GCC_ARGS						+= -Wall
GCC_ARGS						+= -Werror

GCC_ARGS						+= -mthumb
GCC_ARGS						+= -mcpu=$(MCPU)

GCC_ARGS						+= -O3
GCC_ARGS						+= -ffunction-sections
GCC_ARGS						+= -fdata-sections
GCC_ARGS						+= -Wl,--gc-sections

GCC_ARGS 						+= -nostartfiles
GCC_ARGS						+= -nostdlib

GCC_ARGS						+= -I./include
GCC_ARGS						+= -I./vendor
GCC_ARGS						+= -I../shared/include

# AS Arguments
AS_ARGS							+= -mthumb
AS_ARGS							+= -mcpu=$(MCPU)

# GPP Arguments
GPP_ARGS						+= $(GCC_ARGS)

# OBJCOPY Arguments
OBJCOPY_ARGS				+= -O binary
OBJCOPY_ARGS				+= $(FIRMWARE_ELF)
OBJCOPY_ARGS				+= $(FIRMWARE_BIN)

# Size Arguments
SIZE_ARGS						+= --format=gnu
SIZE_ARGS						+= --radix=10
SIZE_ARGS						+= --common
SIZE_ARGS						+= $(FIRMWARE_ELF)

# Files
GPP_SOURCES					+= $(shell find ./source -name *.cpp)
GPP_SOURCES					+= $(shell find ../shared/source -name *.cpp)
C_SOURCES						+= $(shell find ./source -name *.c)
S_SOURCES						+= $(shell find ./source -name *.s)

OBJECTS							+= $(GPP_SOURCES:.cpp=.arm.o)
OBJECTS							+= $(C_SOURCES:.c=.arm.o)
OBJECTS							+= $(S_SOURCES:.s=.arm.o)

# Compilation
%.arm.o: %.s
	$(AS) $< -o $@
%.arm.o: %.cpp
	$(GPP) $(GPP_ARGS) -c $< -o $@
%.arm.o: %.c
	$(GCC) $(GCC_ARGS) -c $< -o $@

# General Make Rules
all: $(OBJECTS)
	$(GPP) $(OBJECTS) -T $(LINKER_SCRIPT) -o $(FIRMWARE_ELF)
size:
	$(SIZE) $(SIZE_ARGS)
clean:
	rm -rf $(OBJECTS)
bin:
	$(OBJCOPY) $(OBJCOPY_ARGS)
flash:
	$(ST_FLASH) $(ST_FLASH_ARGS)
