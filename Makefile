include make/*.mk

EMULATOR_SRC := $(shell find src/ -type f -name "*.c")

$(eval $(call c_binary,emulator,$(EMULATOR_SRC)))
