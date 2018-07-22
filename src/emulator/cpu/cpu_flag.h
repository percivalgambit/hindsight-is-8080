#ifndef EMULATOR_CPU_CPU_FLAG_H_
#define EMULATOR_CPU_CPU_FLAG_H_

#include <stdbool.h>
#include <stdint.h>

#include "emulator/cpu/cpu.h"

typedef enum {
  FlagIndex_CARRY = 1,
  FlagIndex_PARITY = 1 << 2,
  FlagIndex_AUXILIARY_CARRY = 1 << 4,
  FlagIndex_ZERO = 1 << 6,
  FlagIndex_SIGN = 1 << 7,
} FlagIndex;

typedef FlagIndex FlagIndexBitset;

void cpuFlagSet(Cpu *cpu, const bool value, const FlagIndex index);
bool cpuFlagGet(const Cpu *cpu, const FlagIndex index) __attribute__((const));
void cpuFlagComplement(Cpu *cpu, const FlagIndex index);

void cpuFlagUpdateResult(Cpu *cpu, const FlagIndexBitset flags_affected,
                         const uint8_t result);
uint8_t cpuFlagUpdateAdd(Cpu *cpu, const FlagIndexBitset flags_affected,
                         const uint8_t operand1, const uint8_t operand2);
uint8_t cpuFlagUpdateSub(Cpu *cpu, const FlagIndexBitset flags_affected,
                         const uint8_t operand1, const uint8_t operand2);

#endif  // EMULATOR_CPU_CPU_FLAG_H_
