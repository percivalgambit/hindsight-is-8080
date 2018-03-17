#ifndef EMULATOR_CMD_LINE_H_
#define EMULATOR_CMD_LINE_H_

typedef struct {
  const char *program_file;
} CmdLine;

CmdLine *parseCmdLine(const int argc, const char *argv[]);
void deleteCmdLine(const CmdLine *cmd_line);

#endif  // EMULATOR_CMD_LINE_H_
