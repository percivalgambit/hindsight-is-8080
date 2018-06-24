#include "emulator/instructions/instruction.h"

#include <assert.h>
#include <inttypes.h>
#include <string.h>

#include "emulator/cpu/cpu.h"
#include "emulator/instructions/instruction_header.h"
#include "emulator/instructions/nullary_instruction.h"
#include "emulator/instructions/one_register_instruction.h"
#include "emulator/instructions/opcode.h"
#include "emulator/instructions/opcode_defs.h"
#include "emulator/instructions/register_pair_instruction.h"
#include "emulator/instructions/two_register_instruction.h"
#include "util/logging.h"

void _initInstruction(Instruction *instruction, const Opcode opcode,
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
      _deleteNullaryInstruction(
          (NullaryInstruction *)castNullaryInstruction(instruction));
      break;
    case InstructionType_ONE_REGISTER:
      _deleteOneRegisterInstruction(
          (OneRegisterInstruction *)castOneRegisterInstruction(instruction));
      break;
    case InstructionType_TWO_REGISTER:
      _deleteTwoRegisterInstruction(
          (TwoRegisterInstruction *)castTwoRegisterInstruction(instruction));
      break;
    case InstructionType_REGISTER_PAIR:
      _deleteRegisterPairInstruction(
          (RegisterPairInstruction *)castRegisterPairInstruction(instruction));
      break;
  }
}

Instruction *decodeInstruction(Cpu *cpu) {
  assert(cpu != NULL);

  const uint8_t instruction_header = cpuGetAndAdvanceProgramCounter(cpu);
  const Opcode opcode = _instructionHeaderOpcode(instruction_header);
  const OperandEntry operand_entry =
      _instructionHeaderOperands(instruction_header);

  const unsigned instruction_size = _instructionHeaderSize(instruction_header);
  uint8_t instruction_data[instruction_size];
  instruction_data[0] = instruction_header;
  for (unsigned i = 1; i < instruction_size; i++) {
    instruction_data[i] = cpuGetAndAdvanceProgramCounter(cpu);
  }

  const InstructionType instruction_type =
      _instructionHeaderType(instruction_header);
  switch (instruction_type) {
    case InstructionType_NULLARY:
      assert(operand_entry.instruction_type == InstructionType_NULLARY);
      assert(operand_entry.num_operands == 0);
      return (Instruction *)_newNullaryInstruction(opcode, instruction_size,
                                                   instruction_data);
    case InstructionType_ONE_REGISTER:
      assert(operand_entry.instruction_type == InstructionType_ONE_REGISTER);
      assert(operand_entry.num_operands == 1);
      return (Instruction *)_newOneRegisterInstruction(
          instruction_header, instruction_size, instruction_data,
          operand_entry.operands[0].reg_index);
    case InstructionType_TWO_REGISTER:
      assert(operand_entry.instruction_type == InstructionType_TWO_REGISTER);
      assert(operand_entry.num_operands == 2);
      return (Instruction *)_newTwoRegisterInstruction(
          instruction_header, instruction_size, instruction_data,
          operand_entry.operands[0].reg_index,
          operand_entry.operands[1].reg_index);
    case InstructionType_REGISTER_PAIR:
      assert(operand_entry.instruction_type == InstructionType_REGISTER_PAIR);
      assert(operand_entry.num_operands == 1);
      return (Instruction *)_newRegisterPairInstruction(
          instruction_header, instruction_size, instruction_data,
          operand_entry.operands[0].reg_pair_index);
    default:
      ERROR("Unknown instruction header type %u", instruction_type);
  }
}

void executeInstruction(Cpu *cpu, const Instruction *instruction) {
  switch (instruction->opcode) {
#define TABLE_ITEM(opcode, ...)                                 \
  case Opcode_##opcode:                                         \
    Execute_##opcode(cpu, castNullaryInstruction(instruction)); \
    break;
    NULLARY_OPCODE_DEFS
#undef TABLE_ITEM
#define TABLE_ITEM(opcode, ...)                                     \
  case Opcode_##opcode:                                             \
    Execute_##opcode(cpu, castOneRegisterInstruction(instruction)); \
    break;
    ONE_REGISTER_OPCODE_DEFS
#undef TABLE_ITEM
#define TABLE_ITEM(opcode, ...)                                     \
  case Opcode_##opcode:                                             \
    Execute_##opcode(cpu, castTwoRegisterInstruction(instruction)); \
    break;
    TWO_REGISTER_OPCODE_DEFS
#undef TABLE_ITEM
#define TABLE_ITEM(opcode, ...)                                      \
  case Opcode_##opcode:                                              \
    Execute_##opcode(cpu, castRegisterPairInstruction(instruction)); \
    break;
    REGISTER_PAIR_OPCODE_DEFS
#undef TABLE_ITEM
    case Opcode_INVALID:
      Execute_INVALID(cpu, instruction);
  }
}

void Execute_INVALID(Cpu *cpu, const Instruction *instruction) {
  assert(instruction != NULL);
  assert(cpu != NULL);

  ERROR("Invalid instruction %" PRIu8 "encountered at position %" PRIu16,
        *instruction->data, cpuProgramCounter(cpu));
}
