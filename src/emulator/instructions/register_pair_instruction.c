#include "emulator/instructions/register_pair_instruction.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"
#include "emulator/instructions/operands.h"

static RegisterPairInstruction register_pair_instruction;
static bool in_use;

RegisterPairInstruction *newRegisterPairInstruction(
    const Opcode opcode, const unsigned instruction_size, const uint8_t *data,
    const RegisterPairIndex reg_pair_index) {
  assert(in_use == false);

  in_use = true;
  initInstruction((Instruction *)&register_pair_instruction, opcode,
                  instruction_size, data, InstructionType_REGISTER_PAIR);
  register_pair_instruction.reg_pair_index = reg_pair_index;
  return &register_pair_instruction;
}

void deleteRegisterPairInstruction(const RegisterPairInstruction *instruction
                                   __attribute__((unused))) {
  in_use = false;
}

const RegisterPairInstruction *castRegisterPairInstruction(
    const Instruction *instruction) {
  assert(instruction != NULL);
  assert(instruction->type == InstructionType_REGISTER_PAIR);

  return (const RegisterPairInstruction *)instruction;
}
