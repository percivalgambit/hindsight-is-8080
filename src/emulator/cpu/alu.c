#include "emulator/cpu/alu.h"

#include <assert.h>

#include "emulator/cpu/cpu.h"
#include "emulator/cpu/cpu_flag.h"
#include "emulator/instructions/instruction_operands.h"

void aluAdd(Cpu *cpu, const RegisterIndex dst_index,
            const RegisterIndex src_index,
            const FlagIndexBitset flags_affected __attribute__((unused))) {
  assert(cpu != NULL);
  assert(dst_index != RegisterIndex_FLAGS);
  assert(src_index != RegisterIndex_FLAGS);

  int8_t *dst = (int8_t *)_cpuGetByte(cpu, dst_index);
  const int8_t src = *(int8_t *)_cpuGetByte(cpu, src_index);

  *dst = (int8_t)(*dst + src);
}
