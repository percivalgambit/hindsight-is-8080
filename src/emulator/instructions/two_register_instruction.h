#ifndef EMULATOR_INSTRUCTIONS_TWO_REGISTER_INSTRUCTION_H_
#define EMULATOR_INSTRUCTIONS_TWO_REGISTER_INSTRUCTION_H_

#include <stdint.h>

#include "emulator/emulator.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"
#include "emulator/instructions/opcode_defs.h"
#include "emulator/instructions/operands.h"

typedef struct {
  INSTRUCTION_BASE;
  RegisterIndex reg_index1;
  RegisterIndex reg_index2;
} TwoRegisterInstruction;

TwoRegisterInstruction *newTwoRegisterInstruction(
    const Opcode opcode, const unsigned instruction_size, const uint8_t *data,
    const RegisterIndex reg_index1, const RegisterIndex reg_index2);
void deleteTwoRegisterInstruction(const TwoRegisterInstruction *instruction);

const TwoRegisterInstruction *castTwoRegisterInstruction(
    const Instruction *instruction) __attribute__((const));

#define TABLE_ITEM(opcode, ...)             \
  void Execute_##opcode(Emulator *emulator, \
                        const TwoRegisterInstruction *instruction);
TWO_REGISTER_OPCODE_DEFS
#undef TABLE_ITEM

#endif  // EMULATOR_INSTRUCTIONS_TWO_REGISTER_INSTRUCTION_H_
