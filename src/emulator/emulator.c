#include "emulator.h"

#include "emulator/instruction.h"
#include "emulator/io_device.h"
#include "emulator/memory.h"
#include "emulator/opcode_table.h"
#include "emulator/register.h"
#include "emulator/types.h"
#include "util/logging.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct EmulatorImpl {
  Register registers[8];
  Word program_counter;
  Word stack_pointer;
  Memory memory;
  // TODO: implement io devices
  struct IoDevice *io_devices[UINT8_MAX];
  bool halt;
};

Emulator *newEmulator(FILE *program) {
  assert(program != NULL);
  assert(!ferror(program));

  static const Register initFlags = 0x02;

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
    const Byte opcode = emulator->memory[emulator->program_counter];
    const OpcodeTableEntry *entry = &kOpcodeTable[opcode];
    if (emulator->program_counter + entry->instruction_size >=
        sizeof(emulator->memory)) {
      ERROR(
          "Attempting to read instruction of size %u, overrunning memory "
          "bounds of %d to address %" PRIu16,
          entry->instruction_size, kMemorySize,
          emulator->program_counter + entry->instruction_size);
    }
    const Instruction instruction = newInstruction(
        entry->opcode, entry->instruction_size, emulator->memory);
    emulator->program_counter++;
    instructionExecute(instruction, emulator);
  }
}

Flags *emulatorFlags(Emulator *emulator) {
  return &emulator->registers[RegisterIndex_FLAGS];
}

Word emulatorProgramCounter(Emulator *emulator) {
  return emulator->program_counter;
}
