#include <stdio.h>

void action(){
    int ayshi = 123;
    int val = 0x7318ffee;
    char message[] = "ABCDEFGHIJ";
    static const int cval = 0xe8e8e8e8;
    printf("val = %d, cval = %d\n",
        val, cval);
    
    val++;
    static int ayshi;
    // mov eax, 0xe8e8e8e8
    // mov rax, 0x4142434445464748
}

int main(){
    action();
    return 0;
}
