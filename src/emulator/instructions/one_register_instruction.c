#include "emulator/instructions/one_register_instruction.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "emulator/cpu/cpu.h"
#include "emulator/cpu/cpu_flag.h"
#include "emulator/cpu/register_index.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"

static OneRegisterInstruction one_register_instruction;
static bool in_use;

OneRegisterInstruction *_newOneRegisterInstruction(
    const Opcode opcode, const unsigned instruction_size, const uint8_t *data,
    const FlagIndexBitset flags_affected, const RegisterIndex reg_index) {
  assert(in_use == false);

  in_use = true;
  _initInstruction((Instruction *)&one_register_instruction, opcode,
                   instruction_size, data, flags_affected,
                   InstructionType_ONE_REGISTER);
  one_register_instruction.reg_index = reg_index;
  return &one_register_instruction;
}

void _deleteOneRegisterInstruction(OneRegisterInstruction *instruction
                                   __attribute__((unused))) {
  in_use = false;
}

const OneRegisterInstruction *castOneRegisterInstruction(
    const Instruction *instruction) {
  assert(instruction != NULL);
  assert(instruction->type == InstructionType_ONE_REGISTER);

  return (const OneRegisterInstruction *)instruction;
}

void Execute_MVI(Cpu *cpu, const OneRegisterInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterIndexOperand(instruction->reg_index));
  assert(instruction->size == 2);

  uint8_t *dst = cpuGetByte(cpu, instruction->reg_index);
  *dst = instruction->data[1];
}

void Execute_ADD(Cpu *cpu, const OneRegisterInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterIndexOperand(instruction->reg_index));

  const uint8_t src = *cpuGetByte(cpu, instruction->reg_index);
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc = cpuFlagUpdateAdd(cpu, instruction->flags_affected, *acc, src);
}

void Execute_ADC(Cpu *cpu, const OneRegisterInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterIndexOperand(instruction->reg_index));

  const uint8_t src = *cpuGetByte(cpu, instruction->reg_index);
  const bool carry = cpuFlagGet(cpu, FlagIndex_CARRY);
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc = cpuFlagUpdateAdd(cpu, instruction->flags_affected, *acc,
                          carry ? (uint8_t)(src + 1) : src);
}

void Execute_SUB(Cpu *cpu, const OneRegisterInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterIndexOperand(instruction->reg_index));

  const uint8_t src = *cpuGetByte(cpu, instruction->reg_index);
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc = cpuFlagUpdateSub(cpu, instruction->flags_affected, *acc, src);
}

void Execute_SBB(Cpu *cpu, const OneRegisterInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterIndexOperand(instruction->reg_index));

  const uint8_t src = *cpuGetByte(cpu, instruction->reg_index);
  const bool carry = cpuFlagGet(cpu, FlagIndex_CARRY);
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc = cpuFlagUpdateSub(cpu, instruction->flags_affected, *acc,
                          carry ? (uint8_t)(src + 1) : src);
}

void Execute_INR(Cpu *cpu, const OneRegisterInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterIndexOperand(instruction->reg_index));

  uint8_t *dst = cpuGetByte(cpu, instruction->reg_index);
  *dst = cpuFlagUpdateAdd(cpu, instruction->flags_affected, *dst,
                          1 /* operand2 */);
}

void Execute_DCR(Cpu *cpu, const OneRegisterInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterIndexOperand(instruction->reg_index));

  uint8_t *dst = cpuGetByte(cpu, instruction->reg_index);
  *dst = cpuFlagUpdateSub(cpu, instruction->flags_affected, *dst,
                          1 /* operand2 */);
}

void Execute_ANA(Cpu *cpu, const OneRegisterInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterIndexOperand(instruction->reg_index));

  const uint8_t src = *cpuGetByte(cpu, instruction->reg_index);
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc &= src;

  cpuFlagUpdateResult(cpu, instruction->flags_affected, *acc);
  cpuFlagSet(cpu, FlagIndex_CARRY, false);
}

void Execute_XRA(Cpu *cpu, const OneRegisterInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterIndexOperand(instruction->reg_index));

  const uint8_t src = *cpuGetByte(cpu, instruction->reg_index);
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc ^= src;

  cpuFlagUpdateResult(cpu, instruction->flags_affected, *acc);
  cpuFlagSet(cpu, FlagIndex_CARRY, false);
}

void Execute_ORA(Cpu *cpu, const OneRegisterInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterIndexOperand(instruction->reg_index));

  const uint8_t src = *cpuGetByte(cpu, instruction->reg_index);
  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  *acc |= src;

  cpuFlagUpdateResult(cpu, instruction->flags_affected, *acc);
  cpuFlagSet(cpu, FlagIndex_CARRY, false);
}

void Execute_CMP(Cpu *cpu, const OneRegisterInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterIndexOperand(instruction->reg_index));

  const uint8_t src = *cpuGetByte(cpu, instruction->reg_index);
  const uint8_t acc = *cpuGetByte(cpu, RegisterIndex_ACC);
  cpuFlagUpdateSub(cpu, instruction->flags_affected, acc, src);
}
