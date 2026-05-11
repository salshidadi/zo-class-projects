#include <stdio.h>

struct info{
    unsigned char v1;
    unsigned int v2;
    unsigned char v3;
    unsigned short v4;
};

int main(){
    struct info x, y; // this is info type
    struct info informationTech[1000];
    printf("&x = %p, &y= %p, %lu, %lu\n",
       &x, &y, sizeof(x), sizeof(y));
    
    printf("x.v1= %p\nx.v2= %p\nx.v3= %p\nx.v4 = %p\n",
      &x.v1, &x.v2, &x.v3, &x.v4);

    //   'X', 'Y', 'Z'

    unsigned char *ptr = (unsigned char*)&x.v1;
    *(ptr+1) = 'X';
    *(ptr+2) = 'Y';
    *(ptr+3) = 'Z';
    
    ptr = (unsigned char*)&x.v3;
    *(ptr+1) = 'R';

    ptr = (unsigned char*)&x;

    for(int i = 0; i < sizeof(x); i++){
        printf("%p -> %c\n", ptr+i, *(ptr+i));
    }
    
    return 0;
}