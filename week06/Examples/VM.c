/*
CPU
Memory
IO
Bus
*/

// Note file.
#include <stdint.h>
#include <stdbool.h>

typedef struct VM VM;
typedef struct CPU CPU;
typedef struct Memory Memory;
typedef struct Program Program;
typedef struct Instruction Instruction;

#define DEFAULT_MEMORY_SIZE   4096

struct Memory{
    uint8_t memory[DEFAULT_MEMORY_SIZE];
    int allocated;
};

struct CPU{
    uint16_t ip; // note
    uint16_t ir;

    uint8_t br0;
    uint8_t br1;
    uint8_t br2;
    uint8_t br3;

    uint16_t r0;
    uint16_t r1;
    uint16_t r2;
    uint16_t r3;
    uint16_t r4;
    uint16_t r5;
    uint16_t r6;
    uint16_t r7;

    uint32_t er0;
    uint32_t er1;
    uint32_t er2;
    uint32_t er3;

    uint64_t xr;
    uint64_t yr;
};

struct Program{
    int32_t offset;
    int32_t data_size;
    int32_t code_size;

    CPU cpu;
    int32_t instructions_count;
    Instruction *instructions;
};

// enum InstructionRegisterType {
//     _8BIT,
//     _16BIT,
//     _32BIT,
//     _64BIT,
// };

#define INST_REG_8BIT  0
#define INST_REG_16BIT 1
#define INST_REG_32BIT 2
#define INST_REG_64BIT 3

// bool opcode(VM *vm, InstructionOpcode op, uint16_t register_type, uint64_t in0, uint64_t in1,
// uint64_t out);

typedef bool (*opcode_t)(VM *vm, InstructionOpcode op, 
    uint16_t register_type, uint64_t in0, uint64_t in1, uint64_t *out);

struct Instruction{
    uint16_t opcode:5;
    uint16_t register_type:2;
    uint16_t in_reg_0:3;
    uint16_t in_reg_1:3;
    uint16_t out_reg:3;
};

typedef enum InstructionOpcode{
    OPCODE_AND,
    OPCODE_OR,
    OPCODE_NOT,
    OPCODE_XOR,
    OPCODE_SHL,
    OPCODE_SHR
}InstructionOpcode;

const OpcodeAction instructions[32] = {
    {OPCODE_AND, opcode_and},
    {OPCODE_OR, opcode_or},
    {OPCODE_NOT, opcode_not},

};

struct VM{
    CPU cpu;
    Memory memory;
};

typedef struct OpcodeAction OpcodeAction;

struct OpcodeAction{
    InstructionOpcode opcode;
    opcode_t function;
};

#include <stdio.h>

bool opcode_and(VM *vm, InstructionOpcode op, 
    uint16_t register_type, uint64_t in0, uint64_t in1, uint64_t *out){
        if(out != NULL){
            *out = in0 & in1;
            return true;
        }
    return false;
}

bool opcode_or(VM *vm, InstructionOpcode op, 
    uint16_t register_type, uint64_t in0, uint64_t in1, uint64_t *out){
        if(out != NULL){
            *out = in0 | in1;
            return true;
        }
    return false;
}

bool opcode_not(VM *vm, InstructionOpcode op, 
    uint16_t register_type, uint64_t in0, uint64_t in1, uint64_t *out){
        if(out != NULL){
            *out = ~in0;
            return true;
        }
    return false;
}

bool execute(VM *vm, Program *program){
    int base = program->offset + program->data_size;
    // for(int i = base; i < (base + program->code_size /* - 1 */, i++)){

    for(int i = 0; i < program->instructions_count; i++){
        instructions[program->instructions[i].opcode].function(vm, OPCODE_AND, program->instructions[i].register_type,
        //         program->instructions[i].in_reg_0, program->instructions[i].in_reg_1,
        //         &program->instructions[i].out_reg);
        // switch(program->instructions[i].opcode){
        //     case OPCODE_AND:
        //         instructions[OPCODE_AND].function(vm, OPCODE_AND, program->instructions[i].register_type,
        //         program->instructions[i].in_reg_0, program->instructions[i].in_reg_1,
        //         &program->instructions[i].out_reg);
        // }
    }
}

int main(void){

    VM vm;
    Program program;
    if(execute(&vm, &program)){
        printf("executed!\n");
    }
    return 0;
}
