#include "emulator/instruction.h"

#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>

#include "emulator/emulator.h"
#include "emulator/opcode.h"
#include "util/logging.h"

#define TABLE_ITEM(opcode, _)                                 \
  static void Execute_##opcode(const Instruction instruction, \
                               Emulator *emulator);
#include "emulator/opcode_defs.h"
#undef TABLE_ITEM
static void Execute_INVALID(const Instruction instruction, Emulator *emulator)
    __attribute__((noreturn));

Instruction newInstruction(const Opcode opcode, const unsigned instruction_size,
                           const uint8_t *memory) {
  assert(instruction_size > 0);
  assert(memory != NULL);

  const Instruction instruction = {
      .opcode = opcode, .size = instruction_size, .data = memory};
  return instruction;
}

void instructionExecute(const Instruction instruction, Emulator *emulator) {
  switch (instruction.opcode) {
#define TABLE_ITEM(opcode, _)                \
  case Opcode_##opcode:                      \
    Execute_##opcode(instruction, emulator); \
    break;
#include "emulator/opcode_defs.h"
#undef TABLE_ITEM
    case Opcode_INVALID:
      Execute_INVALID(instruction, emulator);
      break;
    default:
      ERROR("Unrecognized opcode: %u", instruction.opcode);
  }
}

static bool getParity(const int8_t byte) {
  int8_t parity = byte;
  parity ^= parity >> 4;
  parity ^= parity >> 2;
  parity ^= parity >> 1;
  return (~parity) & 1;
}

static void Execute_MOV(const Instruction instruction, Emulator *emulator) {
  const uint8_t src_mask = *instruction.data & 0x7;
  const uint8_t dst_mask = (*instruction.data >> 3) & 0x7;
  const int8_t src = *getByteForInstructionMask(src_mask, emulator);
  int8_t *dst = getByteForInstructionMask(dst_mask, emulator);
  *dst = src;
}

static void Execute_LDAX(const Instruction instruction, Emulator *emulator) {
  const Register reg =
      (*instruction.data >> 4) & 0x01 ? Register_D : Register_B;
  const uint16_t memory_location = *getRegisterPair(reg, emulator);
  const int8_t src = *getRandomAccessMemoryByte(memory_location, emulator);
  int8_t *acc = getRegister(Register_ACCUMULATOR, emulator);
  *acc = src;
}

static void Execute_LDA(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_MVI(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_STAX(const Instruction instruction, Emulator *emulator) {
  const Register reg =
      (*instruction.data >> 4) & 0x01 ? Register_D : Register_B;
  const uint16_t memory_location = *getRegisterPair(reg, emulator);
  const int8_t acc_value = *getRegister(Register_ACCUMULATOR, emulator);
  int8_t *dst = getRandomAccessMemoryByte(memory_location, emulator);
  *dst = acc_value;
}

static void Execute_STA(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_LXI(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_LHLD(const Instruction instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_SHLD(const Instruction instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_SPHL(const Instruction instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_XCHG(const Instruction instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_XTHL(const Instruction instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_ADD(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ADI(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ADC(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ACI(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_SUB(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_SUI(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_SBB(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_SBI(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_DAD(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_DI(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_EI(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_NOP(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_HLT(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_INR(const Instruction instruction, Emulator *emulator) {
  const uint8_t mask = (*instruction.data >> 3) & 0x7;
  int8_t *byte = getByteForInstructionMask(mask, emulator);
  (*byte)++;

  setFlag(*byte == 0, FlagPosition_ZERO, emulator);
  setFlag(*byte < 0, FlagPosition_SIGN, emulator);
  setFlag(getParity(*byte), FlagPosition_PARITY, emulator);
  const bool auxiliary_carry = !(*byte & 0xF);
  setFlag(auxiliary_carry, FlagPosition_AUXILIARY_CARRY, emulator);
}

static void Execute_DCR(const Instruction instruction, Emulator *emulator) {
  const uint8_t mask = (*instruction.data >> 3) & 0x7;
  int8_t *byte = getByteForInstructionMask(mask, emulator);
  (*byte)--;

  setFlag(*byte == 0, FlagPosition_ZERO, emulator);
  setFlag(*byte < 0, FlagPosition_SIGN, emulator);
  setFlag(getParity(*byte), FlagPosition_PARITY, emulator);
  const bool auxiliary_carry = *byte & 0x0F;
  setFlag(auxiliary_carry, FlagPosition_AUXILIARY_CARRY, emulator);
}

static void Execute_INX(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_DCX(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_DAA(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator) {
  int8_t *accumulator = getRegister(Register_ACCUMULATOR, emulator);
  const int8_t lower_nibble = *accumulator & 0x0F;
  if (lower_nibble > 9 || getFlag(FlagPosition_AUXILIARY_CARRY, emulator)) {
    setFlag((lower_nibble + 0x06) | 0x10, FlagPosition_AUXILIARY_CARRY,
            emulator);
    *accumulator += 0x06;
  }
  const int8_t upper_nibble = (*accumulator >> 4) & 0x0F;
  if (upper_nibble > 9 || getFlag(FlagPosition_CARRY, emulator)) {
    setFlag((upper_nibble + 0x06) | 0x10, FlagPosition_CARRY, emulator);
    *accumulator += 0x60;
  }
  setFlag(*accumulator == 0, FlagPosition_ZERO, emulator);
  setFlag(*accumulator < 0, FlagPosition_SIGN, emulator);
  setFlag(getParity(*accumulator), FlagPosition_PARITY, emulator);
}

static void Execute_CMA(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator) {
  int8_t *accumulator = getRegister(Register_ACCUMULATOR, emulator);
  *accumulator = ~(*accumulator);
}

static void Execute_STC(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator) {
  setFlag(true, FlagPosition_CARRY, emulator);
}

static void Execute_CMC(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator) {
  complementFlag(FlagPosition_CARRY, emulator);
}

static void Execute_RLC(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RRC(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RAL(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RAR(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ANA(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ANI(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_XRA(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_XRI(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ORA(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ORI(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CMP(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CPI(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_JMP(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_JNZ(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_JZ(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_JNC(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_JC(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_JPO(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_JPE(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_JP(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_JM(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_PCHL(const Instruction instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_CALL(const Instruction instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_CNZ(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CZ(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_CNC(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CC(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_CPO(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CPE(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CP(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_CM(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_RET(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RNZ(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RZ(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_RNC(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RC(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_RPO(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RPE(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RP(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_RM(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_RST(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_PUSH(const Instruction instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_POP(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_IN(const Instruction instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_OUT(const Instruction instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_INVALID(const Instruction instruction, Emulator *emulator) {
  ERROR("Invalid instruction %" PRIu8 "encountered at position %" PRIi16,
        *instruction.data, getProgramCounter(emulator));
}
