#include "emulator/cpu/registers.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "emulator/cpu/register_index.h"
#include "util/logging.h"

struct Registers {
  union {
    struct {
      uint8_t b;
      uint8_t c;
    };
    uint16_t bc;
  };
  union {
    struct {
      uint8_t d;
      uint8_t e;
    };
    uint16_t de;
  };
  union {
    struct {
      uint8_t h;
      uint8_t l;
    };
    uint16_t hl;
  };
  union {
    struct {
      uint8_t flags;
      uint8_t acc;
    };
    uint16_t psw;
  };
};

Registers *_newRegisters(void) {
  Registers *registers = calloc(1, sizeof(Registers));

  static const uint8_t initFlags = 0x02;
  registers->flags = initFlags;

  return registers;
}

void _deleteRegisters(Registers *registers) { free(registers); }

uint8_t *registerGet(Registers *registers, const RegisterIndex reg_index) {
  assert(registers != NULL);
  assert(reg_index != RegisterIndex_MEM);

  switch (reg_index) {
    case RegisterIndex_B:
      return &registers->b;
    case RegisterIndex_C:
      return &registers->c;
    case RegisterIndex_D:
      return &registers->d;
    case RegisterIndex_E:
      return &registers->e;
    case RegisterIndex_H:
      return &registers->h;
    case RegisterIndex_L:
      return &registers->l;
    case RegisterIndex_FLAGS:
      return &registers->flags;
    case RegisterIndex_ACC:
      return &registers->acc;
    case RegisterIndex_MEM:
    default:
      ERROR("Unknown register index %u", reg_index);
  }
}

uint16_t *registerPairGet(Registers *registers,
                          const RegisterPairIndex reg_pair_index) {
  assert(registers != NULL);
  assert(reg_pair_index != RegisterPairIndex_SP);

  switch (reg_pair_index) {
    case RegisterPairIndex_BC:
      return &registers->bc;
    case RegisterPairIndex_DE:
      return &registers->de;
    case RegisterPairIndex_HL:
      return &registers->hl;
    case RegisterPairIndex_PSW:
      return &registers->psw;
    case RegisterPairIndex_SP:
    default:
      ERROR("Unknown register pair index %u", reg_pair_index);
  }
}
