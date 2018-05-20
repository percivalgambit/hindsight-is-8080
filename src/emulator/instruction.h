#ifndef EMULATOR_INSTRUCTION_H_
#define EMULATOR_INSTRUCTION_H_

#include "emulator/emulator.h"
#include "emulator/opcode.h"
#include "emulator/types.h"

typedef enum {
  InstructionType_NULLARY,
  InstructionType_ONE_REGISTER,
  InstructionType_TWO_REGISTER,
  InstructionType_REGISTER_PAIR,
} InstructionType;

typedef enum {
  InstructionRegisterOperand_B = 0,
  InstructionRegisterOperand_C = 1,
  InstructionRegisterOperand_D = 2,
  InstructionRegisterOperand_E = 3,
  InstructionRegisterOperand_H = 4,
  InstructionRegisterOperand_L = 5,
  InstructionRegisterOperand_MEM = 6,
  InstructionRegisterOperand_ACC = 7,
  InstructionRegisterOperand_INVALID = -1,
} InstructionRegisterOperand;

typedef enum {
  InstructionRegisterPairOperand_B,
  InstructionRegisterPairOperand_D,
  InstructionRegisterPairOperand_H,
  InstructionRegisterPairOperand_PSW,
  InstructionRegisterPairOperand_SP,
  InstructionRegisterPairOperand_INVALID = -1,
} InstructionRegisterPairOperand;

#define INSTRUCTION_BASE        \
  struct {                      \
    const Opcode opcode;        \
    const unsigned size;        \
    const Byte *data;           \
    const InstructionType type; \
  }

typedef INSTRUCTION_BASE Instruction;

typedef struct {
  INSTRUCTION_BASE;
} NullaryInstruction;

typedef struct {
  INSTRUCTION_BASE;
  const InstructionRegisterOperand reg;
} OneRegisterInstruction;

typedef struct {
  INSTRUCTION_BASE;
  const InstructionRegisterOperand reg1;
  const InstructionRegisterOperand reg2;
} TwoRegisterInstruction;

typedef struct {
  INSTRUCTION_BASE;
  const InstructionRegisterPairOperand reg_pair;
} RegisterPairInstruction;

#undef INSTRUCTION_BASE

NullaryInstruction newNullaryInstruction(const Opcode opcode,
                                         const unsigned instruction_size,
                                         const Byte *memory)
    __attribute__((const));

OneRegisterInstruction newOneRegisterInstruction(
    const Opcode opcode, const unsigned instruction_size, const Byte *memory,
    const InstructionRegisterOperand reg) __attribute__((const));

TwoRegisterInstruction newTwoRegisterInstruction(
    const Opcode opcode, const unsigned instruction_size, const Byte *memory,
    const InstructionRegisterOperand reg1,
    const InstructionRegisterOperand reg2) __attribute__((const));

RegisterPairInstruction newRegisterPairInstruction(
    const Opcode opcode, const unsigned instruction_size, const Byte *memory,
    const InstructionRegisterPairOperand reg_pair) __attribute__((const));

const NullaryInstruction *castNullaryInstruction(const Instruction *instruction)
    __attribute__((const));
const OneRegisterInstruction *castOneRegisterInstruction(
    const Instruction *instruction) __attribute__((const));
const TwoRegisterInstruction *castTwoRegisterInstruction(
    const Instruction *instruction) __attribute__((const));
const RegisterPairInstruction *castRegisterPairInstruction(
    const Instruction *instruction) __attribute__((const));

void instructionExecute(const Instruction *instruction, Emulator *emulator);

#endif  // EMULATOR_INSTRUCTION_H_
