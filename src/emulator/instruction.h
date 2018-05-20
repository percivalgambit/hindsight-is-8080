#ifndef EMULATOR_INSTRUCTION_H_
#define EMULATOR_INSTRUCTION_H_

#include "emulator/emulator.h"
#include "emulator/opcode.h"
#include "emulator/types.h"

typedef enum {
  InstructionRegisterOperand_B = 0,
  InstructionRegisterOperand_C = 1,
  InstructionRegisterOperand_D = 2,
  InstructionRegisterOperand_E = 3,
  InstructionRegisterOperand_H = 4,
  InstructionRegisterOperand_L = 5,
  InstructionRegisterOperand_MEM = 6,
  InstructionRegisterOperand_ACC = 7,
} InstructionRegisterOperand;

typedef enum {
  InstructionRegisterPairOperand_B,
  InstructionRegisterPairOperand_D,
  InstructionRegisterPairOperand_H,
  InstructionRegisterPairOperand_PSW,
  InstructionRegisterPairOperand_SP,
} InstructionRegisterPairOperand;

typedef struct {
  const Opcode opcode;
  const unsigned size;
  const Byte *data;
} Instruction;

typedef struct {
  const Opcode opcode;
  const unsigned size;
  const Byte *data;
} NullaryInstruction;

typedef struct {
  const Opcode opcode;
  const unsigned size;
  const Byte *data;
  const InstructionRegisterOperand reg;
} OneRegisterInstruction;

typedef struct {
  const Opcode opcode;
  const unsigned size;
  const Byte *data;
  const InstructionRegisterOperand reg1;
  const InstructionRegisterOperand reg2;
} TwoRegisterInstruction;

typedef struct {
  const Opcode opcode;
  const unsigned size;
  const Byte *data;
  const InstructionRegisterPairOperand reg_pair;
} RegisterPairInstruction;

Instruction newInstruction(const Opcode opcode, const unsigned instruction_size,
                           const Byte *memory) __attribute__((pure));

void instructionExecute(const Instruction instruction, Emulator *emulator);

#endif  // EMULATOR_INSTRUCTION_H_
