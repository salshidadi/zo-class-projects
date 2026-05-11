#include <stdio.h>


struct info{
    long l;
    int i;
    char c;
    int x;
};

int main(){
    printf("struct info size = %lu\n", 
       sizeof(struct info));
    return 0;
}