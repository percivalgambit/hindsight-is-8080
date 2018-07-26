#include "emulator/instructions/instruction_header.h"

#include <stdint.h>

#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"
#include "emulator/instructions/opcode_defs.h"
#include "util/logging.h"

typedef struct {
  Opcode opcode;
  OperandEntry operand_entry;
} InstructionHeaderEntry;

#define NULLARY_OP(opcode_)                                      \
  {                                                              \
    .opcode = Opcode_##opcode_, .operand_entry.num_operands = 0, \
    .operand_entry.instruction_type = InstructionType_NULLARY    \
  }
#define ONE_REGISTER_OP(opcode_, reg_index_)                           \
  {                                                                    \
    .opcode = Opcode_##opcode_, .operand_entry.num_operands = 1,       \
    .operand_entry.operands[0].reg_index = RegisterIndex_##reg_index_, \
    .operand_entry.instruction_type = InstructionType_ONE_REGISTER     \
  }
#define TWO_REGISTER_OP(opcode_, reg_index1, reg_index2)               \
  {                                                                    \
    .opcode = Opcode_##opcode_, .operand_entry.num_operands = 2,       \
    .operand_entry.operands[0].reg_index = RegisterIndex_##reg_index1, \
    .operand_entry.operands[1].reg_index = RegisterIndex_##reg_index2, \
    .operand_entry.instruction_type = InstructionType_TWO_REGISTER     \
  }
#define REGISTER_PAIR_OP(opcode_, reg_pair_index_)                  \
  {                                                                 \
    .opcode = Opcode_##opcode_, .operand_entry.num_operands = 1,    \
    .operand_entry.operands[0].reg_pair_index =                     \
        RegisterPairIndex_##reg_pair_index_,                        \
    .operand_entry.instruction_type = InstructionType_REGISTER_PAIR \
  }

