#include <stdio.h>

void action(){
    int val = 10;
    static int sval = 1;
    printf("val = %d, sval = %d\n",
        val, sval);
    
    val++;
    sval++;
}

int main(){
    action();
    action();
    action();
    action();
    action();
    return 0;
}
