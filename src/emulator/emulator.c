#include "emulator/emulator.h"

#include "emulator/instructions/instruction.h"
#include "emulator/instructions/operands.h"
#include "emulator/io_device.h"
#include "util/logging.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Emulator {
  uint8_t registers[kNumRegisters];
  uint16_t program_counter;
  uint16_t stack_pointer;
  uint8_t memory[kMemorySize];
  // TODO: implement io devices
  struct IoDevice *io_devices[kNumIoDevices];
  bool halt;
};

Emulator *newEmulator(FILE *program) {
  assert(program != NULL);
  assert(!ferror(program));

  static const uint8_t initFlags = 0x02;

  Emulator *emulator = calloc(1, sizeof(Emulator));
  emulator->registers[RegisterIndex_FLAGS] = initFlags;

  fread(emulator->memory, sizeof(emulator->memory), 1, program);
  if (ferror(program)) {
    fclose(program);
    ERROR("Could not read program contents");
  }
  if (!feof(program)) {
    WARNING("Program was too large to fit in memory");
  }
  fclose(program);
  return emulator;
}

void deleteEmulator(Emulator *emulator) {
  assert(emulator != NULL);

  free(emulator);
}

void emulatorRun(Emulator *emulator) {
  assert(emulator != NULL);

  while (!emulator->halt) {
    const Instruction *instruction = decodeInstruction(emulator);
    executeInstruction(emulator, instruction);
    deleteInstruction(instruction);
  }
}

uint16_t emulatorProgramCounter(const Emulator *emulator) {
  return emulator->program_counter;
}

uint8_t emulatorGetAndAdvanceProgramCounter(Emulator *emulator) {
  return emulator->memory[emulator->program_counter++];
}

void emulatorSetFlag(Emulator *emulator, const bool value,
                     const FlagIndex index) {
  assert(emulator != NULL);
  assert(index >= 0 && index < 8);

  uint8_t *flags = &emulator->registers[RegisterIndex_FLAGS];
  if (value) {
    *flags |= (uint8_t)(1 << index);
  } else {
    *flags &= (uint8_t)(~(1u << index));
  }
}

bool emulatorGetFlag(const Emulator *emulator, const FlagIndex index) {
  assert(emulator != NULL);
  assert(index >= 0 && index < 8);

  const uint8_t *flags = &emulator->registers[RegisterIndex_FLAGS];
  return *flags & (1 << index);
}

void emulatorComplementFlag(Emulator *emulator, const FlagIndex index) {
  assert(emulator != NULL);
  assert(index >= 0 && index < 8);

  uint8_t *flags = &emulator->registers[RegisterIndex_FLAGS];
  *flags ^= (uint8_t)(1 << index);
}
