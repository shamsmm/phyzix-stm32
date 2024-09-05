# Can be either `test` for physics tests or `stm` to cross-compile
MODE := stm

# If current run is for cross-compiling to the STM32 chip
ifeq ($(MODE), stm)
include Makefile.stm.mk
all: flash
endif


# If the current run is for a host PC to run physics tests
ifeq ($(MODE), test)
include Makefile.test.mk
all: test
endif