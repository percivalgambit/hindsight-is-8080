#ifndef EMULATOR_INSTRUCTIONS_OPERANDS_H_
#define EMULATOR_INSTRUCTIONS_OPERANDS_H_

typedef enum {
  RegisterIndex_B = 0,
  RegisterIndex_C = 1,
  RegisterIndex_D = 2,
  RegisterIndex_E = 3,
  RegisterIndex_H = 4,
  RegisterIndex_L = 5,
  RegisterIndex_FLAGS = 6,
  RegisterIndex_ACC = 7,
  RegisterIndex_MEM,
} RegisterIndex;

typedef enum {
  RegisterPairIndex_B = RegisterIndex_B,
  RegisterPairIndex_D = RegisterIndex_D,
  RegisterPairIndex_H = RegisterIndex_H,
  RegisterPairIndex_PSW = RegisterIndex_FLAGS,
  RegisterPairIndex_SP,
} RegisterPairIndex;

typedef enum {
  FlagIndex_CARRY = 0,
  FlagIndex_PARITY = 2,
  FlagIndex_AUXILIARY_CARRY = 4,
  FlagIndex_ZERO = 6,
  FlagIndex_SIGN = 7,
} FlagIndex;

#endif  // EMULATOR_INSTRUCTIONS_OPERANDS_H_
