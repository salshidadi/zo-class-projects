#include <stdio.h>

void action(){
    int val = 10;
    const int cval = 50;
    // cval++;
    int *ptr = (int*)&cval;
    (*ptr)++;
    printf("val = %d, cval = %d\n",
        val, cval);
    
    val++;
    // cval++;
}

int main(){
    action();
    return 0;
}
