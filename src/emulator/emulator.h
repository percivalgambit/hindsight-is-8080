#ifndef EMULATOR_EMULATOR_H_
#define EMULATOR_EMULATOR_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef enum {
  Register_B = 0,
  Register_C = 1,
  Register_D = 2,
  Register_E = 3,
  Register_H = 4,
  Register_L = 5,
  Register_FLAGS = 6,
  Register_ACCUMULATOR = 7,
} Register;

typedef enum {
  FlagPosition_CARRY = 0,
  FlagPosition_PARITY = 2,
  FlagPosition_AUXILIARY_CARRY = 4,
  FlagPosition_ZERO = 6,
  FlagPosition_SIGN = 7,
} FlagPosition;

typedef enum {
  InstructionMask_B = 0x0,
  InstructionMask_C = 0x1,
  InstructionMask_D = 0x2,
  InstructionMask_E = 0x3,
  InstructionMask_H = 0x4,
  InstructionMask_L = 0x5,
  InstructionMask_MEM = 0x6,
  InstructionMask_ACC = 0x7,
} InstructionMask;

typedef struct EmulatorImpl Emulator;

Emulator *newEmulator(FILE *program);
void deleteEmulator(const Emulator *emulator);

void emulatorRun(Emulator *emulator);

void setFlag(const bool value, const FlagPosition position, Emulator *emulator);
bool getFlag(const FlagPosition position, const Emulator *emulator);
void complementFlag(const FlagPosition position, Emulator *emulator);

int8_t *getRegister(const Register reg, Emulator *emulator);
uint16_t *getRegisterPair(const Register reg, Emulator *emulator);
int8_t *getRandomAccessMemoryByte(const uint16_t memory_location,
                                  Emulator *emulator);
int8_t *getMemoryByte(Emulator *emulator);
int8_t *getByteForInstructionMask(const InstructionMask mask,
                                  Emulator *emulator);

uint16_t getProgramCounter(const Emulator *emulator);

#endif  // EMULATOR_EMULATOR_H_
