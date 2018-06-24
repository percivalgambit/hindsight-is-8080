#ifndef EMULATOR_CPU_CPU_FLAG_H_
#define EMULATOR_CPU_CPU_FLAG_H_

#include <stdbool.h>

#include "emulator/cpu/cpu.h"
#include "emulator/instructions/operands.h"

void cpuFlagSet(Cpu *cpu, const bool value, const FlagIndex index);
bool cpuFlagGet(const Cpu *cpu, const FlagIndex index) __attribute__((const));
void cpuFlagComplement(Cpu *cpu, const FlagIndex index);

#endif  // EMULATOR_CPU_CPU_FLAG_H_
