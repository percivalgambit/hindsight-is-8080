#include "emulator/cpu/cpu.h"

#include "emulator/cpu/registers.h"
#include "emulator/instructions/instruction.h"
#include "emulator/instructions/instruction_operands.h"
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

uint16_t cpuProgramCounter(const Cpu *cpu) {
  assert(cpu != NULL);

  return cpu->program_counter;
}

uint8_t cpuGetAndAdvanceProgramCounter(Cpu *cpu) {
  assert(cpu != NULL);

  return cpu->memory[cpu->program_counter++];
}

uint8_t *_cpuGetByte(Cpu *cpu, const RegisterIndex reg_index) {
  assert(cpu != NULL);

  if (reg_index == RegisterIndex_MEM) {
    const uint16_t address =
        *_registerPairGet(cpu->registers, RegisterPairIndex_HL);
    return &cpu->memory[address];
  }
  return _registerGet(cpu->registers, reg_index);
}
