#ifndef __ZVM_H__
#define __ZVM_H__

#include <stdint.h>
#include "zvm_exception.h"
#include "zvm_instruction.h"
#include "zvm_program.h"

#define ZVM_RX_REGISTERS_COUNT 4

/* Program */
typedef struct zvm_instruction_operand_t zvm_instruction_operand_t;
typedef struct zvm_instruction_t zvm_instruction_t;
typedef struct zvm_program_t zvm_program_t;

typedef struct zvm_instruction_metadata_t zvm_instruction_metadata_t;
typedef struct zvm_operand_metadata_t zvm_operand_metadata_t;

typedef struct zvm_vm_t zvm_vm_t;

/* Machine */

typedef struct zvm_cpu_t zvm_cpu_t;
typedef struct zvm_memory_t zvm_memory_t;

struct zvm_cpu_t{
    uint8_t IP;
    zvm_instruction_t* IR;
    uint8_t R[ZVM_RX_REGISTERS_COUNT];
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