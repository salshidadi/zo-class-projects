#include <stdio.h>

int main(){
    unsigned char values[8] = {
        0x32, 0xee, 0xf8, 0x91,
        0x6a, 0xdc, 0xb4, 0xab
    };

    int block_size = sizeof(values);
    int array_size = sizeof(values) / sizeof(unsigned char);

    printf("block address: %p\n", values);

    unsigned char *ptr = values;

    ptr += 3;
    printf("ptr.address = %p, ptr.value = %x\n", 
        ptr, *ptr);
    
    for(int i = 0; i < array_size; i++){
        printf("%p -> values[%d] = %x\n",
            &values[i], i, values[i]);
    }

    printf("...........................\n");
    
    ptr = values;
    for(int i = 0; i < array_size; i++){
        printf("%p -> values[%d] = %x\n",
            ptr+i, i, *(ptr+i));
    }

    // int size = sizeof(values);


    return 0;
}