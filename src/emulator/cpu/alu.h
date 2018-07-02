#ifndef EMULATOR_CPU_ALU_H_
#define EMULATOR_CPU_ALU_H_

#include "emulator/cpu/cpu.h"
#include "emulator/cpu/cpu_flag.h"
#include "emulator/instructions/instruction_operands.h"

void aluAdd(Cpu *cpu, const RegisterIndex dst_index,
            const RegisterIndex src_index,
            const FlagIndexBitset flags_affected);

#endif  // EMULATOR_CPU_ALU_H_
