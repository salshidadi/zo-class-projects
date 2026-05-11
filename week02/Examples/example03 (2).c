#include <stdio.h>

struct data{
    unsigned short v1;
    unsigned short v2;
    unsigned int v3;
};

struct info{
    // struct data d;
    int i;
    char c;
};

int main(){
    struct info xyz[2];
    // struct data x;
    struct info y;
    struct info *yptr = &y;
    // yptr->d.v1 = 0xaaaa;
    // yptr->d.v2 = 0xbbbb;
    // yptr->d.v3 = 0xacacacac;
    yptr->i = 0x8e8e8e8e;
    yptr->c = 0xff;
    // struct data *xptr = &x;
    // xptr = (struct data*)&y;

    unsigned char *ptr = (unsigned char*)&y;

    for(int i = 0; i < sizeof(y); i++){
        printf("%p -> %x\n", ptr+i, *(i+ptr));
    }
    return 0;
}