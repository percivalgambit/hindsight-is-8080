#include "emulator/instructions/nullary_instruction.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "emulator/cpu/cpu.h"
#include "emulator/cpu/cpu_flag.h"
#include "emulator/cpu/register_index.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"

static NullaryInstruction nullary_instruction;
static bool in_use;

NullaryInstruction *_newNullaryInstruction(
    const Opcode opcode, const unsigned instruction_size, const uint8_t *data,
    const FlagIndexBitset flags_affected) {
  assert(in_use == false);

  in_use = true;
  _initInstruction((Instruction *)&nullary_instruction, opcode,
                   instruction_size, data, flags_affected,
                   InstructionType_NULLARY);
  return &nullary_instruction;
}

void _deleteNullaryInstruction(NullaryInstruction *instruction
                               __attribute__((unused))) {
  in_use = false;
}

const NullaryInstruction *castNullaryInstruction(
    const Instruction *instruction) {
  assert(instruction != NULL);
  assert(instruction->type == InstructionType_NULLARY);

  return (const NullaryInstruction *)instruction;
}

void Execute_LDA(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);

  uint16_t address = 0;
  address = (uint16_t)(address | (instruction->data[1] << 8));
  address = (uint16_t)(address | instruction->data[2]);

  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc = *cpuGetMemoryByte(cpu, address);
}

void Execute_STA(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);

  uint16_t address = 0;
  address = (uint16_t)(address | (instruction->data[1] << 8));
  address = (uint16_t)(address | instruction->data[2]);

  uint8_t *dst = cpuGetMemoryByte(cpu, address);
  *dst = *cpuGetByte(cpu, RegisterIndex_ACC);
}

void Execute_LHLD(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);

  uint16_t address = 0;
  address = (uint16_t)(address | (instruction->data[1] << 8));
  address = (uint16_t)(address | instruction->data[2]);

  uint16_t *hl = cpuGetWord(cpu, RegisterPairIndex_HL);
  *hl = cpuReadWordFromMemory(cpu, address);
}

void Execute_SHLD(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);

  uint16_t address = 0;
  address = (uint16_t)(address | (instruction->data[1] << 8));
  address = (uint16_t)(address | instruction->data[2]);

  const uint16_t hl = *cpuGetWord(cpu, RegisterPairIndex_HL);
  cpuWriteWordToMemory(cpu, address, hl);
}

void Execute_XCHG(Cpu *cpu, const NullaryInstruction *instruction
                  __attribute__((unused))) {
  assert(cpu != NULL);

  uint16_t *de = cpuGetWord(cpu, RegisterPairIndex_DE);
  uint16_t *hl = cpuGetWord(cpu, RegisterPairIndex_HL);
  const uint16_t hl_val = *hl;
  *hl = *de;
  *de = hl_val;
}

void Execute_SPHL(Cpu *cpu, const NullaryInstruction *instruction
                  __attribute__((unused))) {
  assert(cpu != NULL);

  const uint16_t hl = *cpuGetWord(cpu, RegisterPairIndex_HL);
  uint16_t *stack_pointer = cpuStackPointer(cpu);

  *stack_pointer = hl;
}

void Execute_XTHL(Cpu *cpu, const NullaryInstruction *instruction
                  __attribute__((unused))) {
  assert(cpu != NULL);

  const uint16_t stack_pointer = *cpuStackPointer(cpu);
  const uint16_t stack_val = cpuReadWordFromMemory(cpu, stack_pointer);
  uint16_t *hl = cpuGetWord(cpu, RegisterPairIndex_HL);

  cpuWriteWordToMemory(cpu, stack_pointer, *hl);
  *hl = stack_val;
}

void Execute_ADI(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 2);

  const uint8_t src = instruction->data[1];
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc = cpuFlagUpdateAdd(cpu, instruction->flags_affected, *acc, src);
}

void Execute_ACI(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 2);

  const uint8_t src = instruction->data[1];
  const bool carry = cpuFlagGet(cpu, FlagIndex_CARRY);
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc = cpuFlagUpdateAdd(cpu, instruction->flags_affected, *acc,
                          carry ? (uint8_t)(src + 1) : src);
}

void Execute_SUI(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 2);

  const uint8_t src = instruction->data[1];
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc = cpuFlagUpdateSub(cpu, instruction->flags_affected, *acc, src);
}

