# Toolchains
TOOLCHAIN=arm-none-eabi
CC=$(TOOLCHAIN)-gcc
PP=$(TOOLCHAIN)-g++

INCDIR = src src/inc modules/
SRCDIR = src $(wildcard modules/*/src) $(wildcard modules/*)

INCLUDES = $(addprefix -I, $(INCDIR))

SRC = $(wildcard modules/*/*.c)
SRC += $(wildcard modules/*/*.s)
SRC += $(wildcard modules/*/src/*.c)
SRC += $(wildcard src/*.c)
SRC += $(wildcard src/*.s)
SRC += $(wildcard src/*.cpp)

# User defined added source files
SRC += $(wildcard src/app/*.cpp)
SRC += $(wildcard src/app/*/*.cpp)

OBJ = $(SRC:.c=.o)
OBJ := $(OBJ:.cpp=.o)
OBJ := $(OBJ:.s=.o)

BINDIR = build

TARGET = $(BINDIR)/phyzix.elf

CFLAGS=-ggdb -mthumb -mcpu=cortex-m3 -O0 -ffreestanding $(INCLUDES)
CPPFLAGS=-lstdc++
ASMFLAGS=-ggdb -mthumb -mcpu=cortex-m3

flash: $(TARGET)
	openocd -f stlink.cfg -c "program $(TARGET) verify reset exit"

$(TARGET): $(OBJ)
	$(PP) $(CFLAGS) -nostartfiles -Tstm32f103.ld -o $(TARGET) $(addprefix $(BINDIR)/, $(OBJ))


%.o: %.c
	@mkdir -p $(dir $(BINDIR)/$@)
	$(CC) -c $(CFLAGS) $< -o $(BINDIR)/$@

%.o: %.cpp
	@mkdir -p $(dir $(BINDIR)/$@)
	$(PP) -c $(CFLAGS) $(CPPFLAGS) $< -o $(BINDIR)/$@

%.o: %.s
	@mkdir -p $(dir $(BINDIR)/$@)
	$(CC) -c $(ASMFLAGS) $< -o $(BINDIR)/$@

clean:
	rm -rf $(BINDIR)

.PHONY: clean flash