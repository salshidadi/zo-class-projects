#include <stdio.h>

int main(){
    unsigned char values[8] = {
                0x32,
                0xee,
                0xf8,
                0x91,
    /* -> */    0x6a,
                0xdc,
                0xb4,
                0xab
    };

    unsigned char *ptr = values + 4;

    printf("left: %x, right: %x\n", 
      *(ptr-2), *(ptr+1));
    return 0;
}