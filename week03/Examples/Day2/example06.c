#include <stdio.h>

int gval = 20; // external
const int cval = 0xe8e8;

void action(){
    int lval = 10;
    printf("lval: %d, gval: %d, cval: %x\n",
        lval++, gval++, cval);

}

int main(){
    action();
    action();
    return 0;
}
