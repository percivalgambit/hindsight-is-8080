#ifndef EMULATOR_CPU_REGISTERS_H_
#define EMULATOR_CPU_REGISTERS_H_

#include <stdint.h>

#include "emulator/cpu/register_index.h"

typedef struct Registers Registers;

Registers *_newRegisters(void);
void _deleteRegisters(Registers *registers);

uint8_t *registerGet(Registers *registers, const RegisterIndex reg_index);
uint16_t *registerPairGet(Registers *registers,
                          const RegisterPairIndex reg_pair_index);

#endif  // EMULATOR_CPU_REGISTERS_H_
