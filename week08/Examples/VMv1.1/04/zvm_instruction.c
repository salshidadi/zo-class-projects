#include <stdio.h>
#include "zvm_instruction.h"
#include "zvm.h"

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(add)
    vm->cpu.R[output] = vm->cpu.R[left] + vm->cpu.R[right];
    printf("R=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(sub)
    vm->cpu.R[output] = vm->cpu.R[left] - vm->cpu.R[right];
    printf("R=%u\n", vm->cpu.R[output]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(ldi)
    vm->cpu.R[left] = right;
    printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(str)
    /* STR reg, mem */
    vm->program.data[right] = vm->cpu.R[left];
    printf("MEM=%u\n", vm->program.data[right]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(ldm)
    /* LDM reg, mem */
    vm->cpu.R[left] = vm->program.data[right];
    printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(lda)
    uint8_t address = vm->cpu.R[left];
    if(!zvm_is_address(address)){
        zvm_raise(vm, EXECUTE, BAD_MEMORY_ADDRESS)
        return false;
    }
    vm->cpu.R[right] = vm->program.data[address];
    printf("R=%u\n", vm->cpu.R[right]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(sta)
    /* STA reg, reg */
    uint8_t address = vm->cpu.R[left];
    if(!zvm_is_address(address)){
        zvm_raise(vm, EXECUTE, BAD_MEMORY_ADDRESS)
        return false;
    }
    vm->program.data[address] = vm->cpu.R[right];
    printf("address=%u\n", vm->program.data[address]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(push)
    uint8_t value;
    if(vm->cpu.SP >= ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE){
        zvm_raise(vm, EXECUTE, STACK_OVERFLOW)
        return false;
    }

    vm->cpu.SP++;
    value = vm->cpu.R[left];
    vm->program.stack[(ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) - vm->cpu.SP] = value;
    printf("stack=%u\n", value);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(pop)
    uint8_t value;
    if(vm->cpu.SP < 0){
        zvm_raise(vm, EXECUTE, STACK_UNDERFLOW)
        return false;
    }

    value = vm->program.stack[(ZVM_PROGRAM_DEFAULT_STACK_SEGMENT_SIZE - 1) - vm->cpu.SP];
    vm->cpu.SP--;
    
    vm->cpu.R[left] = value;
    printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(inc)
    /* INC reg*/
    vm->cpu.R[left]++;
    printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END

ZVM_INSTRUCTION_HANDLER_FUNCTION_BEGIN(dec)
    /* DEC reg*/
    vm->cpu.R[left]--;
    printf("R=%u\n", vm->cpu.R[left]);
ZVM_INSTRUCTION_HANDLER_FUNCTION_END