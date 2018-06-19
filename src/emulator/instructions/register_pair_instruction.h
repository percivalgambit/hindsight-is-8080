#ifndef EMULATOR_INSTRUCTIONS_REGISTER_PAIR_INSTRUCTION_H_
#define EMULATOR_INSTRUCTIONS_REGISTER_PAIR_INSTRUCTION_H_

#include <stdint.h>

#include "emulator/emulator.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"
#include "emulator/instructions/opcode_defs.h"
#include "emulator/instructions/operands.h"

typedef struct {
  INSTRUCTION_BASE;
  RegisterPairIndex reg_pair_index;
} RegisterPairInstruction;

RegisterPairInstruction *newRegisterPairInstruction(
    const Opcode opcode, const unsigned instruction_size, const uint8_t *data,
    const RegisterPairIndex reg_pair_index);
void deleteRegisterPairInstruction(const RegisterPairInstruction *instruction);

const RegisterPairInstruction *castRegisterPairInstruction(
    const Instruction *instruction) __attribute__((const));

#define TABLE_ITEM(opcode, ...)             \
  void Execute_##opcode(Emulator *emulator, \
                        const RegisterPairInstruction *instruction);
REGISTER_PAIR_OPCODE_DEFS
#undef TABLE_ITEM

#endif  // EMULATOR_INSTRUCTIONS_REGISTER_PAIR_INSTRUCTION_H_
