#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "zvm.h"


void zfnx_add(zvm_vm_t* vm, uint8_t left, uint8_t right, uint8_t output){
    printf("zfnx_add\n");
}
void zfnx_sub(zvm_vm_t* vm, uint8_t left, uint8_t right, uint8_t output){
    printf("zfnx_sub\n");
}

bool zxpt_divzero(zvm_vm_t* vm, uint8_t code){
    return false;
}


void zvm_init(zvm_vm_t *vm){
    vm->cpu.IP = 0;
    vm->cpu.IR = NULL;

    vm->cpu.R[0] = 0;
    vm->cpu.R[1] = 0;
    vm->cpu.R[2] = 0;
    vm->cpu.R[3] = 0;

    vm->cpu.OUTPUT = 0;
    vm->cpu.FLAGS  = 0;

    vm->cpu.DR = 0;
    vm->cpu.CR = 0;
    vm->cpu.SR = 0;
    vm->cpu.SP = 0;
}

void zvm_init_program(zvm_vm_t* vm){
    ADD_EX(vm->program, 0, R0, R2, R1)
    SUB_EX(vm->program, 1, R1, R3, R0)
    ADD_EX(vm->program, 2, R0, R3, R0)
}

static bool fetch(zvm_vm_t *vm){
    /* TODO: The instruction MUST be fetched
             from code segment.
    */
    if(!zvm_has_next_instruction(vm)){
        exit(0);
    }
    
    vm->cpu.IR = &vm->program.instructions[vm->cpu.IP];
    vm->cpu.IP++;
    return true;
}

#define zvm_is_valid_instruction(opcode) (opcode) < ZVM_INSTRUCTION_SET_COUNT


static bool decode(zvm_vm_t* vm){
    if(!zvm_is_valid_instruction(vm->cpu.IR->metadata->opcode)){
        vm->has_exception = true;
        vm->exception_type = ZVM_EXCEPT_DECODE;
        return false;
    }
    return true;
}

static bool execute(zvm_vm_t* vm){
    int8_t instruction_type = vm->cpu.IR->metadata->handler.type;

    zfn_inst_handler_rrr_t rrr_action = NULL;

    switch(instruction_type){
        case ZVM_INST_HANDLER_RRR:
            rrr_action = (zfn_inst_handler_rrr_t)vm->cpu.IR->metadata->handler.action;
            rrr_action(vm, vm->cpu.IR->operands[0].value,
                           vm->cpu.IR->operands[1].value,
                           vm->cpu.IR->operands[2].value);
            break;
        
        default: 
            vm->has_exception = true;
            vm->exception_type = ZVM_EXCEPT_EXECUTE;
            return false;
    }

    return true;
}

void ehandler(zvm_vm_t* vm){
    if(vm->has_exception){
        switch(vm->exception_type){
            case ZVM_EXCEPT_FETCH:
                fprintf(stderr, "ZVM_EXCEPT_FETCH: Bad instruction.\n");
            break;
            case ZVM_EXCEPT_DECODE:
                fprintf(stderr, "ZVM_EXCEPT_DECODE: Invalid instruction opcode.\n");
            break;
            case ZVM_EXCEPT_EXECUTE:
                if(zvm_is_valid_exception_handler(vm->exception_code)){
                    bool result = exception_handlers[vm->exception_code].handler(vm, vm->exception_code);
                    if(!result) exit(1);
                }
                fprintf(stderr, "ZVM_EXCEPT_EXECUTE: Exception.\n");
            break;
        }
    }
}


int main(void){
    zvm_vm_t vm;

    zvm_init(&vm);
    zvm_init_program(&vm);
    
    while(true){
        /* fetch */
        if(!fetch(&vm)){
            fprintf(stderr, "Bad instruction!\n");
            goto except;
            // exit(1);
        }

        /* decode  */
        if(!decode(&vm)){
            fprintf(stderr, "Invalid opcode instruction\n");
            goto except;
            // exit(1);
        }

        /* execute */
        if(!execute(&vm)){
            goto except;
        }

        continue;
    
    /* exception handling */
    except:
        ehandler(&vm);
    }
    
    return 0;
}