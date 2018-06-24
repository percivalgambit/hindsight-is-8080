#ifndef EMULATOR_INSTRUCTIONS_NULLARY_INSTRUCTION_H_
#define EMULATOR_INSTRUCTIONS_NULLARY_INSTRUCTION_H_

#include <stdint.h>

#include "emulator/cpu/cpu.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"
#include "emulator/instructions/opcode_defs.h"

typedef struct {
  INSTRUCTION_BASE;
} NullaryInstruction;

NullaryInstruction *_newNullaryInstruction(const Opcode opcode,
                                           const unsigned instruction_size,
                                           const uint8_t *data);
void _deleteNullaryInstruction(NullaryInstruction *instruction);

const NullaryInstruction *castNullaryInstruction(const Instruction *instruction)
    __attribute__((const));

#define TABLE_ITEM(opcode, ...) \
  void Execute_##opcode(Cpu *cpu, const NullaryInstruction *instruction);
NULLARY_OPCODE_DEFS
#undef TABLE_ITEM

#endif  // EMULATOR_INSTRUCTIONS_NULLARY_INSTRUCTION_H_
