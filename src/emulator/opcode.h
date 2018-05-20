#ifndef EMULATOR_OPCODE_H_
#define EMULATOR_OPCODE_H_

#include "emulator/opcode_defs.h"

typedef enum {
#define TABLE_ITEM(opcode, _) Opcode_##opcode,
  OPCODE_DEFS
#undef TABLE_ITEM
      Opcode_INVALID,
} Opcode;

#endif  // EMULATOR_OPCODE_H_
