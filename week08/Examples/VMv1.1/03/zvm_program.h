#ifndef __ZVM_PROGRAM_H__
#define __ZVM_PROGRAM_H__

#define ZVM_PROGRAM_MAX_INSTRUCTIONS 256

typedef struct zvm_instruction_t zvm_instruction_t;
struct zvm_program_t{
    zvm_instruction_t instructions[ZVM_PROGRAM_MAX_INSTRUCTIONS];
    int32_t instructions_count;
};

#endif