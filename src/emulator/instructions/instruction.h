#ifndef EMULATOR_INSTRUCTIONS_INSTRUCTION_H_
#define EMULATOR_INSTRUCTIONS_INSTRUCTION_H_

#include <stdint.h>

#include "emulator/emulator.h"
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

void initInstruction(Instruction *instruction, const unsigned instruction_size,
                     const Opcode opcode, const uint8_t *data,
                     const InstructionType type);
void deleteInstruction(const Instruction *instruction);

Instruction *decodeInstruction(Emulator *emulator);
void executeInstruction(Emulator *emulator, const Instruction *instruction);

void Execute_INVALID(Emulator *emulator, const Instruction *instruction)
    __attribute__((noreturn));

#endif  // EMULATOR_INSTRUCTIONS_INSTRUCTION_H_
