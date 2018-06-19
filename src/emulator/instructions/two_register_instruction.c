#include "emulator/instructions/two_register_instruction.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"
#include "emulator/instructions/operands.h"

static TwoRegisterInstruction two_register_instruction;
static bool in_use;

TwoRegisterInstruction *newTwoRegisterInstruction(
    const Opcode opcode, const unsigned instruction_size, const uint8_t *data,
    const RegisterIndex reg_index1, const RegisterIndex reg_index2) {
  assert(in_use == false);

  in_use = true;
  initInstruction((Instruction *)&two_register_instruction, opcode,
                  instruction_size, data, InstructionType_TWO_REGISTER);
  two_register_instruction.reg_index1 = reg_index1;
  two_register_instruction.reg_index2 = reg_index2;
  return &two_register_instruction;
}

void deleteTwoRegisterInstruction(const TwoRegisterInstruction *instruction
                                  __attribute__((unused))) {
  in_use = false;
}

const TwoRegisterInstruction *castTwoRegisterInstruction(
    const Instruction *instruction) {
  assert(instruction != NULL);
  assert(instruction->type == InstructionType_TWO_REGISTER);

  return (const TwoRegisterInstruction *)instruction;
}
