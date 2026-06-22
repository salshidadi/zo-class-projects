#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "zvm.h"

ZVM_INSTRUCTION_RRR_HANDLER_FUNCTION_BEGIN(add)
    vm->cpu.R[output] = vm->cpu.R[left] + vm->cpu.R[right];
ZVM_INSTRUCTION_RRR_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_RRR_HANDLER_FUNCTION_BEGIN(sub)
    vm->cpu.R[output] = vm->cpu.R[left] - vm->cpu.R[right];
ZVM_INSTRUCTION_RRR_HANDLER_FUNCTION_END


bool zxpt_fetch(zvm_vm_t* vm, uint8_t code)   {return false;}
bool zxpt_decode(zvm_vm_t* vm, uint8_t code)  {return false;}
bool zxpt_execute(zvm_vm_t* vm, uint8_t code) {return false;}
bool zxpt_invalid_register(zvm_vm_t* vm, uint8_t code) {return false;}


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
    vm->program.instructions_count = 3;
    ADD_EX(vm->program, 0, R0, R2, R1)
    SUB_EX(vm->program, 1, R1, R3, R0)
    ADD_EX(vm->program, 2, R0, R3, R0)
}

/* raise exception */
static bool fetch(zvm_vm_t *vm){
    /* TODO: The instruction MUST be fetched
             from code segment.
    */
   
    vm->cpu.IR = &vm->program.instructions[vm->cpu.IP];
    vm->cpu.IP++;
    return true;
}

#define zvm_is_valid_instruction(opcode) ((opcode) < ZVM_INSTRUCTION_SET_COUNT)


static bool decode(zvm_vm_t* vm){
    if(!zvm_is_valid_instruction(vm->cpu.IR->metadata->opcode)){
        vm->has_exception = true;
        vm->exception_type = ZVM_EXCEPT_TYPE_DECODE;
        return false;
    }
    return true;
}

static bool execute(zvm_vm_t* vm){
    int8_t instruction_type = vm->cpu.IR->metadata->handler.type;

    zfn_inst_handler_rrr_t rrr_action = NULL;
    bool instruction_result = false;

    switch(instruction_type){
        case ZVM_INST_HANDLER_RRR:
            rrr_action = (zfn_inst_handler_rrr_t)vm->cpu.IR->metadata->handler.action;
            instruction_result = rrr_action(vm, vm->cpu.IR->operands[0].value,
                                            vm->cpu.IR->operands[1].value,
                                            vm->cpu.IR->operands[2].value);
            break;
        
        default:
            zvm_raise(vm, EXECUTE, EXECUTE);
            return false;
    }

    return instruction_result;
}

bool except(zvm_vm_t* vm){
    if(vm->has_exception){
        int8_t code = zvm_exception_get_code(vm);

        if(zvm_exception_is_handler(code)){
            return exception_handlers[code]
                            .handler(ZVM_EXCEPTION_HANDLER_FUNCTION_ARGS);
        }else{
            fprintf(stderr, "Invalid exception handler code\n");
            return false;
        }
    }
    
    return true;
}


/* TODO:
   - Remove zvm_init_program?
*/

int main(void){
    /* declaration */
    zvm_vm_t vm;

    /* initialization */
    zvm_init(&vm);
    zvm_init_program(&vm);
    
    /* execution */
    while(zvm_has_next_instruction(&vm)){
        /* fetch */
        if(!fetch(&vm)){
            zvm_raise(&vm, FETCH, FETCH)
            goto zvm_catch;
        }
        /* decode  */
        if(!decode(&vm)){
            zvm_raise(&vm, DECODE, DECODE)
            goto zvm_catch;
        }
        /* execute */
        if(!execute(&vm)){
            goto zvm_catch;
        }
        continue;
    /* exception handling */
    zvm_catch:
        if(!except(&vm)){
            break;
        }else{
            zvm_exception_reset(&vm)
        }
    }

    if(vm.has_exception){
        fprintf(stderr, "Exception(%d): %s\n", vm.exception_code,
                    exception_handlers[vm.exception_code].message);
    }

    /* finalization */

    return 0;
}