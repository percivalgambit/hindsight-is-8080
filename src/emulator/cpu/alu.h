#ifndef EMULATOR_CPU_ALU_H_
#define EMULATOR_CPU_ALU_H_

#include "emulator/cpu/cpu.h"
#include "emulator/instructions/operands.h"

void aluAdd(Cpu *cpu, const RegisterIndex dst_index,
            const RegisterIndex src_index);

#endif  // EMULATOR_CPU_ALU_H_
