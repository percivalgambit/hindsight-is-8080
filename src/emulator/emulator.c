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

struct Emulator {
  Register registers[8];
  Word program_counter;
  Word stack_pointer;
  Memory memory;
  // TODO: implement io devices
  struct IoDevice *io_devices[kNumIoDevices];
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
    if (emulator->program_counter + entry->instruction_size >= kMemorySize) {
      ERROR(
          "Attempting to read instruction of size %u, overrunning memory "
          "bounds of %d to address %" PRIu16,
          entry->instruction_size, kMemorySize,
          emulator->program_counter + entry->instruction_size);
    }
    emulator->program_counter++;
    switch (entry->type) {
      case InstructionType_NULLARY: {
        assert(entry->num_operands == 0);
        NullaryInstruction instruction =
            newNullaryInstruction(entry->opcode, entry->instruction_size,
                                  &emulator->memory[emulator->program_counter]);
        instructionExecute((Instruction *)&instruction, emulator);
        break;
      }
      case InstructionType_ONE_REGISTER: {
        assert(entry->num_operands == 1);
        OneRegisterInstruction instruction = newOneRegisterInstruction(
            entry->opcode, entry->instruction_size,
            &emulator->memory[emulator->program_counter],
            entry->operands[0].reg);
        instructionExecute((Instruction *)&instruction, emulator);
        break;
      }
      case InstructionType_TWO_REGISTER: {
        assert(entry->num_operands == 2);
        TwoRegisterInstruction instruction = newTwoRegisterInstruction(
            entry->opcode, entry->instruction_size,
            &emulator->memory[emulator->program_counter],
            entry->operands[0].reg, entry->operands[1].reg);
        instructionExecute((Instruction *)&instruction, emulator);
        break;
      }
      case InstructionType_REGISTER_PAIR: {
        assert(entry->num_operands == 1);
        RegisterPairInstruction instruction = newRegisterPairInstruction(
            entry->opcode, entry->instruction_size,
            &emulator->memory[emulator->program_counter],
            entry->operands[0].reg_pair);
        instructionExecute((Instruction *)&instruction, emulator);
        break;
      }
    }
  }
}

Flags *emulatorFlags(Emulator *emulator) {
  return &emulator->registers[RegisterIndex_FLAGS];
}

Word emulatorProgramCounter(Emulator *emulator) {
  return emulator->program_counter;
}
