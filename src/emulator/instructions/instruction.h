#ifndef EMULATOR_INSTRUCTIONS_INSTRUCTION_H_
#define EMULATOR_INSTRUCTIONS_INSTRUCTION_H_

#include <stdint.h>

#include "emulator/cpu/cpu.h"
#include "emulator/cpu/cpu_flag.h"
#include "emulator/instructions/opcode.h"

#define kMaxInstructionSize 3

typedef enum {
  InstructionType_NULLARY,
  InstructionType_ONE_REGISTER,
  InstructionType_TWO_REGISTER,
  InstructionType_REGISTER_PAIR,
} InstructionType;

#define INSTRUCTION_BASE               \
  struct {                             \
    Opcode opcode;                     \
    unsigned size;                     \
    uint8_t data[kMaxInstructionSize]; \
    FlagIndexBitset flags_affected;    \
    InstructionType type;              \
  }

typedef INSTRUCTION_BASE Instruction;

void _initInstruction(Instruction *instruction, const Opcode opcode,
                      const unsigned instruction_size, const uint8_t *data,
                      const FlagIndexBitset flags_affected,
                      const InstructionType type);
void deleteInstruction(const Instruction *instruction);

Instruction *decodeInstruction(Cpu *cpu);
void executeInstruction(Cpu *cpu, const Instruction *instruction);

void Execute_INVALID(Cpu *cpu, const Instruction *instruction)
    __attribute__((noreturn));

#endif  // EMULATOR_INSTRUCTIONS_INSTRUCTION_H_
