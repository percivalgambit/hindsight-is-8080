#ifndef EMULATOR_OPCODE_H_
#define EMULATOR_OPCODE_H_

typedef enum {
#define TABLE_ITEM(opcode, _) Opcode_##opcode,
#include "emulator/opcode_defs.h"
#undef TABLE_ITEM
  Opcode_INVALID,
} Opcode;

#endif  // EMULATOR_OPCODE_H_
