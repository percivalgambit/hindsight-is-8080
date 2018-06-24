#include "emulator/cpu/cpu_flag.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "emulator/cpu/cpu.h"
#include "emulator/instructions/operands.h"
#include "util/logging.h"

__attribute__((const)) static unsigned _cpuFlagIndex(
    const FlagIndex flag_index) {
  switch (flag_index) {
    case FlagIndex_CARRY:
      return 0;
    case FlagIndex_PARITY:
      return 2;
    case FlagIndex_AUXILIARY_CARRY:
      return 4;
    case FlagIndex_ZERO:
      return 6;
    case FlagIndex_SIGN:
      return 7;
    default:
      ERROR("Unknown flag index value %u", flag_index);
  }
}

void cpuFlagSet(Cpu *cpu, const bool value, const FlagIndex index) {
  assert(cpu != NULL);

  uint8_t *flags = _cpuGetByte(cpu, RegisterIndex_FLAGS);
  if (value) {
    *flags |= (uint8_t)(1 << _cpuFlagIndex(index));
  } else {
    *flags &= (uint8_t)(~(1 << _cpuFlagIndex(index)));
  }
}

bool cpuFlagGet(const Cpu *cpu, const FlagIndex index) {
  assert(cpu != NULL);

  const uint8_t *flags = _cpuGetByte((Cpu *)cpu, RegisterIndex_FLAGS);
  return *flags & (1 << _cpuFlagIndex(index));
}

void cpuFlagComplement(Cpu *cpu, const FlagIndex index) {
  assert(cpu != NULL);

  uint8_t *flags = _cpuGetByte(cpu, RegisterIndex_FLAGS);
  *flags ^= (uint8_t)(1 << _cpuFlagIndex(index));
}
