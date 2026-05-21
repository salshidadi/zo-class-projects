#include <stdio.h>


// sum: [int] -> (int, int) <- type
int sum(int a, int b){
    return a + b;
}

int sub(int a, int b){
    return a - b;
}

int mul(int a, int b){
    return a * b;
}

int main(){
    int x = 10;
    int *p = &x;

    int (*fn)(int, int);
    printf("sum: %d, sub: %d, mul: %d\n", 
        sum(1, 2), sub(5, 6), mul(9,2));
    
    int result = 0;
    
    fn = sum;
    result = fn(4, 6);
    printf("result: %d\n", result);

    fn = sub;
    result = fn(4, 6);
    printf("result: %d\n", result);

    fn = mul;
    result = fn(4, 6);
    printf("result: %d\n", result);
    
    return 0;
}
