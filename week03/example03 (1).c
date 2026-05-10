#include <stdio.h>

int values = 0x3b9dff;

int sum(int a, int b){
    return a + b + values;
}

/* sum.code */
int main(){
    unsigned char *sum_code = (unsigned char*)sum;
    unsigned int code_size = 0;

    //*sum_code = 0x33;

    while(1){
        printf("%p -> %02x\n", sum_code, *sum_code);
        code_size++;
        if((*sum_code) == 0xc3) break;
        sum_code++;
    }
    printf("code size: %u\n", code_size);


    return 0;
}