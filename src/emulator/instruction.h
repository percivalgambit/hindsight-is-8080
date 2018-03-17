#ifndef EMULATOR_INSTRUCTION_H_
#define EMULATOR_INSTRUCTION_H_

#include <stdint.h>

#include "emulator/emulator.h"
#include "emulator/opcode.h"

typedef struct {
  const Opcode opcode;
  const unsigned size;
  const uint8_t *data;
} Instruction;

Instruction newInstruction(const Opcode opcode, const unsigned instruction_size,
                           const uint8_t *memory);

void instructionExecute(const Instruction instruction, Emulator *emulator);

#endif  // EMULATOR_INSTRUCTION_H_
