#ifndef EMULATOR_CPU_CPU_H_
#define EMULATOR_CPU_CPU_H_

#include <stdint.h>
#include <stdio.h>

#include "emulator/instructions/instruction_operands.h"

typedef struct Cpu Cpu;

#define kMemorySize (UINT16_MAX + 1)
#define kNumIoDevices (UINT8_MAX + 1)

Cpu *newCpu(FILE *program);
void deleteCpu(Cpu *cpu);

void cpuRun(Cpu *cpu);

uint16_t cpuProgramCounter(const Cpu *cpu) __attribute__((const));
uint8_t cpuGetAndAdvanceProgramCounter(Cpu *cpu);

uint8_t *_cpuGetByte(Cpu *cpu, const RegisterIndex reg_index)
    __attribute__((pure));

#endif  // EMULATOR_CPU_CPU_H_
