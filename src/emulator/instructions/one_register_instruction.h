#ifndef EMULATOR_INSTRUCTIONS_ONE_REGISTER_INSTRUCTION_H_
#define EMULATOR_INSTRUCTIONS_ONE_REGISTER_INSTRUCTION_H_

#include <stdint.h>

#include "emulator/emulator.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"
#include "emulator/instructions/opcode_defs.h"
#include "emulator/instructions/operands.h"

typedef struct {
  INSTRUCTION_BASE;
  RegisterIndex reg_index;
} OneRegisterInstruction;

OneRegisterInstruction *newOneRegisterInstruction(
    const Opcode opcode, const unsigned instruction_size, const uint8_t *data,
    const RegisterIndex reg_index);
void deleteOneRegisterInstruction(const OneRegisterInstruction *instruction);

const OneRegisterInstruction *castOneRegisterInstruction(
    const Instruction *instruction) __attribute__((const));

#define TABLE_ITEM(opcode, ...)             \
  void Execute_##opcode(Emulator *emulator, \
                        const OneRegisterInstruction *instruction);
ONE_REGISTER_OPCODE_DEFS
#undef TABLE_ITEM

#endif  // EMULATOR_INSTRUCTIONS_ONE_REGISTER_INSTRUCTION_H_
