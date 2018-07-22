#ifndef EMULATOR_CPU_REGISTER_INDEX_H_
#define EMULATOR_CPU_REGISTER_INDEX_H_

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

#endif  // EMULATOR_CPU_REGISTER_INDEX_H_
