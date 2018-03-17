#include <stdio.h>
#include <stdlib.h>

#include "emulator/cmd_line.h"
#include "emulator/emulator.h"
#include "util/logging.h"

static void cleanup();

static const CmdLine *cmd_line = NULL;
static Emulator *emulator = NULL;

int main(const int argc, const char *argv[]) {
  if (atexit(cleanup)) {
    WARNING("Cannot set exit function. Expect a memory leak.");
  }

  cmd_line = parseCmdLine(argc, argv);
  FILE *program = fopen(cmd_line->program_file, "rb");
  if (program == NULL) {
    ERROR("Could not open %s", cmd_line->program_file);
  }
  emulator = newEmulator(program);
  emulatorRun(emulator);

  return EXIT_SUCCESS;
}

static void cleanup() {
  if (cmd_line != NULL) {
    deleteCmdLine(cmd_line);
  }
  if (emulator != NULL) {
    deleteEmulator(emulator);
  }
}
