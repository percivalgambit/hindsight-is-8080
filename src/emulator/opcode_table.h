#ifndef EMULATOR_OPCODE_TABLE_H_
#define EMULATOR_OPCODE_TABLE_H_

#include "emulator/opcode.h"

typedef struct {
  const Opcode opcode;
  const unsigned instruction_size;
} OpcodeTableEntry;

static const OpcodeTableEntry *kOpcodeTable[256];

#endif  // EMULATOR_OPCODE_TABLE_H_