void Execute_SBI(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 2);

  const uint8_t src = instruction->data[1];
  const bool carry = cpuFlagGet(cpu, FlagIndex_CARRY);
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc = cpuFlagUpdateSub(cpu, instruction->flags_affected, *acc,
                          carry ? (uint8_t)(src + 1) : src);
}

void Execute_CMA(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);

  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc = (uint8_t) ~(*acc);
}

void Execute_DI(Cpu *cpu __attribute__((unused)),
                const NullaryInstruction *instruction __attribute__((unused))) {
  // TODO: implement DI
}

void Execute_EI(Cpu *cpu __attribute__((unused)),
                const NullaryInstruction *instruction __attribute__((unused))) {
  // TODO: implement EI
}

void Execute_NOP(Cpu *cpu __attribute__((unused)),
                 const NullaryInstruction *instruction
                 __attribute__((unused))) {}

void Execute_HLT(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);

  cpuHalt(cpu);
}

void Execute_DAA(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);
}

void Execute_STC(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);

  cpuFlagSet(cpu, true, FlagIndex_CARRY);
}

void Execute_CMC(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);

  cpuFlagComplement(cpu, FlagIndex_CARRY);
}

void Execute_RLC(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);

  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  const bool highBit = *acc & 0x80;

  *acc = (uint8_t)(*acc << 1);
  *acc = (uint8_t)(*acc | (highBit ? 0x1 : 0x0));
  cpuFlagSet(cpu, FlagIndex_CARRY, highBit);
}

void Execute_RRC(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);

  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  const bool lowBit = *acc & 0x01;

  *acc = (uint8_t)(*acc >> 1);
  *acc = (uint8_t)(*acc | (lowBit ? 0x80 : 0x00));
  cpuFlagSet(cpu, FlagIndex_CARRY, lowBit);
}

void Execute_RAL(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);

  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  const bool highBit = *acc & 0x80;
  const bool carry = cpuFlagGet(cpu, FlagIndex_CARRY);

  *acc = (uint8_t)(*acc << 1);
  *acc = (uint8_t)(*acc | (carry ? 0x1 : 0x0));
  cpuFlagSet(cpu, FlagIndex_CARRY, highBit);
}

void Execute_RAR(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);

  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  const bool lowBit = *acc & 0x01;
  const bool carry = cpuFlagGet(cpu, FlagIndex_CARRY);

  *acc = (uint8_t)(*acc >> 1);
  *acc |= (uint8_t)(*acc | (carry ? 0x80 : 0x00));
  cpuFlagSet(cpu, FlagIndex_CARRY, lowBit);
}

void Execute_ANI(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 2);

  const uint8_t src = instruction->data[1];
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc &= src;

  cpuFlagUpdateResult(cpu, instruction->flags_affected, *acc);
  cpuFlagSet(cpu, FlagIndex_CARRY, false);
}

void Execute_XRI(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 2);

  const uint8_t src = instruction->data[1];
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc ^= src;

  cpuFlagUpdateResult(cpu, instruction->flags_affected, *acc);
  cpuFlagSet(cpu, FlagIndex_CARRY, false);
}

void Execute_ORI(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 2);

  const uint8_t src = instruction->data[1];
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc |= src;

  cpuFlagUpdateResult(cpu, instruction->flags_affected, *acc);
  cpuFlagSet(cpu, FlagIndex_CARRY, false);
}

void Execute_CPI(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 2);

  const uint8_t src = instruction->data[1];
  const uint8_t acc = *cpuGetByte(cpu, RegisterIndex_ACC);
  cpuFlagUpdateSub(cpu, instruction->flags_affected, acc, src);
}

void Execute_JMP(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);

  uint16_t address = 0;
  address = (uint16_t)(address | (instruction->data[1] << 8));
  address = (uint16_t)(address | instruction->data[2]);

  uint16_t *pc = cpuProgramCounter(cpu);
  *pc = address;
}

void Execute_JNZ(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);

  uint16_t address = 0;
  address = (uint16_t)(address | (instruction->data[1] << 8));
  address = (uint16_t)(address | instruction->data[2]);

  uint16_t *pc = cpuProgramCounter(cpu);
  if (!cpuFlagGet(cpu, FlagIndex_ZERO)) {
    *pc = address;
  }
}

