#ifndef EMULATOR_INSTRUCTIONS_OPCODE_DEFS_H_
#define EMULATOR_INSTRUCTIONS_OPCODE_DEFS_H_

// TABLE_ITEM(Enum opcode, unsigned instruction_size)
#define NULLARY_OPCODE_DEFS \
  TABLE_ITEM(LDA, 3)        \
  TABLE_ITEM(STA, 3)        \
  TABLE_ITEM(LHLD, 3)       \
  TABLE_ITEM(SHLD, 3)       \
  TABLE_ITEM(SPHL, 1)       \
  TABLE_ITEM(XCHG, 1)       \
  TABLE_ITEM(XTHL, 1)       \
  TABLE_ITEM(ADI, 2)        \
  TABLE_ITEM(ACI, 2)        \
  TABLE_ITEM(SUI, 2)        \
  TABLE_ITEM(SBI, 2)        \
  TABLE_ITEM(DI, 1)         \
  TABLE_ITEM(EI, 1)         \
  TABLE_ITEM(NOP, 1)        \
  TABLE_ITEM(HLT, 1)        \
  TABLE_ITEM(DAA, 1)        \
  TABLE_ITEM(CMA, 1)        \
  TABLE_ITEM(STC, 1)        \
  TABLE_ITEM(CMC, 1)        \
  TABLE_ITEM(RLC, 1)        \
  TABLE_ITEM(RRC, 1)        \
  TABLE_ITEM(RAL, 1)        \
  TABLE_ITEM(RAR, 1)        \
  TABLE_ITEM(ANI, 2)        \
  TABLE_ITEM(XRI, 2)        \
  TABLE_ITEM(ORI, 2)        \
  TABLE_ITEM(CPI, 2)        \
  TABLE_ITEM(JMP, 3)        \
  TABLE_ITEM(JNZ, 3)        \
  TABLE_ITEM(JZ, 3)         \
  TABLE_ITEM(JNC, 3)        \
  TABLE_ITEM(JC, 3)         \
  TABLE_ITEM(JPO, 3)        \
  TABLE_ITEM(JPE, 3)        \
  TABLE_ITEM(JP, 3)         \
  TABLE_ITEM(JM, 3)         \
  TABLE_ITEM(PCHL, 1)       \
  TABLE_ITEM(CALL, 3)       \
  TABLE_ITEM(CNZ, 3)        \
  TABLE_ITEM(CZ, 3)         \
  TABLE_ITEM(CNC, 3)        \
  TABLE_ITEM(CC, 3)         \
  TABLE_ITEM(CPO, 3)        \
  TABLE_ITEM(CPE, 3)        \
  TABLE_ITEM(CP, 3)         \
  TABLE_ITEM(CM, 3)         \
  TABLE_ITEM(RET, 1)        \
  TABLE_ITEM(RNZ, 1)        \
  TABLE_ITEM(RZ, 1)         \
  TABLE_ITEM(RNC, 1)        \
  TABLE_ITEM(RC, 1)         \
  TABLE_ITEM(RPO, 1)        \
  TABLE_ITEM(RPE, 1)        \
  TABLE_ITEM(RP, 1)         \
  TABLE_ITEM(RM, 1)         \
  TABLE_ITEM(RST, 1)        \
  TABLE_ITEM(IN, 2)         \
  TABLE_ITEM(OUT, 2)

#define ONE_REGISTER_OPCODE_DEFS \
  TABLE_ITEM(MVI, 2)             \
  TABLE_ITEM(ADD, 1)             \
  TABLE_ITEM(ADC, 1)             \
  TABLE_ITEM(SUB, 1)             \
  TABLE_ITEM(SBB, 1)             \
  TABLE_ITEM(INR, 1)             \
  TABLE_ITEM(DCR, 1)             \
  TABLE_ITEM(ANA, 1)             \
  TABLE_ITEM(XRA, 1)             \
  TABLE_ITEM(ORA, 1)             \
  TABLE_ITEM(CMP, 1)

#define TWO_REGISTER_OPCODE_DEFS TABLE_ITEM(MOV, 1)

#define REGISTER_PAIR_OPCODE_DEFS \
  TABLE_ITEM(LDAX, 1)             \
  TABLE_ITEM(STAX, 1)             \
  TABLE_ITEM(LXI, 3)              \
  TABLE_ITEM(DAD, 1)              \
  TABLE_ITEM(INX, 1)              \
  TABLE_ITEM(DCX, 1)              \
  TABLE_ITEM(PUSH, 1)             \
  TABLE_ITEM(POP, 1)

#define OPCODE_DEFS         \
  NULLARY_OPCODE_DEFS       \
  ONE_REGISTER_OPCODE_DEFS  \
  TWO_REGISTER_OPCODE_DEFS  \
  REGISTER_PAIR_OPCODE_DEFS \
  TABLE_ITEM(INVALID, 1)

#endif  // EMULATOR_INSTRUCTIONS_OPCODE_DEFS_H_
