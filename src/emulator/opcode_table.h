#ifndef EMULATOR_OPCODE_TABLE_H_
#define EMULATOR_OPCODE_TABLE_H_

#include "emulator/instruction.h"
#include "emulator/opcode.h"

typedef union {
  InstructionRegisterOperand reg;
  InstructionRegisterPairOperand reg_pair;
} InstructionOperand;

typedef struct {
  const Opcode opcode;
  const unsigned instruction_size;
  const InstructionType type;
  const unsigned num_operands;
  const InstructionOperand operands[2];
} OpcodeTableEntry;

extern const OpcodeTableEntry kOpcodeTable[256];

#endif  // EMULATOR_OPCODE_TABLE_H_
