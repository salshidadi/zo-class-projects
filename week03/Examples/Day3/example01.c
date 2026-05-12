#include <stdio.h>

// identifier :
/*
 1. external linkage.
 2. internal linkage.
 3. no linkage
*/

int value = 10;
static int v1 = 50;
static int result = 5555;

void update_value(){
    printf("value: %d\n", value);
    value = 33;
}

void action(){
    int value = 20;
    printf("result: %d\n", result);
    static int result = 5;
    printf("result: %d\n", result);


    {
        printf("value: %d\n", value);
        int value = 30;
        printf("value: %d\n", value);

        {
            extern int value;
            printf("value: %d\n", value);
            // int value = 40;
            printf("value: %d\n", value);
        }

        int v1 = 55;
        // action
        
        {
           extern int v1;
           printf("value: %d\n", v1);
        }
        
    }
}

int get_value(){
    int value = 30;
    return value;
}

int main(void){
    update_value();
    action();
    return 0;
}