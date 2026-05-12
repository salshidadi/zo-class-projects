#include <stdio.h>
#include "code.h"

struct student {
    int id;
    char name;
    int age;
};

int main(){
    int result = sub(1, 2);
    int val = 0xe8e8e8e8;
    float f = val;
    struct student s1;
    s1.id = 0xf3f3f3f3;
    s1.age = 0x5d5d5d5d;
    s1.name = 'C';
    printf("%lu\n", sizeof(struct student));

    return 0;
}
