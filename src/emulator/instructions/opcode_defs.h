#ifndef EMULATOR_INSTRUCTIONS_OPCODE_DEFS_H_
#define EMULATOR_INSTRUCTIONS_OPCODE_DEFS_H_

#include "emulator/cpu/cpu_flag.h"

#define ALL_FLAGS (~0)
#define NO_FLAGS 0

// TABLE_ITEM(Enum opcode, unsigned instruction_size, FlagIndexBitset
// flags_affected)
#define NULLARY_OPCODE_DEFS                                                   \
  TABLE_ITEM(LDA, 3, NO_FLAGS)                                                \
  TABLE_ITEM(STA, 3, NO_FLAGS)                                                \
  TABLE_ITEM(LHLD, 3, NO_FLAGS)                                               \
  TABLE_ITEM(SHLD, 3, NO_FLAGS)                                               \
  TABLE_ITEM(SPHL, 1, NO_FLAGS)                                               \
  TABLE_ITEM(XCHG, 1, NO_FLAGS)                                               \
  TABLE_ITEM(XTHL, 1, NO_FLAGS)                                               \
  TABLE_ITEM(ADI, 2, ALL_FLAGS)                                               \
  TABLE_ITEM(ACI, 2, ALL_FLAGS)                                               \
  TABLE_ITEM(SUI, 2, ALL_FLAGS)                                               \
  TABLE_ITEM(SBI, 2, ALL_FLAGS)                                               \
  TABLE_ITEM(DI, 1, NO_FLAGS)                                                 \
  TABLE_ITEM(EI, 1, NO_FLAGS)                                                 \
  TABLE_ITEM(NOP, 1, NO_FLAGS)                                                \
  TABLE_ITEM(HLT, 1, NO_FLAGS)                                                \
  TABLE_ITEM(DAA, 1, ALL_FLAGS)                                               \
  TABLE_ITEM(CMA, 1, NO_FLAGS)                                                \
  TABLE_ITEM(STC, 1, FlagIndex_CARRY)                                         \
  TABLE_ITEM(CMC, 1, FlagIndex_CARRY)                                         \
  TABLE_ITEM(RLC, 1, FlagIndex_CARRY)                                         \
  TABLE_ITEM(RRC, 1, FlagIndex_CARRY)                                         \
  TABLE_ITEM(RAL, 1, FlagIndex_CARRY)                                         \
  TABLE_ITEM(RAR, 1, FlagIndex_CARRY)                                         \
  TABLE_ITEM(                                                                 \
      ANI, 2,                                                                 \
      (FlagIndex_CARRY | FlagIndex_PARITY | FlagIndex_ZERO | FlagIndex_SIGN)) \
  TABLE_ITEM(                                                                 \
      XRI, 2,                                                                 \
      (FlagIndex_CARRY | FlagIndex_PARITY | FlagIndex_ZERO | FlagIndex_SIGN)) \
  TABLE_ITEM(                                                                 \
      ORI, 2,                                                                 \
      (FlagIndex_CARRY | FlagIndex_PARITY | FlagIndex_ZERO | FlagIndex_SIGN)) \
  TABLE_ITEM(CPI, 2, ALL_FLAGS)                                               \
  TABLE_ITEM(JMP, 3, NO_FLAGS)                                                \
  TABLE_ITEM(JNZ, 3, NO_FLAGS)                                                \
  TABLE_ITEM(JZ, 3, NO_FLAGS)                                                 \
  TABLE_ITEM(JNC, 3, NO_FLAGS)                                                \
  TABLE_ITEM(JC, 3, NO_FLAGS)                                                 \
  TABLE_ITEM(JPO, 3, NO_FLAGS)                                                \
  TABLE_ITEM(JPE, 3, NO_FLAGS)                                                \
  TABLE_ITEM(JP, 3, NO_FLAGS)                                                 \
  TABLE_ITEM(JM, 3, NO_FLAGS)                                                 \
  TABLE_ITEM(PCHL, 1, NO_FLAGS)                                               \
  TABLE_ITEM(CALL, 3, NO_FLAGS)                                               \
  TABLE_ITEM(CNZ, 3, NO_FLAGS)                                                \
  TABLE_ITEM(CZ, 3, NO_FLAGS)                                                 \
  TABLE_ITEM(CNC, 3, NO_FLAGS)                                                \
  TABLE_ITEM(CC, 3, NO_FLAGS)                                                 \
  TABLE_ITEM(CPO, 3, NO_FLAGS)                                                \
  TABLE_ITEM(CPE, 3, NO_FLAGS)                                                \
  TABLE_ITEM(CP, 3, NO_FLAGS)                                                 \
  TABLE_ITEM(CM, 3, NO_FLAGS)                                                 \
  TABLE_ITEM(RET, 1, NO_FLAGS)                                                \
  TABLE_ITEM(RNZ, 1, NO_FLAGS)                                                \
  TABLE_ITEM(RZ, 1, NO_FLAGS)                                                 \
  TABLE_ITEM(RNC, 1, NO_FLAGS)                                                \
  TABLE_ITEM(RC, 1, NO_FLAGS)                                                 \
  TABLE_ITEM(RPO, 1, NO_FLAGS)                                                \
  TABLE_ITEM(RPE, 1, NO_FLAGS)                                                \
  TABLE_ITEM(RP, 1, NO_FLAGS)                                                 \
  TABLE_ITEM(RM, 1, NO_FLAGS)                                                 \
  TABLE_ITEM(RST, 1, NO_FLAGS)                                                \
  TABLE_ITEM(IN, 2, NO_FLAGS)                                                 \
  TABLE_ITEM(OUT, 2, NO_FLAGS)