void Execute_JZ(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);

  uint16_t address = 0;
  address = (uint16_t)(address | (instruction->data[1] << 8));
  address = (uint16_t)(address | instruction->data[2]);

  uint16_t *pc = cpuProgramCounter(cpu);
  if (cpuFlagGet(cpu, FlagIndex_ZERO)) {
    *pc = address;
  }
}

void Execute_JNC(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);

  uint16_t address = 0;
  address = (uint16_t)(address | (instruction->data[1] << 8));
  address = (uint16_t)(address | instruction->data[2]);

  uint16_t *pc = cpuProgramCounter(cpu);
  if (!cpuFlagGet(cpu, FlagIndex_CARRY)) {
    *pc = address;
  }
}

void Execute_JC(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);

  uint16_t address = 0;
  address = (uint16_t)(address | (instruction->data[1] << 8));
  address = (uint16_t)(address | instruction->data[2]);

  uint16_t *pc = cpuProgramCounter(cpu);
  if (cpuFlagGet(cpu, FlagIndex_CARRY)) {
    *pc = address;
  }
}

void Execute_JPO(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);

  uint16_t address = 0;
  address = (uint16_t)(address | (instruction->data[1] << 8));
  address = (uint16_t)(address | instruction->data[2]);

  uint16_t *pc = cpuProgramCounter(cpu);
  if (!cpuFlagGet(cpu, FlagIndex_PARITY)) {
    *pc = address;
  }
}

void Execute_JPE(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);

  uint16_t address = 0;
  address = (uint16_t)(address | (instruction->data[1] << 8));
  address = (uint16_t)(address | instruction->data[2]);

  uint16_t *pc = cpuProgramCounter(cpu);
  if (cpuFlagGet(cpu, FlagIndex_PARITY)) {
    *pc = address;
  }
}

void Execute_JP(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);

  uint16_t address = 0;
  address = (uint16_t)(address | (instruction->data[1] << 8));
  address = (uint16_t)(address | instruction->data[2]);

  uint16_t *pc = cpuProgramCounter(cpu);
  if (!cpuFlagGet(cpu, FlagIndex_SIGN)) {
    *pc = address;
  }
}

void Execute_JM(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);

  uint16_t address = 0;
  address = (uint16_t)(address | (instruction->data[1] << 8));
  address = (uint16_t)(address | instruction->data[2]);

  uint16_t *pc = cpuProgramCounter(cpu);
  if (cpuFlagGet(cpu, FlagIndex_SIGN)) {
    *pc = address;
  }
}

void Execute_PCHL(Cpu *cpu, const NullaryInstruction *instruction
                  __attribute__((unused))) {
  assert(cpu != NULL);

  uint16_t *pc = cpuProgramCounter(cpu);
  *pc = *cpuGetWord(cpu, RegisterPairIndex_HL);
}

void Execute_CALL(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);
}

void Execute_CNZ(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);
}

void Execute_CZ(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);
}

void Execute_CNC(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);
}

void Execute_CC(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);
}

void Execute_CPO(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);
}

void Execute_CPE(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);
}

void Execute_CP(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);
}

void Execute_CM(Cpu *cpu, const NullaryInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->size == 3);
}

void Execute_RET(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);
}

void Execute_RNZ(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);
}

void Execute_RZ(Cpu *cpu,
                const NullaryInstruction *instruction __attribute__((unused))) {
  assert(cpu != NULL);
}

void Execute_RNC(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);
}

void Execute_RC(Cpu *cpu,
                const NullaryInstruction *instruction __attribute__((unused))) {
  assert(cpu != NULL);
}

void Execute_RPO(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);
}

void Execute_RPE(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);
}

void Execute_RP(Cpu *cpu,
                const NullaryInstruction *instruction __attribute__((unused))) {
  assert(cpu != NULL);
}

void Execute_RM(Cpu *cpu,
                const NullaryInstruction *instruction __attribute__((unused))) {
  assert(cpu != NULL);
}

void Execute_RST(Cpu *cpu, const NullaryInstruction *instruction
                 __attribute__((unused))) {
  assert(cpu != NULL);
}

void Execute_IN(Cpu *cpu __attribute__((unused)),
                const NullaryInstruction *instruction __attribute__((unused))) {
  // TODO: implement IN
}

void Execute_OUT(Cpu *cpu __attribute__((unused)),
                 const NullaryInstruction *instruction
                 __attribute__((unused))) {
  // TODO: implement OUT
}
