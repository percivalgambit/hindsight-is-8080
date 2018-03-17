#include "emulator.h"

#include "emulator/instruction.h"
#include "emulator/io_device.h"
#include "emulator/opcode_table.h"
#include "util/logging.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct EmulatorImpl {
  uint8_t registers[8];
  uint16_t program_counter;
  uint16_t stack_pointer;
  uint8_t memory[INT16_MAX];
  // TODO: implement io devices
  struct IoDevice *io_devices[INT8_MAX];
  bool halt;
};

Emulator *newEmulator(FILE *program) {
  assert(program != NULL);
  assert(!ferror(program));

  static const uint8_t initFlags = 0x02;

  Emulator *emulator = malloc(sizeof(Emulator));
  *emulator = (Emulator){.registers = {0},
                         .program_counter = 0,
                         .stack_pointer = 0,
                         .io_devices = {0},
                         .halt = false};
  emulator->registers[Register_FLAGS] = initFlags;

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

void deleteEmulator(const Emulator *emulator) {
  assert(emulator != NULL);

  free((void *)emulator);
}

void emulatorRun(Emulator *emulator) {
  assert(emulator != NULL);

  while (!emulator->halt) {
    const uint8_t opcode = emulator->memory[emulator->program_counter];
    const OpcodeTableEntry *entry = kOpcodeTable[opcode];
    if (emulator->program_counter + entry->instruction_size >=
        sizeof(emulator->memory)) {
      ERROR(
          "Attempting to read instruction of size %u, overrunning memory "
          "bounds of %lu to address %u",
          entry->instruction_size, sizeof(emulator->memory),
          emulator->program_counter + entry->instruction_size);
    }
    const Instruction instruction = newInstruction(
        entry->opcode, entry->instruction_size, emulator->memory);
    emulator->program_counter++;
    instructionExecute(instruction, emulator);
  }
}

void setFlag(const bool value, const FlagPosition position,
             Emulator *emulator) {
  if (value) {
    emulator->registers[Register_FLAGS] |= (1 << position);
  } else {
    emulator->registers[Register_FLAGS] &= ~(1 << position);
  }
}

bool getFlag(const FlagPosition position, const Emulator *emulator) {
  return emulator->registers[Register_FLAGS] & (1 << position);
}

void complementFlag(const FlagPosition position, Emulator *emulator) {
  emulator->registers[Register_FLAGS] ^= (1 << position);
}

int8_t *getRegister(const Register reg, Emulator *emulator) {
  return (int8_t *)&emulator->registers[reg];
}

uint16_t *getRegisterPair(const Register reg, Emulator *emulator) {
  return (uint16_t *)&emulator->registers[reg];
}

int8_t *getRandomAccessMemoryByte(const uint16_t memory_location,
                                  Emulator *emulator) {
  return (int8_t *)&emulator->memory[memory_location];
}

int8_t *getMemoryByte(Emulator *emulator) {
  return getRandomAccessMemoryByte(*getRegisterPair(Register_H, emulator),
                                   emulator);
}

int8_t *getByteForInstructionMask(const InstructionMask mask,
                                  Emulator *emulator) {
  switch (mask) {
    case InstructionMask_B:
      return getRegister(Register_B, emulator);
    case InstructionMask_C:
      return getRegister(Register_C, emulator);
    case InstructionMask_D:
      return getRegister(Register_D, emulator);
    case InstructionMask_E:
      return getRegister(Register_E, emulator);
    case InstructionMask_H:
      return getRegister(Register_H, emulator);
    case InstructionMask_L:
      return getRegister(Register_L, emulator);
    case InstructionMask_MEM:
      return getMemoryByte(emulator);
    case InstructionMask_ACC:
      return getRegister(Register_ACCUMULATOR, emulator);
    default:
      ERROR("This is impossible");
  }
}

uint16_t getProgramCounter(const Emulator *emulator) {
  return emulator->program_counter;
}
