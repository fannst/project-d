# Toolchains & Tools
GPP									:= g++
GCC									:= gcc

# General Files
MAIN_ELF						:= main.elf

# GCC Arguments
GCC_ARGS						+= -Wall
GCC_ARGS						+= -Werror

GCC_ARGS						+= -I./include
GCC_ARGS						+= -I../shared/include

GCC_ARGS						+= -lpthread
GCC_ARGS						+= -pthread

# GPP Arguments
GPP_ARGS						+= $(GCC_ARGS)

# Files
GPP_SOURCES					+= $(shell find ./source -name *.cpp)
GPP_SOURCES					+= $(shell find ../shared/source -name *.cpp)
C_SOURCES						+= $(shell find ./source -name *.c)

OBJECTS							+= $(GPP_SOURCES:.cpp=.x86.o)
OBJECTS							+= $(C_SOURCES:.c=.x86.o)
OBJECTS							+= $(S_SOURCES:.s=.x86.o)

# Compilation
%.x86.o: %.cpp
	$(GPP) $(GPP_ARGS) -c $< -o $@
%.x86.o: %.c
	$(GCC) $(GCC_ARGS) -c $< -o $@

# General Make Rules
all: $(OBJECTS)
	$(GPP) $(GPP_ARGS) $(OBJECTS) -o $(MAIN_ELF)
clean:
	rm -rf $(OBJECTS)
