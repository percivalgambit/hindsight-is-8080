#ifndef EMULATOR_INSTRUCTIONS_INSTRUCTION_HEADER_H_
#define EMULATOR_INSTRUCTIONS_INSTRUCTION_HEADER_H_

#include <stdint.h>

#include "emulator/cpu/cpu_flag.h"
#include "emulator/cpu/register_index.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"

#define kMaxNumOperands 2

typedef union {
  RegisterIndex reg_index;
  RegisterPairIndex reg_pair_index;
} InstructionOperand;

typedef struct {
  unsigned num_operands;
  InstructionOperand operands[kMaxNumOperands];
  InstructionType instruction_type;
} OperandEntry;

Opcode _instructionHeaderOpcode(const uint8_t instruction_header)
    __attribute__((const));
unsigned _instructionHeaderSize(const uint8_t instruction_header);
InstructionType _instructionHeaderType(const uint8_t instruction_header);
OperandEntry _instructionHeaderOperands(const uint8_t instruction_header)
    __attribute__((const));
FlagIndexBitset _instructionHeaderFlagsAffected(
    const uint8_t instruction_header) __attribute__((const));

#endif  // EMULATOR_INSTRUCTIONS_INSTRUCTION_HEADER_H_
