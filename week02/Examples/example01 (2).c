#include <stdio.h>

int main(){

    unsigned short values[8] = {
        1, 2, 3, 4, 5, 6, 7, 8
    };

    unsigned short *ptr = NULL;
    for(int i = 0; i < 8; i++){
        ptr = &values[i];
        printf("%p -> %u\n", ptr, *ptr);
    }

    printf("\n-----------------------------\n");
    unsigned char x = 0xcd;
    printf("x = %u, &x = %p\n", x, &x);
    
    unsigned int ivalues[5] = {
        1, 2, 3, 4, 5
    };

    unsigned int *iptr = NULL;
    for(int i = 0; i < 5; i++){
        iptr = &ivalues[i];
        printf("%p -> %u\n", iptr, *iptr);
    }
    return 0;
}