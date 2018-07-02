#ifndef EMULATOR_INSTRUCTIONS_TWO_REGISTER_INSTRUCTION_H_
#define EMULATOR_INSTRUCTIONS_TWO_REGISTER_INSTRUCTION_H_

#include <stdint.h>

#include "emulator/cpu/cpu.h"
#include "emulator/cpu/cpu_flag.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"
#include "emulator/instructions/opcode_defs.h"
#include "emulator/instructions/instruction_operands.h"

typedef struct {
  INSTRUCTION_BASE;
  RegisterIndex reg_index1;
  RegisterIndex reg_index2;
} TwoRegisterInstruction;

TwoRegisterInstruction *_newTwoRegisterInstruction(
    const Opcode opcode, const unsigned instruction_size, const uint8_t *data,
    const FlagIndexBitset flags_affected, const RegisterIndex reg_index1,
    const RegisterIndex reg_index2);
void _deleteTwoRegisterInstruction(TwoRegisterInstruction *instruction);

const TwoRegisterInstruction *castTwoRegisterInstruction(
    const Instruction *instruction) __attribute__((const));

#define TABLE_ITEM(opcode, ...) \
  void Execute_##opcode(Cpu *cpu, const TwoRegisterInstruction *instruction);
TWO_REGISTER_OPCODE_DEFS
#undef TABLE_ITEM

#endif  // EMULATOR_INSTRUCTIONS_TWO_REGISTER_INSTRUCTION_H_
