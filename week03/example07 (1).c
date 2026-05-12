#include <stdio.h>
// #include "code.h"

// #include "test.h"

int value = 20;

// extern int sum(int a, int b);
// int sub(int a, int b);

extern int sub(int a, int b);

int main(){
    int result = sub(50, 60);
    printf("result: %d, value: %d\n", result, value);
    return 0;
}
