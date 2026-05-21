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

// typedef struct student student;
// typedef struct student {
//     int id;
//     int age;
//     char name[20];
// }student;

// typedef unsigned char uchar;
// typedef unsigned char* puchar;
// typedef unsigned int student_id_t;

typedef int (*fun_t)(int, int);

int main(){
    // student_id_t id = 10;
    // uchar c;
    // puchar p;
    // int (*fn)(int, int);
    fun_t fn;

    unsigned char* funcs[3] = {
        (unsigned char*)sum,
        (unsigned char*)sub,
        (unsigned char*)mul
    };

    for(int i = 0; i < 3; i++){
        fn = (fun_t)funcs[i];
        printf("fn[%d] = %d\n", i, fn(10, 5));
    }

    return 0;
}