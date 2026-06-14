#include <stdio.h>
#include <stdbool.h>
#include "zvm.h"


void zfnx_add(zvm_vm_t* vm, uint8_t left, uint8_t right, uint8_t output){
    printf("zfnx_add\n");
}
void zfnx_sub(zvm_vm_t* vm, uint8_t left, uint8_t right, uint8_t output){
    printf("zfnx_sub\n");
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

void zvm_init_program(zvm_program_t* program){
    ADD_EX(*program, 0, R0, R2, R1)
    SUB_EX(*program, 1, R1, R3, R0)
    ADD_EX(*program, 2, R0, R3, R0)
}

int main(void){
    zvm_vm_t vm;
    zvm_program_t program;

    zvm_init(&vm);
    zvm_init_program(&program);
    
    while(true){
        /* fetch   */
        /* decode  */
        /* execute */

    }

    return 0;
}