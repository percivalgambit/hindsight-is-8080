#ifndef EMULATOR_INSTRUCTIONS_OPERANDS_H_
#define EMULATOR_INSTRUCTIONS_OPERANDS_H_

#include <stdbool.h>

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

typedef enum {
  FlagIndex_CARRY,
  FlagIndex_PARITY,
  FlagIndex_AUXILIARY_CARRY,
  FlagIndex_ZERO,
  FlagIndex_SIGN,
} FlagIndex;

bool _operandValidRegisterIndexOperand(const RegisterIndex reg_index)
    __attribute__((const));

#endif  // EMULATOR_INSTRUCTIONS_OPERANDS_H_
