#ifndef EMULATOR_EMULATOR_H_
#define EMULATOR_EMULATOR_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "emulator/instructions/operands.h"

typedef struct Emulator Emulator;

#define kNumRegisters 8
#define kMemorySize (UINT16_MAX + 1)
#define kNumIoDevices (UINT8_MAX + 1)

Emulator *newEmulator(FILE *program);
void deleteEmulator(Emulator *emulator);

void emulatorRun(Emulator *emulator);

uint16_t emulatorProgramCounter(const Emulator *emulator)
    __attribute__((const));
uint8_t emulatorGetAndAdvanceProgramCounter(Emulator *emulator);

void emulatorSetFlag(Emulator *emulator, const bool value,
                     const FlagIndex index);
bool emulatorGetFlag(const Emulator *emulator, const FlagIndex index)
    __attribute__((const));
void emulatorComplementFlag(Emulator *emulator, const FlagIndex index);

#endif  // EMULATOR_EMULATOR_H_