static const InstructionHeaderEntry kInstructionHeaderTable[UINT8_MAX + 1] = {
    [0x00] = NULLARY_OP(NOP),
    [0x01] = REGISTER_PAIR_OP(LXI, BC),
    [0x02] = REGISTER_PAIR_OP(STAX, BC),
    [0x03] = REGISTER_PAIR_OP(INX, BC),
    [0x04] = ONE_REGISTER_OP(INR, B),
    [0x05] = ONE_REGISTER_OP(DCR, B),
    [0x06] = ONE_REGISTER_OP(MVI, B),
    [0x07] = NULLARY_OP(RLC),
    [0x08] = NULLARY_OP(INVALID),
    [0x09] = REGISTER_PAIR_OP(DAD, BC),
    [0x0A] = REGISTER_PAIR_OP(LDAX, BC),
    [0x0B] = REGISTER_PAIR_OP(DCX, BC),
    [0x0C] = ONE_REGISTER_OP(INR, C),
    [0x0D] = ONE_REGISTER_OP(DCR, C),
    [0x0E] = ONE_REGISTER_OP(MVI, C),
    [0x0F] = NULLARY_OP(RRC),
    [0x10] = NULLARY_OP(INVALID),
    [0x11] = REGISTER_PAIR_OP(LXI, DE),
    [0x12] = REGISTER_PAIR_OP(STAX, DE),
    [0x13] = REGISTER_PAIR_OP(INX, DE),
    [0x14] = ONE_REGISTER_OP(INR, D),
    [0x15] = ONE_REGISTER_OP(DCR, D),
    [0x16] = ONE_REGISTER_OP(MVI, D),
    [0x17] = NULLARY_OP(RAL),
    [0x18] = NULLARY_OP(INVALID),
    [0x19] = REGISTER_PAIR_OP(DAD, DE),
    [0x1A] = REGISTER_PAIR_OP(LDAX, DE),
    [0x1B] = REGISTER_PAIR_OP(DCX, DE),
    [0x1C] = ONE_REGISTER_OP(INR, E),
    [0x1D] = ONE_REGISTER_OP(DCR, E),
    [0x1E] = ONE_REGISTER_OP(MVI, E),
    [0x1F] = NULLARY_OP(RAR),
    [0x20] = NULLARY_OP(INVALID),
    [0x21] = REGISTER_PAIR_OP(LXI, HL),
    [0x22] = NULLARY_OP(SHLD),
    [0x23] = REGISTER_PAIR_OP(INX, HL),
    [0x24] = ONE_REGISTER_OP(INR, H),
    [0x25] = ONE_REGISTER_OP(DCR, H),
    [0x26] = ONE_REGISTER_OP(MVI, H),
    [0x27] = NULLARY_OP(DAA),
    [0x28] = NULLARY_OP(INVALID),
    [0x29] = REGISTER_PAIR_OP(DAD, HL),
    [0x2A] = NULLARY_OP(LHLD),
    [0x2B] = REGISTER_PAIR_OP(DCX, HL),
    [0x2C] = ONE_REGISTER_OP(INR, L),
    [0x2D] = ONE_REGISTER_OP(DCR, L),
    [0x2E] = ONE_REGISTER_OP(MVI, L),
    [0x2F] = NULLARY_OP(CMA),
    [0x30] = NULLARY_OP(INVALID),
    [0x31] = REGISTER_PAIR_OP(LXI, SP),
    [0x32] = NULLARY_OP(STA),
    [0x33] = REGISTER_PAIR_OP(INX, SP),
    [0x34] = ONE_REGISTER_OP(INR, MEM),
    [0x35] = ONE_REGISTER_OP(DCR, MEM),
    [0x36] = ONE_REGISTER_OP(MVI, MEM),
    [0x37] = NULLARY_OP(STC),
    [0x38] = NULLARY_OP(INVALID),
    [0x39] = REGISTER_PAIR_OP(DAD, SP),
    [0x3A] = NULLARY_OP(LDA),
    [0x3B] = REGISTER_PAIR_OP(DCX, SP),
    [0x3C] = ONE_REGISTER_OP(INR, ACC),
    [0x3D] = ONE_REGISTER_OP(DCR, ACC),
    [0x3E] = ONE_REGISTER_OP(MVI, ACC),
    [0x3F] = NULLARY_OP(CMC),
    [0x40] = TWO_REGISTER_OP(MOV, B, B),
    [0x41] = TWO_REGISTER_OP(MOV, B, C),
    [0x42] = TWO_REGISTER_OP(MOV, B, D),
    [0x43] = TWO_REGISTER_OP(MOV, B, E),
    [0x44] = TWO_REGISTER_OP(MOV, B, H),
    [0x45] = TWO_REGISTER_OP(MOV, B, L),
    [0x46] = TWO_REGISTER_OP(MOV, B, MEM),
    [0x47] = TWO_REGISTER_OP(MOV, B, ACC),
    [0x48] = TWO_REGISTER_OP(MOV, C, B),
    [0x49] = TWO_REGISTER_OP(MOV, C, C),
    [0x4A] = TWO_REGISTER_OP(MOV, C, D),
    [0x4B] = TWO_REGISTER_OP(MOV, C, E),
    [0x4C] = TWO_REGISTER_OP(MOV, C, H),
    [0x4D] = TWO_REGISTER_OP(MOV, C, L),
    [0x4E] = TWO_REGISTER_OP(MOV, C, MEM),
    [0x4F] = TWO_REGISTER_OP(MOV, C, ACC),
    [0x50] = TWO_REGISTER_OP(MOV, D, B),
    [0x51] = TWO_REGISTER_OP(MOV, D, C),
    [0x52] = TWO_REGISTER_OP(MOV, D, D),
    [0x53] = TWO_REGISTER_OP(MOV, D, E),
    [0x54] = TWO_REGISTER_OP(MOV, D, H),
    [0x55] = TWO_REGISTER_OP(MOV, D, L),
    [0x56] = TWO_REGISTER_OP(MOV, D, MEM),
    [0x57] = TWO_REGISTER_OP(MOV, D, ACC),
    [0x58] = TWO_REGISTER_OP(MOV, E, B),
    [0x59] = TWO_REGISTER_OP(MOV, E, C),
    [0x5A] = TWO_REGISTER_OP(MOV, E, D),
    [0x5B] = TWO_REGISTER_OP(MOV, E, E),
    [0x5C] = TWO_REGISTER_OP(MOV, E, H),
    [0x5D] = TWO_REGISTER_OP(MOV, E, L),
    [0x5E] = TWO_REGISTER_OP(MOV, E, MEM),
    [0x5F] = TWO_REGISTER_OP(MOV, E, ACC),
    [0x60] = TWO_REGISTER_OP(MOV, H, B),
    [0x61] = TWO_REGISTER_OP(MOV, H, C),
    [0x62] = TWO_REGISTER_OP(MOV, H, D),
    [0x63] = TWO_REGISTER_OP(MOV, H, E),
    [0x64] = TWO_REGISTER_OP(MOV, H, H),
    [0x65] = TWO_REGISTER_OP(MOV, H, L),
    [0x66] = TWO_REGISTER_OP(MOV, H, MEM),
    [0x67] = TWO_REGISTER_OP(MOV, H, ACC),
    [0x68] = TWO_REGISTER_OP(MOV, L, B),
    [0x69] = TWO_REGISTER_OP(MOV, L, C),
    [0x6A] = TWO_REGISTER_OP(MOV, L, D),
    [0x6B] = TWO_REGISTER_OP(MOV, L, E),
    [0x6C] = TWO_REGISTER_OP(MOV, L, H),
    [0x6D] = TWO_REGISTER_OP(MOV, L, L),
    [0x6E] = TWO_REGISTER_OP(MOV, L, MEM),
    [0x6F] = TWO_REGISTER_OP(MOV, L, ACC),
    [0x70] = TWO_REGISTER_OP(MOV, MEM, B),
    [0x71] = TWO_REGISTER_OP(MOV, MEM, C),
    [0x72] = TWO_REGISTER_OP(MOV, MEM, D),
    [0x73] = TWO_REGISTER_OP(MOV, MEM, E),
    [0x74] = TWO_REGISTER_OP(MOV, MEM, H),
    [0x75] = TWO_REGISTER_OP(MOV, MEM, L),
    [0x76] = NULLARY_OP(HLT),
    [0x77] = TWO_REGISTER_OP(MOV, MEM, ACC),
    [0x78] = TWO_REGISTER_OP(MOV, ACC, B),
    [0x79] = TWO_REGISTER_OP(MOV, ACC, C),
    [0x7A] = TWO_REGISTER_OP(MOV, ACC, D),
    [0x7B] = TWO_REGISTER_OP(MOV, ACC, E),
    [0x7C] = TWO_REGISTER_OP(MOV, ACC, H),
    [0x7D] = TWO_REGISTER_OP(MOV, ACC, L),
    [0x7E] = TWO_REGISTER_OP(MOV, ACC, MEM),
    [0x7F] = TWO_REGISTER_OP(MOV, ACC, ACC),
    [0x80] = ONE_REGISTER_OP(ADD, B),
    [0x81] = ONE_REGISTER_OP(ADD, C),
    [0x82] = ONE_REGISTER_OP(ADD, D),
    [0x83] = ONE_REGISTER_OP(ADD, E),
    [0x84] = ONE_REGISTER_OP(ADD, H),
    [0x85] = ONE_REGISTER_OP(ADD, L),
    [0x86] = ONE_REGISTER_OP(ADD, MEM),
    [0x87] = ONE_REGISTER_OP(ADD, ACC),
    [0x88] = ONE_REGISTER_OP(ADC, B),
    [0x89] = ONE_REGISTER_OP(ADC, C),
    [0x8A] = ONE_REGISTER_OP(ADC, D),
    [0x8B] = ONE_REGISTER_OP(ADC, E),
    [0x8C] = ONE_REGISTER_OP(ADC, H),
    [0x8D] = ONE_REGISTER_OP(ADC, L),
    [0x8E] = ONE_REGISTER_OP(ADC, MEM),
    [0x8F] = ONE_REGISTER_OP(ADC, ACC),
    [0x90] = ONE_REGISTER_OP(SUB, B),
    [0x91] = ONE_REGISTER_OP(SUB, C),
    [0x92] = ONE_REGISTER_OP(SUB, D),
    [0x93] = ONE_REGISTER_OP(SUB, E),
    [0x94] = ONE_REGISTER_OP(SUB, H),
    [0x95] = ONE_REGISTER_OP(SUB, L),
    [0x96] = ONE_REGISTER_OP(SUB, MEM),
    [0x97] = ONE_REGISTER_OP(SUB, ACC),
    [0x98] = ONE_REGISTER_OP(SBB, B),
    [0x99] = ONE_REGISTER_OP(SBB, C),
    [0x9A] = ONE_REGISTER_OP(SBB, D),
    [0x9B] = ONE_REGISTER_OP(SBB, E),
    [0x9C] = ONE_REGISTER_OP(SBB, H),
    [0x9D] = ONE_REGISTER_OP(SBB, L),
    [0x9E] = ONE_REGISTER_OP(SBB, MEM),
    [0x9F] = ONE_REGISTER_OP(SBB, ACC),
    [0xA0] = ONE_REGISTER_OP(ANA, B),
    [0xA1] = ONE_REGISTER_OP(ANA, C),
    [0xA2] = ONE_REGISTER_OP(ANA, D),
    [0xA3] = ONE_REGISTER_OP(ANA, E),
    [0xA4] = ONE_REGISTER_OP(ANA, H),
    [0xA5] = ONE_REGISTER_OP(ANA, L),
    [0xA6] = ONE_REGISTER_OP(ANA, MEM),
    [0xA7] = ONE_REGISTER_OP(ANA, ACC),
    [0xA8] = ONE_REGISTER_OP(XRA, B),
    [0xA9] = ONE_REGISTER_OP(XRA, C),
    [0xAA] = ONE_REGISTER_OP(XRA, D),
    [0xAB] = ONE_REGISTER_OP(XRA, E),
    [0xAC] = ONE_REGISTER_OP(XRA, H),
    [0xAD] = ONE_REGISTER_OP(XRA, L),
    [0xAE] = ONE_REGISTER_OP(XRA, MEM),
    [0xAF] = ONE_REGISTER_OP(XRA, ACC),
    [0xB0] = ONE_REGISTER_OP(ORA, B),
    [0xB1] = ONE_REGISTER_OP(ORA, C),
    [0xB2] = ONE_REGISTER_OP(ORA, D),
    [0xB3] = ONE_REGISTER_OP(ORA, E),
    [0xB4] = ONE_REGISTER_OP(ORA, H),
    [0xB5] = ONE_REGISTER_OP(ORA, L),
    [0xB6] = ONE_REGISTER_OP(ORA, MEM),
    [0xB7] = ONE_REGISTER_OP(ORA, ACC),
    [0xB8] = ONE_REGISTER_OP(CMP, B),
    [0xB9] = ONE_REGISTER_OP(CMP, C),
    [0xBA] = ONE_REGISTER_OP(CMP, D),
    [0xBB] = ONE_REGISTER_OP(CMP, E),
    [0xBC] = ONE_REGISTER_OP(CMP, H),
    [0xBD] = ONE_REGISTER_OP(CMP, L),
    [0xBE] = ONE_REGISTER_OP(CMP, MEM),
    [0xBF] = ONE_REGISTER_OP(CMP, ACC),
    [0xC0] = NULLARY_OP(RNZ),
    [0xC1] = REGISTER_PAIR_OP(POP, BC),
    [0xC2] = NULLARY_OP(JNZ),
    [0xC3] = NULLARY_OP(JMP),
    [0xC4] = NULLARY_OP(CNZ),
    [0xC5] = REGISTER_PAIR_OP(PUSH, BC),
    [0xC6] = NULLARY_OP(ADI),
    [0xC7] = NULLARY_OP(RST),
    [0xC8] = NULLARY_OP(RZ),
    [0xC9] = NULLARY_OP(RET),
    [0xCA] = NULLARY_OP(JZ),
    [0xCB] = NULLARY_OP(INVALID),
    [0xCC] = NULLARY_OP(CZ),
    [0xCD] = NULLARY_OP(CALL),
    [0xCE] = NULLARY_OP(ACI),
    [0xCF] = NULLARY_OP(RST),
    [0xD0] = NULLARY_OP(RNC),
    [0xD1] = REGISTER_PAIR_OP(POP, DE),
    [0xD2] = NULLARY_OP(JNC),
    [0xD3] = NULLARY_OP(OUT),
    [0xD4] = NULLARY_OP(CNC),
    [0xD5] = REGISTER_PAIR_OP(PUSH, DE),
    [0xD6] = NULLARY_OP(SUI),
    [0xD7] = NULLARY_OP(RST),
    [0xD8] = NULLARY_OP(RC),
    [0xD9] = NULLARY_OP(INVALID),
    [0xDA] = NULLARY_OP(JC),
    [0xDB] = NULLARY_OP(IN),
    [0xDC] = NULLARY_OP(CC),
    [0xDD] = NULLARY_OP(INVALID),
    [0xDE] = NULLARY_OP(SBI),
    [0xDF] = NULLARY_OP(RST),
    [0xE0] = NULLARY_OP(RPO),
    [0xE1] = REGISTER_PAIR_OP(POP, HL),
    [0xE2] = NULLARY_OP(JPO),
    [0xE3] = NULLARY_OP(XTHL),
    [0xE4] = NULLARY_OP(CPO),
    [0xE5] = REGISTER_PAIR_OP(PUSH, HL),
    [0xE6] = NULLARY_OP(ANI),
    [0xE7] = NULLARY_OP(RST),
    [0xE8] = NULLARY_OP(RPE),
    [0xE9] = NULLARY_OP(PCHL),
    [0xEA] = NULLARY_OP(JPE),
    [0xEB] = NULLARY_OP(XCHG),
    [0xEC] = NULLARY_OP(CPE),
    [0xED] = NULLARY_OP(INVALID),
    [0xEE] = NULLARY_OP(XRI),
    [0xEF] = NULLARY_OP(RST),
    [0xF0] = NULLARY_OP(RP),
    [0xF1] = REGISTER_PAIR_OP(POP, PSW),
    [0xF2] = NULLARY_OP(JP),
    [0xF3] = NULLARY_OP(DI),
    [0xF4] = NULLARY_OP(CP),
    [0xF5] = REGISTER_PAIR_OP(PUSH, PSW),
    [0xF6] = NULLARY_OP(ORI),
    [0xF7] = NULLARY_OP(RST),
    [0xF8] = NULLARY_OP(RM),
    [0xF9] = NULLARY_OP(SPHL),
    [0xFA] = NULLARY_OP(JM),
    [0xFB] = NULLARY_OP(EI),
    [0xFC] = NULLARY_OP(CM),
    [0xFD] = NULLARY_OP(INVALID),
    [0xFE] = NULLARY_OP(CPI),
    [0xFF] = NULLARY_OP(RST),
};

