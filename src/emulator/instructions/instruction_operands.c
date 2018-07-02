#include "emulator/instructions/instruction_operands.h"

#include "util/logging.h"

bool _validRegisterIndexOperand(const RegisterIndex reg_index) {
  switch (reg_index) {
    case RegisterIndex_B:
    case RegisterIndex_C:
    case RegisterIndex_D:
    case RegisterIndex_E:
    case RegisterIndex_H:
    case RegisterIndex_L:
    case RegisterIndex_MEM:
    case RegisterIndex_ACC:
      return true;
    case RegisterIndex_FLAGS:
      return false;
    default:
      ERROR("Unknown flag value %u", reg_index);
  }
}
