#include "emulator/instructions/one_register_instruction.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "emulator/cpu/cpu.h"
#include "emulator/cpu/cpu_flag.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/instruction_operands.h"
#include "emulator/instructions/opcode.h"

static OneRegisterInstruction one_register_instruction;
static bool in_use;

OneRegisterInstruction *_newOneRegisterInstruction(
    const Opcode opcode, const unsigned instruction_size, const uint8_t *data,
    const FlagIndexBitset flags_affected, const RegisterIndex reg_index) {
  assert(in_use == false);

  in_use = true;
  _initInstruction((Instruction *)&one_register_instruction, opcode,
                   instruction_size, data, flags_affected,
                   InstructionType_ONE_REGISTER);
  one_register_instruction.reg_index = reg_index;
  return &one_register_instruction;
}

void _deleteOneRegisterInstruction(OneRegisterInstruction *instruction
                                   __attribute__((unused))) {
  in_use = false;
}

const OneRegisterInstruction *castOneRegisterInstruction(
    const Instruction *instruction) {
  assert(instruction != NULL);
  assert(instruction->type == InstructionType_ONE_REGISTER);

  return (const OneRegisterInstruction *)instruction;
}
