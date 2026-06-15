#ifndef __ZVM_H__
#define __ZVM_H__

#include <stdint.h>

#define zvm_set_instruction(p, i, opcode, v1, v2, v3)\
    (p).instructions[(i)].metadata = &instruction_set[ZVM_OPCODE_ ## opcode];\
    (p).instructions[(i)].operands[0].metadata = &instruction_set[ZVM_OPCODE_ ## opcode].operands[0];\
    (p).instructions[(i)].operands[1].metadata = &instruction_set[ZVM_OPCODE_ ## opcode].operands[1];\
    (p).instructions[(i)].operands[2].metadata = &instruction_set[ZVM_OPCODE_ ## opcode].operands[2];\
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

#define ZVM_OPERAND_REG 0
#define ZVM_OPERAND_MEM 1
#define ZVM_OPERAND_IMM 2

#define ZVM_OPERAND_IN  0
#define ZVM_OPERAND_OUT 1
#define ZVM_OPERAND_INOUT 2

struct zvm_operand_metadata_t {
    uint16_t type:2; /* ZVM_OPERAND_XXX */
    uint16_t inout:2; /* ZVM_OPERAND_XX*/
    uint16_t is_pointer:1;
};

struct zvm_instruction_operand_t{
    zvm_operand_metadata_t* metadata;
    uint8_t value;
};

#define ZVM_INST_0_OP  0
#define ZVM_INST_1_OP  1
#define ZVM_INST_2_OP  2
#define ZVM_INST_3_OP  3

#define ZVM_INST_MAX_OPERANDS  3


#define ZVM_OPCODE_ADD        0
#define ZVM_OPCODE_SUB        1


#define ZVM_INST_HANDLER_RRR  0

typedef struct zvm_instruction_handler_t zvm_instruction_handler_t;

struct zvm_instruction_handler_t{
    int8_t type;
    void *action;
};

typedef void (*zfn_inst_handler_rrr_t)(zvm_vm_t* vm, uint8_t, uint8_t, uint8_t);

void zfnx_add(zvm_vm_t*, uint8_t, uint8_t, uint8_t);
void zfnx_sub(zvm_vm_t*, uint8_t, uint8_t, uint8_t);


struct zvm_instruction_metadata_t{
    char *mnemonic;
    uint8_t opcode;
    uint8_t operands_count;
    zvm_operand_metadata_t operands[ZVM_INST_MAX_OPERANDS];
    zvm_instruction_handler_t handler;
};

// #define ZVM_INST_MD_ENTRY(m, opcode, count, operands, handler) 
/*
ADD R1, R2, R0
LDI R2, 7
LDI R0, 20
LDR R1, 33
SYS 5
*/

#define ZVM_INSTRUCTION_SET_COUNT (sizeof(instruction_set) / sizeof(zvm_instruction_metadata_t))

const zvm_instruction_metadata_t instruction_set [] = {
    {"ADD",
     ZVM_OPCODE_ADD,
     ZVM_INST_3_OP, 
     {{ZVM_OPERAND_REG, ZVM_OPERAND_IN, 0}, {ZVM_OPERAND_REG, ZVM_OPERAND_IN, 0}, {ZVM_OPERAND_REG, ZVM_OPERAND_OUT, 0}},
     {.type = ZVM_INST_HANDLER_RRR, .action = zfnx_add}},

     {"SUB",
     ZVM_OPCODE_SUB,
     ZVM_INST_3_OP, 
     {{ZVM_OPERAND_REG, ZVM_OPERAND_IN, 0}, {ZVM_OPERAND_REG, ZVM_OPERAND_IN, 0}, {ZVM_OPERAND_REG, ZVM_OPERAND_OUT, 0}},
     {.type = ZVM_INST_HANDLER_RRR, .action = zfnx_sub}},
};

struct zvm_instruction_t {
    zvm_instruction_metadata_t *metadata;
    zvm_instruction_operand_t operands[ZVM_INST_MAX_OPERANDS];
};

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

#define ZVM_EXCEPT_FETCH   0
#define ZVM_EXCEPT_DECODE  1
#define ZVM_EXCEPT_EXECUTE 2

#define ZVM_EXCEPT_DIVZERO  0

typedef struct zvm_exception_entry_t zvm_exception_entry_t;
typedef bool (*exception_handler_t)(zvm_vm_t* vm, uint8_t code, void *arg);

struct zvm_exception_entry_t{
    uint8_t type;
    uint8_t code;
    exception_handler_t handler;
};

#define ZVM_EXCEPTION_HANDLERS_COUNT (sizeof(exception_handlers)) / sizeof(zvm_exception_entry_t)
#define zvm_is_valid_exception_handler(code)  (code) < ZVM_EXCEPTION_HANDLERS_COUNT

bool zxpt_divzero(zvm_vm_t* vm, uint8_t code, void *arg);

const zvm_exception_entry_t exception_handlers [] = {
    {ZVM_EXCEPT_EXECUTE, ZVM_EXCEPT_DIVZERO, zxpt_divzero},
};

struct zvm_vm_t{
    // FILE* log;
    bool has_exception;
    uint8_t exception_type;
    uint8_t exception_code;


    zvm_cpu_t cpu;
    zvm_program_t program;
    // zvm_memory_t memory;
};

#define zvm_has_next_instruction(vm) \
  (vm)->cpu.IP < (vm)->program.instructions_count

#endif