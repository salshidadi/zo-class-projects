#include <stdio.h>

struct student {
    int id;
    char *name;
    int age;
    char *address;
    struct student *left;
    struct student *right;
    struct student *up;
    struct student *down;
};

int main(void){
    struct student s1, s2, s3;
    // s1.next = &s2;
    // s1.previous = &s3;

    return 0;
}