Opcode _instructionHeaderOpcode(const uint8_t instruction_header) {
  const InstructionHeaderEntry entry =
      kInstructionHeaderTable[instruction_header];
  return entry.opcode;
}

unsigned _instructionHeaderSize(const uint8_t instruction_header) {
  const Opcode opcode = _instructionHeaderOpcode(instruction_header);
  switch (opcode) {
#define TABLE_ITEM(opcode, instruction_size, ...) \
  case Opcode_##opcode:                           \
    return instruction_size;
    OPCODE_DEFS
#undef TABLE_ITEM
    default:
      ERROR("Unknown opcode %u", opcode);
  }
}

InstructionType _instructionHeaderType(const uint8_t instruction_header) {
  const Opcode opcode = _instructionHeaderOpcode(instruction_header);
  switch (opcode) {
#define TABLE_ITEM(opcode, ...) \
  case Opcode_##opcode:         \
    return InstructionType_NULLARY;
    NULLARY_OPCODE_DEFS
#undef TABLE_ITEM
#define TABLE_ITEM(opcode, ...) \
  case Opcode_##opcode:         \
    return InstructionType_ONE_REGISTER;
    ONE_REGISTER_OPCODE_DEFS
#undef TABLE_ITEM
#define TABLE_ITEM(opcode, ...) \
  case Opcode_##opcode:         \
    return InstructionType_TWO_REGISTER;
    TWO_REGISTER_OPCODE_DEFS
#undef TABLE_ITEM
#define TABLE_ITEM(opcode, ...) \
  case Opcode_##opcode:         \
    return InstructionType_REGISTER_PAIR;
    REGISTER_PAIR_OPCODE_DEFS
#undef TABLE_ITEM
    case Opcode_INVALID:
      return InstructionType_NULLARY;
    default:
      ERROR("Unknown opcode %u", opcode);
  }
}

OperandEntry _instructionHeaderOperands(const uint8_t instruction_header) {
  const InstructionHeaderEntry entry =
      kInstructionHeaderTable[instruction_header];
  return entry.operand_entry;
}

FlagIndexBitset _instructionHeaderFlagsAffected(
    const uint8_t instruction_header) {
  const Opcode opcode = _instructionHeaderOpcode(instruction_header);
  switch (opcode) {
#define TABLE_ITEM(opcode, _, flags_affected) \
  case Opcode_##opcode:                       \
    return (FlagIndexBitset)flags_affected;
    OPCODE_DEFS
#undef TABLE_ITEM
    default:
      ERROR("Unknown opcode %u", opcode);
  }
}
