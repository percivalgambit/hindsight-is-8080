#ifndef EMULATOR_INSTRUCTIONS_INSTRUCTION_H_
#define EMULATOR_INSTRUCTIONS_INSTRUCTION_H_

#include <stdint.h>

#include "emulator/cpu/cpu.h"
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
    InstructionType type;              \
  }

typedef INSTRUCTION_BASE Instruction;

void _initInstruction(Instruction *instruction, const unsigned instruction_size,
                      const Opcode opcode, const uint8_t *data,
                      const InstructionType type);
void deleteInstruction(const Instruction *instruction);

Instruction *decodeInstruction(Cpu *cpu);
void executeInstruction(Cpu *cpu, const Instruction *instruction);

void Execute_INVALID(Cpu *cpu, const Instruction *instruction)
    __attribute__((noreturn));

#endif  // EMULATOR_INSTRUCTIONS_INSTRUCTION_H_
