# Can be either `test` for physics tests or `stm` to cross-compile
MODE := test

include Makefile.stm.mk
include Makefile.test.mk

ifeq ($(MODE), stm)
    all: flash
endif

ifeq ($(MODE), test)
    all: test
endif