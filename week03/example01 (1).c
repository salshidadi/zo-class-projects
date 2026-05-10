#include <stdio.h>

int main(){
    unsigned int values[5] = {
        10, 20, 30, 40, 50
    };
    // address = base + (offset * size)
    // values[2]
    unsigned char *ptr =(unsigned char*)values;
    //ptr = ptr + (2 * 4)
    return 0;
}