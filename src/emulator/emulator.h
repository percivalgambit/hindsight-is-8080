#ifndef EMULATOR_EMULATOR_H_
#define EMULATOR_EMULATOR_H_

#include "emulator/flags.h"

#include <stdio.h>

typedef struct EmulatorImpl Emulator;

typedef enum {
  RegisterIndex_B = 0,
  RegisterIndex_C = 1,
  RegisterIndex_D = 2,
  RegisterIndex_E = 3,
  RegisterIndex_H = 4,
  RegisterIndex_L = 5,
  RegisterIndex_FLAGS = 6,
  RegisterIndex_ACC = 7,
} RegisterIndex;

Emulator *newEmulator(FILE *program);
void deleteEmulator(Emulator *emulator);

void emulatorRun(Emulator *emulator);

Flags *emulatorFlags(Emulator *emulator) __attribute__((const));
Word emulatorProgramCounter(Emulator *emulator) __attribute__((const));

#endif  // EMULATOR_EMULATOR_H_
