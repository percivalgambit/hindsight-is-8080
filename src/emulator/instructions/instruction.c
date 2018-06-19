#include "emulator/instructions/instruction.h"

#include <assert.h>
#include <inttypes.h>
#include <string.h>

#include "emulator/emulator.h"
#include "emulator/instructions/instruction_header.h"
#include "emulator/instructions/nullary_instruction.h"
#include "emulator/instructions/one_register_instruction.h"
#include "emulator/instructions/opcode.h"
#include "emulator/instructions/opcode_defs.h"
#include "emulator/instructions/register_pair_instruction.h"
#include "emulator/instructions/two_register_instruction.h"
#include "util/logging.h"

void initInstruction(Instruction *instruction, const Opcode opcode,
                     const unsigned instruction_size, const uint8_t *data,
                     const InstructionType type) {
  assert(instruction != NULL);
  assert(instruction_size <= kMaxInstructionSize);
  assert(data != NULL);

  *instruction =
      (Instruction){.opcode = opcode, .size = instruction_size, .type = type};
  memcpy(instruction->data, data, instruction_size);
}

void deleteInstruction(const Instruction *instruction) {
  assert(instruction != NULL);

  switch (instruction->type) {
    case InstructionType_NULLARY:
      deleteNullaryInstruction(castNullaryInstruction(instruction));
      break;
    case InstructionType_ONE_REGISTER:
      deleteOneRegisterInstruction(castOneRegisterInstruction(instruction));
      break;
    case InstructionType_TWO_REGISTER:
      deleteTwoRegisterInstruction(castTwoRegisterInstruction(instruction));
      break;
    case InstructionType_REGISTER_PAIR:
      deleteRegisterPairInstruction(castRegisterPairInstruction(instruction));
      break;
  }
}

Instruction *decodeInstruction(Emulator *emulator) {
  assert(emulator != NULL);

  const uint8_t instruction_header =
      emulatorGetAndAdvanceProgramCounter(emulator);
  const Opcode opcode = instructionHeaderOpcode(instruction_header);
  const OperandEntry operand_entry =
      instructionHeaderOperands(instruction_header);

  const unsigned instruction_size = instructionHeaderSize(instruction_header);
  uint8_t instruction_data[instruction_size];
  instruction_data[0] = instruction_header;
  for (unsigned i = 1; i < instruction_size; i++) {
    instruction_data[i] = emulatorGetAndAdvanceProgramCounter(emulator);
  }

  const InstructionType instruction_type =
      instructionHeaderType(instruction_header);
  switch (instruction_type) {
    case InstructionType_NULLARY:
      assert(operand_entry.instruction_type == InstructionType_NULLARY);
      assert(operand_entry.num_operands == 0);
      return (Instruction *)newNullaryInstruction(opcode, instruction_size,
                                                  instruction_data);
    case InstructionType_ONE_REGISTER:
      assert(operand_entry.instruction_type == InstructionType_ONE_REGISTER);
      assert(operand_entry.num_operands == 1);
      return (Instruction *)newOneRegisterInstruction(
          instruction_header, instruction_size, instruction_data,
          operand_entry.operands[0].reg_index);
    case InstructionType_TWO_REGISTER:
      assert(operand_entry.instruction_type == InstructionType_TWO_REGISTER);
      assert(operand_entry.num_operands == 2);
      return (Instruction *)newTwoRegisterInstruction(
          instruction_header, instruction_size, instruction_data,
          operand_entry.operands[0].reg_index,
          operand_entry.operands[1].reg_index);
    case InstructionType_REGISTER_PAIR:
      assert(operand_entry.instruction_type == InstructionType_REGISTER_PAIR);
      assert(operand_entry.num_operands == 1);
      return (Instruction *)newRegisterPairInstruction(
          instruction_header, instruction_size, instruction_data,
          operand_entry.operands[0].reg_pair_index);
    default:
      ERROR("Unknown instruction header type %u", instruction_type);
  }
}

void executeInstruction(Emulator *emulator, const Instruction *instruction) {
  switch (instruction->opcode) {
#define TABLE_ITEM(opcode, ...)                                      \
  case Opcode_##opcode:                                              \
    Execute_##opcode(emulator, castNullaryInstruction(instruction)); \
    break;
    NULLARY_OPCODE_DEFS
#undef TABLE_ITEM
#define TABLE_ITEM(opcode, ...)                                          \
  case Opcode_##opcode:                                                  \
    Execute_##opcode(emulator, castOneRegisterInstruction(instruction)); \
    break;
    ONE_REGISTER_OPCODE_DEFS
#undef TABLE_ITEM
#define TABLE_ITEM(opcode, ...)                                          \
  case Opcode_##opcode:                                                  \
    Execute_##opcode(emulator, castTwoRegisterInstruction(instruction)); \
    break;
    TWO_REGISTER_OPCODE_DEFS
#undef TABLE_ITEM
#define TABLE_ITEM(opcode, ...)                                           \
  case Opcode_##opcode:                                                   \
    Execute_##opcode(emulator, castRegisterPairInstruction(instruction)); \
    break;
    REGISTER_PAIR_OPCODE_DEFS
#undef TABLE_ITEM
    case Opcode_INVALID:
      Execute_INVALID(emulator, instruction);
  }
}

void Execute_INVALID(Emulator *emulator, const Instruction *instruction) {
  assert(instruction != NULL);
  assert(emulator != NULL);

  ERROR("Invalid instruction %" PRIu8 "encountered at position %" PRIu16,
        *instruction->data, emulatorProgramCounter(emulator));
}
