#include "emulator/cpu/cpu.h"

#include "emulator/cpu/register_index.h"
#include "emulator/cpu/registers.h"
#include "emulator/instructions/instruction.h"
#include "emulator/io_device.h"
#include "util/logging.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Cpu {
  Registers *registers;
  uint16_t program_counter;
  uint16_t stack_pointer;
  uint8_t memory[kMemorySize];
  // TODO: implement io devices
  struct IoDevice *io_devices[kNumIoDevices];
  bool halt;
};

Cpu *newCpu(FILE *program) {
  assert(program != NULL);
  assert(!ferror(program));

  Cpu *cpu = calloc(1, sizeof(cpu));
  cpu->registers = _newRegisters();

  fread(cpu->memory, sizeof(cpu->memory), 1, program);
  if (ferror(program)) {
    fclose(program);
    ERROR("Could not read program contents");
  }
  if (!feof(program)) {
    WARNING("Program was too large to fit in memory");
  }
  fclose(program);
  return cpu;
}

void deleteCpu(Cpu *cpu) {
  assert(cpu != NULL);

  _deleteRegisters(cpu->registers);
  free(cpu);
}

void cpuRun(Cpu *cpu) {
  assert(cpu != NULL);

  while (!cpu->halt) {
    const Instruction *instruction = decodeInstruction(cpu);
    executeInstruction(cpu, instruction);
    deleteInstruction(instruction);
  }
}

void cpuHalt(Cpu *cpu) {
  assert(cpu != NULL);

  cpu->halt = true;
}

uint16_t *cpuStackPointer(Cpu *cpu) {
  assert(cpu != NULL);

  return &cpu->stack_pointer;
}

uint16_t *cpuProgramCounter(Cpu *cpu) {
  assert(cpu != NULL);

  return &cpu->program_counter;
}

uint8_t cpuGetAndAdvanceProgramCounter(Cpu *cpu) {
  assert(cpu != NULL);

  return cpu->memory[cpu->program_counter++];
}

uint8_t *cpuGetByte(Cpu *cpu, const RegisterIndex reg_index) {
  assert(cpu != NULL);

  if (reg_index == RegisterIndex_MEM) {
    const uint16_t address =
        *registerPairGet(cpu->registers, RegisterPairIndex_HL);
    return cpuGetMemoryByte(cpu, address);
  }
  return registerGet(cpu->registers, reg_index);
}

uint16_t *cpuGetWord(Cpu *cpu, const RegisterPairIndex reg_pair_index) {
  assert(cpu != NULL);

  if (reg_pair_index == RegisterPairIndex_SP) {
    return cpuStackPointer(cpu);
  }
  return registerPairGet(cpu->registers, reg_pair_index);
}

uint8_t *cpuGetMemoryByte(Cpu *cpu, const uint16_t address) {
  return &cpu->memory[address];
}

bool validRegisterIndexOperand(const RegisterIndex reg_index) {
  switch (reg_index) {
    case RegisterIndex_B:
    case RegisterIndex_C:
    case RegisterIndex_D:
    case RegisterIndex_E:
    case RegisterIndex_H:
    case RegisterIndex_L:
    case RegisterIndex_MEM:
    case RegisterIndex_ACC:
      return true;
    case RegisterIndex_FLAGS:
      return false;
    default:
      ERROR("Unknown register index value %u", reg_index);
  }
}

bool validRegisterPairIndexOperand(const RegisterPairIndex reg_pair_index) {
  switch (reg_pair_index) {
    case RegisterPairIndex_BC:
    case RegisterPairIndex_DE:
    case RegisterPairIndex_HL:
    case RegisterPairIndex_SP:
      return true;
    case RegisterPairIndex_PSW:
      return false;
    default:
      ERROR("Unknown register pair index value %u", reg_pair_index);
  }
}

bool validRegisterPairIndexStackOperand(
    const RegisterPairIndex reg_pair_index) {
  switch (reg_pair_index) {
    case RegisterPairIndex_BC:
    case RegisterPairIndex_DE:
    case RegisterPairIndex_HL:
    case RegisterPairIndex_PSW:
      return true;
    case RegisterPairIndex_SP:
      return false;
    default:
      ERROR("Unknown register pair index value %u", reg_pair_index);
  }
}

void cpuWriteWordToMemory(Cpu *cpu, const uint16_t address,
                          const uint16_t word) {
  assert(cpu != NULL);

  uint8_t *dst1 = cpuGetMemoryByte(cpu, address);
  uint8_t *dst2 = cpuGetMemoryByte(cpu, (uint16_t)(address + 1));
  *dst1 = (uint8_t)word;
  *dst2 = (uint8_t)(word >> 8);
}

uint16_t cpuReadWordFromMemory(const Cpu *cpu, const uint16_t address) {
  assert(cpu != NULL);

  uint16_t result = 0;
  result = (uint16_t)(result | *cpuGetMemoryByte((Cpu *)cpu, address));
  result = (uint16_t)(
      result | *cpuGetMemoryByte((Cpu *)cpu, (uint16_t)(address + 1)) << 8);
  return result;
}
