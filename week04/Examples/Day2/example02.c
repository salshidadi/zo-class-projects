#include <stdio.h>

struct data{
    unsigned short v1:7;
    unsigned short:0;
    unsigned short:1;
    unsigned short:0;
    unsigned short:2;
    unsigned short:0;

    unsigned short v2:2;
    unsigned short:1;
    unsigned short:0;
    unsigned short:2;
    unsigned short:0;
    unsigned short:0;
    unsigned short v3: 3;
};

struct info{
    unsigned int v1:1;
    unsigned short v3:16;
    unsigned char v4:2;
    unsigned int v2:4;
};

struct player{
    unsigned char id:3;
    unsigned char position:2;
    unsigned char asasi:1;
    unsigned char f:2;
};

typedef struct byte_t{
    unsigned char b0:1;
    unsigned char b1:1;
    unsigned char b2:1;
    unsigned char b3:1;
    unsigned char b4:1;
    unsigned char b5:1;
    unsigned char b6:1;
    unsigned char b7:1;
}byte_t;

typedef struct nybble_t{
    unsigned char low:4;
    unsigned char high:4;
}nybble_t;

int main(void){
    unsigned char value = 0x3e; // 0011 1110
    byte_t *bval = (byte_t*)&value;
    nybble_t *nval = (nybble_t*)&value;
    printf("value: %x, nval.low: %x, nval.high: %x\n", 
        value, nval->low, nval->high);
    
    printf("%d%d%d%d %d%d%d%d\n", 
        bval->b7, bval->b6, bval->b5, bval->b4, bval->b3,
        bval->b2, bval->b1, bval->b0);

    printf("%lu\n", sizeof(struct info));
    return 0;
}
