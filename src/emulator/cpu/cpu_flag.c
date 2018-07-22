#include "emulator/cpu/cpu_flag.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "emulator/cpu/cpu.h"
#include "emulator/cpu/register_index.h"
#include "util/logging.h"

static bool _cpuFlagBitsetTest(const FlagIndexBitset bitset,
                               const FlagIndex index) {
  return bitset & index;
}

void cpuFlagSet(Cpu *cpu, const bool value, const FlagIndex index) {
  assert(cpu != NULL);

  uint8_t *flags = cpuGetByte(cpu, RegisterIndex_FLAGS);
  if (value) {
    *flags |= (uint8_t)index;
  } else {
    *flags &= (uint8_t)(~index);
  }
}

bool cpuFlagGet(const Cpu *cpu, const FlagIndex index) {
  assert(cpu != NULL);

  const uint8_t *flags = cpuGetByte((Cpu *)cpu, RegisterIndex_FLAGS);
  return *flags & (uint8_t)index;
}

void cpuFlagComplement(Cpu *cpu, const FlagIndex index) {
  assert(cpu != NULL);

  uint8_t *flags = cpuGetByte(cpu, RegisterIndex_FLAGS);
  *flags ^= (uint8_t)index;
}

void cpuFlagUpdateResult(Cpu *cpu, const FlagIndexBitset flags_affected,
                         const uint8_t result) {
  if (_cpuFlagBitsetTest(flags_affected, FlagIndex_PARITY)) {
    uint8_t parity = result;
    parity ^= parity >> 4;
    parity ^= parity >> 2;
    parity ^= parity >> 1;
    parity = (~parity) & 1;
    cpuFlagSet(cpu, parity, FlagIndex_PARITY);
  }
  if (_cpuFlagBitsetTest(flags_affected, FlagIndex_ZERO)) {
    cpuFlagSet(cpu, result == 0, FlagIndex_ZERO);
  }
  if (_cpuFlagBitsetTest(flags_affected, FlagIndex_SIGN)) {
    cpuFlagSet(cpu, (int8_t)result < 0, FlagIndex_SIGN);
  }
}

uint8_t cpuFlagUpdateAdd(Cpu *cpu, const FlagIndexBitset flags_affected,
                         const uint8_t operand1, const uint8_t operand2) {
  const uint16_t result = (uint16_t)(operand1 + operand2);
  if (_cpuFlagBitsetTest(flags_affected, FlagIndex_CARRY)) {
    cpuFlagSet(cpu, result & 0x100, FlagIndex_CARRY);
  }
  if (_cpuFlagBitsetTest(flags_affected, FlagIndex_AUXILIARY_CARRY)) {
    const uint8_t aux_result = (uint8_t)((operand1 & 0xF) + (operand2 & 0xF));
    cpuFlagSet(cpu, aux_result & 0x10, FlagIndex_AUXILIARY_CARRY);
  }

  cpuFlagUpdateResult(cpu, flags_affected, (uint8_t)result);
  return (uint8_t)result;
}

uint8_t cpuFlagUpdateSub(Cpu *cpu, const FlagIndexBitset flags_affected,
                         const uint8_t operand1, const uint8_t operand2) {
  const uint16_t result = (uint16_t)(operand1 - operand2);
  if (_cpuFlagBitsetTest(flags_affected, FlagIndex_CARRY)) {
    cpuFlagSet(cpu, result & 0x100, FlagIndex_CARRY);
  }
  if (_cpuFlagBitsetTest(flags_affected, FlagIndex_AUXILIARY_CARRY)) {
    const uint8_t aux_result = (uint8_t)((operand1 & 0xF) - (operand2 & 0xF));
    cpuFlagSet(cpu, aux_result & 0x10, FlagIndex_AUXILIARY_CARRY);
  }

  cpuFlagUpdateResult(cpu, flags_affected, (uint8_t)result);
  return (uint8_t)result;
}
