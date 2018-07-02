#include "emulator/cpu/cpu_flag.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "emulator/cpu/cpu.h"
#include "emulator/instructions/instruction_operands.h"
#include "util/logging.h"

void cpuFlagSet(Cpu *cpu, const bool value, const FlagIndex index) {
  assert(cpu != NULL);

  uint8_t *flags = _cpuGetByte(cpu, RegisterIndex_FLAGS);
  if (value) {
    *flags |= (uint8_t)index;
  } else {
    *flags &= (uint8_t)(~index);
  }
}

bool cpuFlagGet(const Cpu *cpu, const FlagIndex index) {
  assert(cpu != NULL);

  const uint8_t *flags = _cpuGetByte((Cpu *)cpu, RegisterIndex_FLAGS);
  return *flags & (uint8_t)index;
}

void cpuFlagComplement(Cpu *cpu, const FlagIndex index) {
  assert(cpu != NULL);

  uint8_t *flags = _cpuGetByte(cpu, RegisterIndex_FLAGS);
  *flags ^= (uint8_t)index;
}

bool cpuFlagBitsetTest(const FlagIndexBitset bitset, const FlagIndex index) {
  return bitset & index;
}
