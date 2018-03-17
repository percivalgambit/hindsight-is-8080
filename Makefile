include make/*.mk

EMULATOR_SRC := src/emulator/main.c src/emulator/emulator.c src/emulator/cmd_line.c src/emulator/instruction.c

$(eval $(call c_binary,emulator,$(EMULATOR_SRC)))
$(eval $(call c_debug_binary,emulator-debug,$(EMULATOR_SRC)))
