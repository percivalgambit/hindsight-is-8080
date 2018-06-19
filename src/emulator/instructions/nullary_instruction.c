#include "emulator/instructions/nullary_instruction.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>

#include "emulator/emulator.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"

static NullaryInstruction nullary_instruction;
static bool in_use;

NullaryInstruction *newNullaryInstruction(const Opcode opcode,
                                          const unsigned instruction_size,
                                          const uint8_t *data) {
  assert(in_use == false);

  in_use = true;
  initInstruction((Instruction *)&nullary_instruction, opcode, instruction_size,
                  data, InstructionType_NULLARY);
  return &nullary_instruction;
}

void deleteNullaryInstruction(const NullaryInstruction *instruction
                              __attribute__((unused))) {
  in_use = false;
}

const NullaryInstruction *castNullaryInstruction(
    const Instruction *instruction) {
  assert(instruction != NULL);
  assert(instruction->type == InstructionType_NULLARY);

  return (const NullaryInstruction *)instruction;
}
