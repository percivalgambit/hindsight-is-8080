#ifndef EMULATOR_INSTRUCTIONS_OPCODE_H_
#define EMULATOR_INSTRUCTIONS_OPCODE_H_

#include "emulator/instructions/opcode_defs.h"

typedef enum {
#define TABLE_ITEM(opcode, ...) Opcode_##opcode,
  OPCODE_DEFS
#undef TABLE_ITEM
} Opcode;

#endif  // EMULATOR_INSTRUCTIONS_OPCODE_H_
