#ifndef __ZVM_INSTRUCTION_H__
#define __ZVM_INSTRUCTION_H__
#include <stdint.h>

typedef struct zvm_vm_t zvm_vm_t;
typedef bool (*zfn_inst_handler_rrr_t)(zvm_vm_t* vm, uint8_t, uint8_t, uint8_t);

#define ZVM_INSTRUCTION_HANDLER_FUNCTION_NAME(name)   zfnx_ ## name
#define ZVM_INSTRUCTION_HANDLER_FUNCTION_PARAM \
    zvm_vm_t* vm, uint8_t left, uint8_t right, uint8_t output

#define ZVM_INSTRUCTION_HANDLER_FUNCTION_ARGS \
    vm, left, right, output

#define ZVM_INSTRUCTION_RRR_HANDLER_FUNCTION(name)  \
    bool ZVM_INSTRUCTION_HANDLER_FUNCTION_NAME(name) (ZVM_INSTRUCTION_HANDLER_FUNCTION_PARAM)


#define ZVM_INSTRUCTION_RRR_HANDLER_FUNCTION_BEGIN(name) \
    ZVM_INSTRUCTION_RRR_HANDLER_FUNCTION(name) {         \
        if(left >= 4 || right >= 4 || output >= 4){      \
            zvm_raise(vm, EXECUTE, INVALID_REGISTER)     \
            return false;                                \
        }

#define ZVM_INSTRUCTION_RRR_HANDLER_FUNCTION_END    \
        printf("output = %u\n", vm->cpu.R[output]); \
        return true;                                \
    }


#define ZVM_INSTRUCTION_HANDLER_CALL(name) zfnx_ ## name(ZVM_INSTRUCTION_HANDLER_FUNCTION_ARGS)


ZVM_INSTRUCTION_RRR_HANDLER_FUNCTION(add);
ZVM_INSTRUCTION_RRR_HANDLER_FUNCTION(sub);


#define ZVM_OPERAND_REG 0
#define ZVM_OPERAND_MEM 1
#define ZVM_OPERAND_IMM 2

#define ZVM_OPERAND_IN  0
#define ZVM_OPERAND_OUT 1
#define ZVM_OPERAND_INOUT 2

typedef struct zvm_operand_metadata_t {
    uint16_t type:2; /* ZVM_OPERAND_XXX */
    uint16_t inout:2; /* ZVM_OPERAND_XX*/
    uint16_t is_pointer:1;
}zvm_operand_metadata_t;

typedef struct zvm_instruction_operand_t{
    zvm_operand_metadata_t* metadata;
    uint8_t value;
}zvm_instruction_operand_t;

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


typedef struct zvm_instruction_metadata_t{
    char *mnemonic;
    uint8_t opcode;
    uint8_t operands_count;
    zvm_operand_metadata_t operands[ZVM_INST_MAX_OPERANDS];
    zvm_instruction_handler_t handler;
}zvm_instruction_metadata_t;


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


#endif