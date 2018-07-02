#include "emulator/instructions/nullary_instruction.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>

#include "emulator/cpu/cpu.h"
#include "emulator/cpu/cpu_flag.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"

static NullaryInstruction nullary_instruction;
static bool in_use;

NullaryInstruction *_newNullaryInstruction(
    const Opcode opcode, const unsigned instruction_size, const uint8_t *data,
    const FlagIndexBitset flags_affected) {
  assert(in_use == false);

  in_use = true;
  _initInstruction((Instruction *)&nullary_instruction, opcode,
                   instruction_size, data, flags_affected,
                   InstructionType_NULLARY);
  return &nullary_instruction;
}

void _deleteNullaryInstruction(NullaryInstruction *instruction
                               __attribute__((unused))) {
  in_use = false;
}

const NullaryInstruction *castNullaryInstruction(
    const Instruction *instruction) {
  assert(instruction != NULL);
  assert(instruction->type == InstructionType_NULLARY);

  return (const NullaryInstruction *)instruction;
}

void Execute_STC(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  cpuFlagSet(cpu, true, FlagIndex_CARRY);
}

void Execute_CMC(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  cpuFlagComplement(cpu, FlagIndex_CARRY);
}
