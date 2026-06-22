#ifndef __ZVM_H__
#define __ZVM_H__

#include <stdint.h>
#include "zvm_exception.h"
#include "zvm_instruction.h"

#define zvm_set_instruction(p, i, opcode, v1, v2, v3)\
    (p).instructions[(i)].metadata = (zvm_instruction_metadata_t*)&instruction_set[ZVM_OPCODE_ ## opcode];\
    (p).instructions[(i)].operands[0].metadata = (zvm_operand_metadata_t*)&instruction_set[ZVM_OPCODE_ ## opcode].operands[0];\
    (p).instructions[(i)].operands[1].metadata = (zvm_operand_metadata_t*)&instruction_set[ZVM_OPCODE_ ## opcode].operands[1];\
    (p).instructions[(i)].operands[2].metadata = (zvm_operand_metadata_t*)&instruction_set[ZVM_OPCODE_ ## opcode].operands[2];\
    (p).instructions[(i)].operands[0].value = (v1); \
    (p).instructions[(i)].operands[1].value = (v2); \
    (p).instructions[(i)].operands[2].value = (v3);

#define R0  0
#define R1  1
#define R2  2
#define R3  3

#define INST_EX(p, i, opcode, v1, v2, v3) zvm_set_instruction(p, i, opcode, v1, v2, v3)
#define INST(i, opcode, v1, v2, v3)  INST_EX(program, i, opcode, v1, v2, v3)

#define ADD_EX(p, i, v1, v2, v3) INST_EX(p, i, ADD, v1, v2, v3)
#define ADD(i, v1, v2, v3)  ADD_EX(program, i, v1, v2, v3)

#define SUB_EX(p, i, v1, v2, v3) INST_EX(p, i, SUB, v1, v2, v3)
#define SUB(i, v1, v2, v3)  SUB_EX(program, i, v1, v2, v3)

/* Program */
typedef struct zvm_instruction_operand_t zvm_instruction_operand_t;
typedef struct zvm_instruction_t zvm_instruction_t;
typedef struct zvm_program_t zvm_program_t;

typedef struct zvm_instruction_metadata_t zvm_instruction_metadata_t;
typedef struct zvm_operand_metadata_t zvm_operand_metadata_t;

typedef struct zvm_vm_t zvm_vm_t;

#define ZVM_PROGRAM_MAX_INSTRUCTIONS 256

struct zvm_program_t{
    zvm_instruction_t instructions[ZVM_PROGRAM_MAX_INSTRUCTIONS];
    int32_t instructions_count;
};

/* Machine */

typedef struct zvm_cpu_t zvm_cpu_t;
typedef struct zvm_memory_t zvm_memory_t;

struct zvm_cpu_t{
    uint8_t IP;
    zvm_instruction_t* IR;
    uint8_t R[4];
    uint32_t OUTPUT;
    uint8_t FLAGS;

    uint8_t DR;
    uint8_t CR;
    uint8_t SR;
    uint8_t SP;
};

#define ZVM_MEMORY_MAX_SIZE 256

struct zvm_memory_t{
    uint8_t block[ZVM_MEMORY_MAX_SIZE];
};

struct zvm_vm_t{
    // FILE* log;
    bool has_exception;
    int8_t exception_type;
    int8_t exception_code;


    zvm_cpu_t cpu;
    zvm_program_t program;
    // zvm_memory_t memory;
};

#define zvm_has_next_instruction(vm) \
  ((vm)->cpu.IP < (vm)->program.instructions_count)

#endif