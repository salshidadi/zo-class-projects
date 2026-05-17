#include <stdio.h>

int main(void){
    int oneval = 500;
    int values[5] = {
        10,
        20,
        30,
        40,
        50
    };

    int *ptr = &oneval;
    int* *pptr = &ptr;
    int** *ppptr = &pptr;

    printf("oneval: %d, ptr = %p, pptr = %p, ppptr = %p\n", oneval, ptr,
        pptr, ppptr);
    printf("oneval: %d, *ptr = %d, **pptr = %d, ***ppptr = %d\n",
        oneval, *ptr, **pptr, ***ppptr);
    
    // ptr = values;
    // pptr = &values;
    // ppptr = &pptr;

    // ptr++;
    // (*((*pptr)+3));
    // *((**ppptr)+2);

    printf("%lu %lu %lu %lu\n",
        sizeof(int*), sizeof(char*), sizeof(long*), sizeof(float*));

    return 0;
}
