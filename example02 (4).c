#include <stdio.h>

struct student {
    int id;
    char *name;
    // char name[20];
    int age;
    char *address;
};

int main(void){
    struct student s1;
    struct student s2;
    struct student *s3;
    s3 = malloc(sizeof(struct student));
    s3->name = malloc(50);
    s1.id = 20;
    s1.age = 30;

    free(s3->name);
    free(s3);
    // s1.name = malloc(100);

    s2.id = 10;
    s2.age = 25;
    // s2.name = malloc(5);

    printf("%lu\n", sizeof(struct student*));
    printf("%lu\n", sizeof(struct student));

    return 0;
}
