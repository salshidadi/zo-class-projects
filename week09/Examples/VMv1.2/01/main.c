#include "zvm.h"

int main(void){
    zvm_vm_t vm;
    uint8_t program_size = 0;
    uint8_t program [] = {};

    return zvm_main(&vm, program, program_size);
}
