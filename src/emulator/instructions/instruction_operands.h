#ifndef EMULATOR_INSTRUCTIONS_INSTRUCTION_OPERANDS_H_
#define EMULATOR_INSTRUCTIONS_INSTRUCTION_OPERANDS_H_

#include <stdbool.h>
#include <stdint.h>

typedef enum {
  RegisterIndex_B,
  RegisterIndex_C,
  RegisterIndex_D,
  RegisterIndex_E,
  RegisterIndex_H,
  RegisterIndex_L,
  RegisterIndex_FLAGS,
  RegisterIndex_ACC,
  RegisterIndex_MEM,
} RegisterIndex;

typedef enum {
  RegisterPairIndex_BC,
  RegisterPairIndex_DE,
  RegisterPairIndex_HL,
  RegisterPairIndex_PSW,
  RegisterPairIndex_SP,
} RegisterPairIndex;

typedef union {
  RegisterIndex reg_index;
  RegisterPairIndex reg_pair_index;
} InstructionOperand;

bool _validRegisterIndexOperand(const RegisterIndex reg_index)
    __attribute__((const));

#endif  // EMULATOR_INSTRUCTIONS_INSTRUCTION_OPERANDS_H_
