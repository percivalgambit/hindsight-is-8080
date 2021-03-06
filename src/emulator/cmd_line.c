#include "emulator/cmd_line.h"

#include <assert.h>
#include <stdlib.h>

#include "util/logging.h"

CmdLine *parseCmdLine(const int argc, const char *argv[]) {
  assert(argc > 0);
  assert(argv != NULL);

  if (argc != 2) {
    ERROR("Expected 2 arguments, got %d", argc);
  }

  CmdLine *cmd_line = calloc(1, sizeof(CmdLine));
  *cmd_line = (CmdLine){.program_file = argv[1]};
  return cmd_line;
}

void deleteCmdLine(CmdLine *cmd_line) {
  assert(cmd_line != NULL);

  free(cmd_line);
}
