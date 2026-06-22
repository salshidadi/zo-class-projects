#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "zvm.h"

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(add)
    vm->cpu.R[output] = vm->cpu.R[left] + vm->cpu.R[right];
    printf("R[0]=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(sub)
    vm->cpu.R[output] = vm->cpu.R[left] - vm->cpu.R[right];
    printf("R[0]=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(ldi)
    vm->cpu.R[left] = right;
    printf("R[0]=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END


bool zxpt_fetch(zvm_vm_t* vm, uint8_t code)   {return false;}
bool zxpt_decode(zvm_vm_t* vm, uint8_t code)  {return false;}
bool zxpt_execute(zvm_vm_t* vm, uint8_t code) {return false;}
bool zxpt_invalid_register(zvm_vm_t* vm, uint8_t code) {return false;}
bool zxpt_bad_instruction(zvm_vm_t* vm, uint8_t code) {return false;}


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
    vm->program.instructions_count = 0;

    INST(vm->program, LDI, R0, 22, 17)
    LDI(vm->program,  R0, 25)
    LDI(vm->program,  R2, 15)

    ADD(vm->program,  R0, R2, R1)
    ADD(vm->program,  R1, R2, R1)
    ADD(vm->program,  R0, R2, R1)
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

#define zvm_is_valid_instruction(opcode) ((opcode) < ZVM_INSTRUCTION_HANDLERS_COUNT)


static bool decode(zvm_vm_t* vm){
    if(!zvm_is_valid_instruction(vm->cpu.IR->metadata->opcode)){
        zvm_raise(vm, DECODE, DECODE)
        return false;
    }

    /* input */
    uint8_t val0 = vm->cpu.IR->operands[0].value;
    uint8_t val1 = vm->cpu.IR->operands[1].value;
    uint8_t val2 = vm->cpu.IR->operands[2].value;

    switch(vm->cpu.IR->metadata->handler.type){
        case ZVM_INST_HANDLER_TYPE_RRR:
            if(val0 >= ZVM_RX_REGISTERS_COUNT
               || val1 >= ZVM_RX_REGISTERS_COUNT
               || val2 >= ZVM_RX_REGISTERS_COUNT){
                zvm_raise(vm, DECODE, INVALID_REGISTER)
                return false;
            }
        break;
         
        case ZVM_INST_HANDLER_TYPE_RI:
            if(val0 >= ZVM_RX_REGISTERS_COUNT
            //    || val1 >= 256
               || val2 != 0){
                zvm_raise(vm, DECODE, INVALID_REGISTER)
                return false;
            }
        break;
    }

    return true;
}

static bool execute(zvm_vm_t* vm){

    int8_t instruction_index = vm->cpu.IR->metadata->handler.type;
    if(instruction_index >= ZVM_INSTRUCTION_HANDLERS_COUNT){
        zvm_raise(vm, EXECUTE, EXECUTE);
        return false;
    }
    
    zfn_instruction_handler_t handler = (zfn_instruction_handler_t)vm->cpu.IR->metadata->handler.action;
    bool instruction_result = false;

    instruction_result = handler(vm, vm->cpu.IR->operands[0].value,
                                 vm->cpu.IR->operands[1].value,
                                 vm->cpu.IR->operands[2].value);

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