#ifndef __ZVM_INSTRUCTION_H__
#define __ZVM_INSTRUCTION_H__
#include <stdint.h>

typedef struct zvm_vm_t zvm_vm_t;
typedef bool (*zfn_instruction_handler_t)(zvm_vm_t* vm, uint8_t, uint8_t, uint8_t);

#define ZVM_INSTRUCTION_HANDLER_FUNCTION_NAME(name)   zfnx_ ## name
#define ZVM_INSTRUCTION_HANDLER_FUNCTION_PARAM \
    zvm_vm_t* vm, uint8_t left, uint8_t right, uint8_t output

#define ZVM_INSTRUCTION_HANDLER_FUNCTION_ARGS \
    vm, left, right, output

#define ZVM_INSTRUCTION_HANDLER_FUNCTION(name)  \
    bool ZVM_INSTRUCTION_HANDLER_FUNCTION_NAME(name) (ZVM_INSTRUCTION_HANDLER_FUNCTION_PARAM)


#define ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(name) \
    ZVM_INSTRUCTION_HANDLER_FUNCTION(name) {

#define ZVM_INSTRUCTION_HANDLER_FUNCTION_END    \
        return true;                            \
    }

#define ZVM_INSTRUCTION_HANDLER_CALL(name) zfnx_ ## name(ZVM_INSTRUCTION_HANDLER_FUNCTION_ARGS)

#define ZVM_OPERAND_TYPE_REG 0
#define ZVM_OPERAND_TYPE_MEM 1
#define ZVM_OPERAND_TYPE_IMM 2

typedef struct zvm_operand_metadata_t {
    uint16_t type:2; /* ZVM_OPERAND_XXX */
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


/* instructions opcodes */
#define ZVM_OPCODE_ADD        0
#define ZVM_OPCODE_SUB        1
#define ZVM_OPCODE_LDI        2          

/* instructions handlers */
ZVM_INSTRUCTION_HANDLER_FUNCTION(add);
ZVM_INSTRUCTION_HANDLER_FUNCTION(sub);
ZVM_INSTRUCTION_HANDLER_FUNCTION(ldi);

#define ZVM_INST_HANDLER_TYPE_RRR  0
#define ZVM_INST_HANDLER_TYPE_RI   1


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


#define ZVM_INSTRUCTION_HANDLERS_COUNT (sizeof(instruction_handlers) / sizeof(zvm_instruction_metadata_t))

// ZVM_INSTRUCTION_HANDLER_ENTRY(ADD, add, 3, RRR)
#define ZVM_INSTRUCTION_HANDLER_ENTRY_BEGIN(name, argc) \
    {#name, ZVM_OPCODE_ ## name, ZVM_INST_ ## argc ## _OP, {

#define ZVM_INSTRUCTION_HANDLER_ENTRY_END(fn, type) \
    },{ZVM_INST_HANDLER_TYPE_ ## type, ZVM_INSTRUCTION_HANDLER_FUNCTION_NAME(fn)}},

#define ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(type, isptr) \
    {ZVM_OPERAND_TYPE_ ## type, isptr},

#define ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(name, fn) \
     ZVM_INSTRUCTION_HANDLER_ENTRY_BEGIN(name, 3) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(REG, 0) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(REG, 0) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(REG, 0) \
    ZVM_INSTRUCTION_HANDLER_ENTRY_END(fn, RRR)


#define ZVM_INSTRUCTION_HANDLER_ENTRY_RI(name, fn) \
     ZVM_INSTRUCTION_HANDLER_ENTRY_BEGIN(name, 2) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(REG, 0) \
        ZVM_INSTRUCTION_HANDLER_OPERAND_ENTRY(IMM, 0) \
    ZVM_INSTRUCTION_HANDLER_ENTRY_END(fn, RI)

const zvm_instruction_metadata_t instruction_handlers [] = {
    ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(ADD, add)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RRR(SUB, sub)
    ZVM_INSTRUCTION_HANDLER_ENTRY_RI(LDI, ldi)
};

struct zvm_instruction_t {
    zvm_instruction_metadata_t *metadata;
    zvm_instruction_operand_t operands[ZVM_INST_MAX_OPERANDS];
};



#define zvm_set_instruction(p, i, opcode, v1, v2, v3)\
    (p).instructions[(i)].metadata = (zvm_instruction_metadata_t*)&instruction_handlers[ZVM_OPCODE_ ## opcode];\
    (p).instructions[(i)].operands[0].metadata = (zvm_operand_metadata_t*)&instruction_handlers[ZVM_OPCODE_ ## opcode].operands[0];\
    (p).instructions[(i)].operands[1].metadata = (zvm_operand_metadata_t*)&instruction_handlers[ZVM_OPCODE_ ## opcode].operands[1];\
    (p).instructions[(i)].operands[2].metadata = (zvm_operand_metadata_t*)&instruction_handlers[ZVM_OPCODE_ ## opcode].operands[2];\
    (p).instructions[(i)].operands[0].value = (v1); \
    (p).instructions[(i)].operands[1].value = (v2); \
    (p).instructions[(i)].operands[2].value = (v3);

#define R0  0
#define R1  1
#define R2  2
#define R3  3

#define INST(p, opcode, v1, v2, v3) \
    zvm_set_instruction(p, ((p).instructions_count), opcode, v1, v2, v3) \
    (p).instructions_count++;


#define ADD(p, v1, v2, v3) INST(p, ADD, v1, v2, v3)
#define SUB(p, v1, v2, v3) INST(p, SUB, v1, v2, v3)
#define LDI(p, v1, v2) INST(p, LDI, v1, v2, 0)

#endif