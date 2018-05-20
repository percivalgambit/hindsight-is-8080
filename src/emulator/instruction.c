#include "emulator/instruction.h"

#include <assert.h>
#include <inttypes.h>

#include "emulator/emulator.h"
#include "emulator/opcode.h"
#include "emulator/opcode_defs.h"
#include "emulator/types.h"
#include "util/logging.h"

#define TABLE_ITEM(opcode, _)                                  \
  static void Execute_##opcode(const Instruction *instruction, \
                               Emulator *emulator);
OPCODE_DEFS
#undef TABLE_ITEM
static void Execute_INVALID(const Instruction *instruction, Emulator *emulator)
    __attribute__((noreturn));

NullaryInstruction newNullaryInstruction(const Opcode opcode,
                                         const unsigned instruction_size,
                                         const Byte *memory) {
  assert(instruction_size > 0);
  assert(memory != NULL);

  const NullaryInstruction instruction = {.opcode = opcode,
                                          .size = instruction_size,
                                          .data = memory,
                                          .type = InstructionType_NULLARY};
  return instruction;
}

OneRegisterInstruction newOneRegisterInstruction(
    const Opcode opcode, const unsigned instruction_size, const Byte *memory,
    const InstructionRegisterOperand reg) {
  assert(instruction_size > 0);
  assert(memory != NULL);
  assert(reg != InstructionRegisterOperand_INVALID);

  const OneRegisterInstruction instruction = {
      .opcode = opcode,
      .size = instruction_size,
      .data = memory,
      .type = InstructionType_ONE_REGISTER,
      .reg = reg};
  return instruction;
}

TwoRegisterInstruction newTwoRegisterInstruction(
    const Opcode opcode, const unsigned instruction_size, const Byte *memory,
    const InstructionRegisterOperand reg1,
    const InstructionRegisterOperand reg2) {
  assert(instruction_size > 0);
  assert(memory != NULL);
  assert(reg1 != InstructionRegisterOperand_INVALID);
  assert(reg2 != InstructionRegisterOperand_INVALID);

  const TwoRegisterInstruction instruction = {
      .opcode = opcode,
      .size = instruction_size,
      .data = memory,
      .type = InstructionType_TWO_REGISTER,
      .reg1 = reg1,
      .reg2 = reg2};
  return instruction;
}

RegisterPairInstruction newRegisterPairInstruction(
    const Opcode opcode, const unsigned instruction_size, const Byte *memory,
    const InstructionRegisterPairOperand reg_pair) {
  assert(instruction_size > 0);
  assert(memory != NULL);
  assert(reg_pair != InstructionRegisterPairOperand_INVALID);

  const RegisterPairInstruction instruction = {
      .opcode = opcode,
      .size = instruction_size,
      .data = memory,
      .type = InstructionType_REGISTER_PAIR,
      .reg_pair = reg_pair};
  return instruction;
}

const NullaryInstruction *castNullaryInstruction(
    const Instruction *instruction) {
  assert(instruction->type == InstructionType_NULLARY);
  return (const NullaryInstruction *)instruction;
}

const OneRegisterInstruction *castOneRegisterInstruction(
    const Instruction *instruction) {
  assert(instruction->type == InstructionType_ONE_REGISTER);
  return (const OneRegisterInstruction *)instruction;
}

const TwoRegisterInstruction *castTwoRegisterInstruction(
    const Instruction *instruction) {
  assert(instruction->type == InstructionType_TWO_REGISTER);
  return (const TwoRegisterInstruction *)instruction;
}

const RegisterPairInstruction *castRegisterPairInstruction(
    const Instruction *instruction) {
  assert(instruction->type == InstructionType_REGISTER_PAIR);
  return (const RegisterPairInstruction *)instruction;
}

void instructionExecute(const Instruction *instruction, Emulator *emulator) {
  switch (instruction->opcode) {
#define TABLE_ITEM(opcode, _)                \
  case Opcode_##opcode:                      \
    Execute_##opcode(instruction, emulator); \
    break;
    OPCODE_DEFS
#undef TABLE_ITEM
    case Opcode_INVALID:
      Execute_INVALID(instruction, emulator);
      break;
    default:
      ERROR("Unrecognized opcode: %u", instruction->opcode);
  }
}

static void Execute_MOV(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_LDAX(const Instruction *instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_LDA(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_MVI(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_STAX(const Instruction *instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_STA(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_LXI(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_LHLD(const Instruction *instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_SHLD(const Instruction *instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_SPHL(const Instruction *instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_XCHG(const Instruction *instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_XTHL(const Instruction *instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_ADD(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ADI(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ADC(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ACI(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_SUB(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_SUI(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_SBB(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_SBI(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_DAD(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_DI(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_EI(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_NOP(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_HLT(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_INR(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_DCR(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_INX(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_DCX(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_DAA(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CMA(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_STC(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CMC(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RLC(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RRC(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RAL(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RAR(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ANA(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ANI(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_XRA(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_XRI(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ORA(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_ORI(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CMP(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CPI(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_JMP(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_JNZ(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_JZ(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_JNC(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_JC(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_JPO(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_JPE(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_JP(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_JM(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_PCHL(const Instruction *instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_CALL(const Instruction *instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_CNZ(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CZ(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_CNC(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CC(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_CPO(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CPE(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_CP(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_CM(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_RET(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RNZ(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RZ(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_RNC(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RC(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_RPO(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RPE(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_RP(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_RM(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_RST(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_PUSH(const Instruction *instruction __attribute__((unused)),
                         Emulator *emulator __attribute__((unused))) {}

static void Execute_POP(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_IN(const Instruction *instruction __attribute__((unused)),
                       Emulator *emulator __attribute__((unused))) {}

static void Execute_OUT(const Instruction *instruction __attribute__((unused)),
                        Emulator *emulator __attribute__((unused))) {}

static void Execute_INVALID(const Instruction *instruction,
                            Emulator *emulator) {
  ERROR("Invalid instruction %" PRIu8 "encountered at position %" PRIu16,
        *instruction->data, emulatorProgramCounter(emulator));
}
