#ifndef EMULATOR_INSTRUCTIONS_NULLARY_INSTRUCTION_H_
#define EMULATOR_INSTRUCTIONS_NULLARY_INSTRUCTION_H_

#include <stdint.h>

#include "emulator/emulator.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"
#include "emulator/instructions/opcode_defs.h"

typedef struct {
  INSTRUCTION_BASE;
} NullaryInstruction;

NullaryInstruction *newNullaryInstruction(const Opcode opcode,
                                          const unsigned instruction_size,
                                          const uint8_t *data);
void deleteNullaryInstruction(const NullaryInstruction *instruction);

const NullaryInstruction *castNullaryInstruction(const Instruction *instruction)
    __attribute__((const));

#define TABLE_ITEM(opcode, ...)             \
  void Execute_##opcode(Emulator *emulator, \
                        const NullaryInstruction *instruction);
NULLARY_OPCODE_DEFS
#undef TABLE_ITEM

#endif  // EMULATOR_INSTRUCTIONS_NULLARY_INSTRUCTION_H_
