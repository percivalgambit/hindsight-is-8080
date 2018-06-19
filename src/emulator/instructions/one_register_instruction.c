#include "emulator/instructions/one_register_instruction.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"
#include "emulator/instructions/operands.h"

static OneRegisterInstruction one_register_instruction;
static bool in_use;

OneRegisterInstruction *newOneRegisterInstruction(
    const Opcode opcode, const unsigned instruction_size, const uint8_t *data,
    const RegisterIndex reg_index) {
  assert(in_use == false);

  in_use = true;
  initInstruction((Instruction *)&one_register_instruction, opcode,
                  instruction_size, data, InstructionType_ONE_REGISTER);
  one_register_instruction.reg_index = reg_index;
  return &one_register_instruction;
}

void deleteOneRegisterInstruction(const OneRegisterInstruction *instruction
                                  __attribute__((unused))) {
  in_use = false;
}

const OneRegisterInstruction *castOneRegisterInstruction(
    const Instruction *instruction) {
  assert(instruction != NULL);
  assert(instruction->type == InstructionType_ONE_REGISTER);

  return (const OneRegisterInstruction *)instruction;
}
