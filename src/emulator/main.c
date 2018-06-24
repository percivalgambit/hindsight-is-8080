#include <stdio.h>
#include <stdlib.h>

#include "emulator/cmd_line.h"
#include "emulator/cpu/cpu.h"
#include "util/logging.h"

static void cleanup(void);

static CmdLine *cmd_line = NULL;
static Cpu *cpu = NULL;

int main(const int argc, const char *argv[]) {
  if (atexit(cleanup)) {
    WARNING("Cannot set exit function. Expect a memory leak.");
  }

  cmd_line = parseCmdLine(argc, argv);
  FILE *program = fopen(cmd_line->program_file, "rb");
  if (program == NULL) {
    ERROR("Could not open %s", cmd_line->program_file);
  }
  cpu = newCpu(program);
  cpuRun(cpu);

  return EXIT_SUCCESS;
}

static void cleanup(void) {
  if (cmd_line != NULL) {
    deleteCmdLine(cmd_line);
  }
  if (cpu != NULL) {
    deleteCpu(cpu);
  }
}
