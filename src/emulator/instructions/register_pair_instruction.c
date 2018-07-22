#include "emulator/instructions/register_pair_instruction.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "emulator/cpu/cpu_flag.h"
#include "emulator/cpu/register_index.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/opcode.h"

static RegisterPairInstruction register_pair_instruction;
static bool in_use;

RegisterPairInstruction *_newRegisterPairInstruction(
    const Opcode opcode, const unsigned instruction_size, const uint8_t *data,
    const FlagIndexBitset flags_affected,
    const RegisterPairIndex reg_pair_index) {
  assert(in_use == false);

  in_use = true;
  _initInstruction((Instruction *)&register_pair_instruction, opcode,
                   instruction_size, data, flags_affected,
                   InstructionType_REGISTER_PAIR);
  register_pair_instruction.reg_pair_index = reg_pair_index;
  return &register_pair_instruction;
}

void _deleteRegisterPairInstruction(RegisterPairInstruction *instruction
                                    __attribute__((unused))) {
  in_use = false;
}

const RegisterPairInstruction *castRegisterPairInstruction(
    const Instruction *instruction) {
  assert(instruction != NULL);
  assert(instruction->type == InstructionType_REGISTER_PAIR);

  return (const RegisterPairInstruction *)instruction;
}

void Execute_LDAX(Cpu *cpu, const RegisterPairInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->reg_pair_index == RegisterPairIndex_BC ||
         instruction->reg_pair_index == RegisterPairIndex_DE);

  uint8_t *acc = cpuGetByte(cpu, RegisterIndex_ACC);
  const uint16_t address = *cpuGetWord(cpu, instruction->reg_pair_index);
  *acc = *cpuGetMemoryByte(cpu, address);
}

void Execute_STAX(Cpu *cpu, const RegisterPairInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(instruction->reg_pair_index == RegisterPairIndex_BC ||
         instruction->reg_pair_index == RegisterPairIndex_DE);

  const uint16_t address = *cpuGetWord(cpu, instruction->reg_pair_index);
  uint8_t *dst = cpuGetMemoryByte(cpu, address);
  *dst = *cpuGetByte(cpu, RegisterIndex_ACC);
}

void Execute_LXI(Cpu *cpu, const RegisterPairInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterPairIndexOperand(instruction->reg_pair_index));
  assert(instruction->size == 3);

  uint16_t result = 0;
  result = (uint16_t)(result | (instruction->data[1] << 8));
  result = (uint16_t)(result | instruction->data[2]);
  uint16_t *dst = cpuGetWord(cpu, instruction->reg_pair_index);
  *dst = result;
}

void Execute_DAD(Cpu *cpu, const RegisterPairInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterPairIndexOperand(instruction->reg_pair_index));

  uint16_t *dst = cpuGetWord(cpu, RegisterPairIndex_HL);
  uint32_t result = *cpuGetWord(cpu, instruction->reg_pair_index);
  result += *dst;

  cpuFlagSet(cpu, FlagIndex_CARRY, result & 0x1000);
  *dst = (uint16_t)result;
}

void Execute_INX(Cpu *cpu, const RegisterPairInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterPairIndexOperand(instruction->reg_pair_index));

  uint16_t *dst = cpuGetWord(cpu, instruction->reg_pair_index);
  (*dst)++;
}

void Execute_DCX(Cpu *cpu, const RegisterPairInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterPairIndexOperand(instruction->reg_pair_index));

  uint16_t *dst = cpuGetWord(cpu, instruction->reg_pair_index);
  (*dst)--;
}

void Execute_PUSH(Cpu *cpu, const RegisterPairInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterPairIndexStackOperand(instruction->reg_pair_index));

  uint16_t *stack_pointer = cpuStackPointer(cpu);
  const uint16_t src = *cpuGetWord(cpu, instruction->reg_pair_index);
  cpuWriteWordToMemory(cpu, (uint16_t)(*stack_pointer - 2), src);
  *stack_pointer = (uint16_t)(*stack_pointer - 2);
}

void Execute_POP(Cpu *cpu, const RegisterPairInstruction *instruction) {
  assert(cpu != NULL);
  assert(instruction != NULL);
  assert(validRegisterPairIndexStackOperand(instruction->reg_pair_index));

  uint16_t *stack_pointer = cpuStackPointer(cpu);
  uint16_t *dst = cpuGetWord(cpu, instruction->reg_pair_index);
  *dst = cpuReadWordFromMemory(cpu, *stack_pointer);
  *stack_pointer = (uint16_t)(*stack_pointer + 2);
}
