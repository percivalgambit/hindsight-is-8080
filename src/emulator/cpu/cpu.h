#ifndef EMULATOR_CPU_CPU_H_
#define EMULATOR_CPU_CPU_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "emulator/cpu/register_index.h"

typedef struct Cpu Cpu;

#define kMemorySize (UINT16_MAX + 1)
#define kNumIoDevices (UINT8_MAX + 1)

Cpu *newCpu(FILE *program);
void deleteCpu(Cpu *cpu);

void cpuRun(Cpu *cpu);

void cpuHalt(Cpu *cpu);

uint16_t *cpuStackPointer(Cpu *cpu) __attribute__((const));
uint16_t *cpuProgramCounter(Cpu *cpu) __attribute__((const));
uint8_t cpuGetAndAdvanceProgramCounter(Cpu *cpu);

uint8_t *cpuGetByte(Cpu *cpu, const RegisterIndex reg_index)
    __attribute__((pure));
uint16_t *cpuGetWord(Cpu *cpu, const RegisterPairIndex reg_pair_index)
    __attribute__((pure));
uint8_t *cpuGetMemoryByte(Cpu *cpu, const uint16_t address)
    __attribute__((const));

bool validRegisterIndexOperand(const RegisterIndex reg_index)
    __attribute__((const));
bool validRegisterPairIndexOperand(const RegisterPairIndex reg_pair_index)
    __attribute__((const));
bool validRegisterPairIndexStackOperand(const RegisterPairIndex reg_pair_index)
    __attribute__((const));

void cpuWriteWordToMemory(Cpu *cpu, const uint16_t address,
                          const uint16_t word);
uint16_t cpuReadWordFromMemory(const Cpu *cpu, const uint16_t address)
    __attribute__((pure));

#endif  // EMULATOR_CPU_CPU_H_