#define ONE_REGISTER_OPCODE_DEFS                                              \
  TABLE_ITEM(MVI, 2, NO_FLAGS)                                                \
  TABLE_ITEM(ADD, 1, ALL_FLAGS)                                               \
  TABLE_ITEM(ADC, 1, ALL_FLAGS)                                               \
  TABLE_ITEM(SUB, 1, ALL_FLAGS)                                               \
  TABLE_ITEM(SBB, 1, ALL_FLAGS)                                               \
  TABLE_ITEM(INR, 1,                                                          \
             (FlagIndex_PARITY | FlagIndex_AUXILIARY_CARRY | FlagIndex_ZERO | \
              FlagIndex_SIGN))                                                \
  TABLE_ITEM(DCR, 1,                                                          \
             (FlagIndex_PARITY | FlagIndex_AUXILIARY_CARRY | FlagIndex_ZERO | \
              FlagIndex_SIGN))                                                \
  TABLE_ITEM(                                                                 \
      ANA, 1,                                                                 \
      (FlagIndex_CARRY | FlagIndex_PARITY | FlagIndex_ZERO | FlagIndex_SIGN)) \
  TABLE_ITEM(                                                                 \
      XRA, 1,                                                                 \
      (FlagIndex_CARRY | FlagIndex_PARITY | FlagIndex_ZERO | FlagIndex_SIGN)) \
  TABLE_ITEM(                                                                 \
      ORA, 1,                                                                 \
      (FlagIndex_CARRY | FlagIndex_PARITY | FlagIndex_ZERO | FlagIndex_SIGN)) \
  TABLE_ITEM(CMP, 1, ALL_FLAGS)

#define TWO_REGISTER_OPCODE_DEFS TABLE_ITEM(MOV, 1, NO_FLAGS)

#define REGISTER_PAIR_OPCODE_DEFS     \
  TABLE_ITEM(LDAX, 1, NO_FLAGS)       \
  TABLE_ITEM(STAX, 1, NO_FLAGS)       \
  TABLE_ITEM(LXI, 3, NO_FLAGS)        \
  TABLE_ITEM(DAD, 1, FlagIndex_CARRY) \
  TABLE_ITEM(INX, 1, NO_FLAGS)        \
  TABLE_ITEM(DCX, 1, NO_FLAGS)        \
  TABLE_ITEM(PUSH, 1, NO_FLAGS)       \
  TABLE_ITEM(POP, 1, NO_FLAGS)

#define OPCODE_DEFS         \
  NULLARY_OPCODE_DEFS       \
  ONE_REGISTER_OPCODE_DEFS  \
  TWO_REGISTER_OPCODE_DEFS  \
  REGISTER_PAIR_OPCODE_DEFS \
  TABLE_ITEM(INVALID, 1, NO_FLAGS)

#endif  // EMULATOR_INSTRUCTIONS_OPCODE_DEFS_H_
