#include <stdio.h>
// #include "code.h"
extern int value;
//extern static 
//  = 10
extern int sub(int a, int b);
// external linkage 
// internal linkage
// no linkage

int main(){
    int result = sub(50, 60);
    printf("result: %d\n", result);
    return 0;
}
