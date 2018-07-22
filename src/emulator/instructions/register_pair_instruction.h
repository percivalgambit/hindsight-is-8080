#ifndef EMULATOR_INSTRUCTIONS_REGISTER_PAIR_INSTRUCTION_H_
#define EMULATOR_INSTRUCTIONS_REGISTER_PAIR_INSTRUCTION_H_

#include <stdint.h>

#include "emulator/cpu/cpu.h"
#include "emulator/cpu/cpu_flag.h"
#include "emulator/cpu/register_index.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"
#include "emulator/instructions/opcode_defs.h"

typedef struct {
  INSTRUCTION_BASE;
  RegisterPairIndex reg_pair_index;
} RegisterPairInstruction;

RegisterPairInstruction *_newRegisterPairInstruction(
    const Opcode opcode, const unsigned instruction_size, const uint8_t *data,
    const FlagIndexBitset flags_affected,
    const RegisterPairIndex reg_pair_index);
void _deleteRegisterPairInstruction(RegisterPairInstruction *instruction);

const RegisterPairInstruction *castRegisterPairInstruction(
    const Instruction *instruction) __attribute__((const));

#define TABLE_ITEM(opcode, ...) \
  void Execute_##opcode(Cpu *cpu, const RegisterPairInstruction *instruction);
REGISTER_PAIR_OPCODE_DEFS
#undef TABLE_ITEM

#endif  // EMULATOR_INSTRUCTIONS_REGISTER_PAIR_INSTRUCTION_H_
