#include <stdio.h>
#include <stdlib.h>

struct student{
    int id;
    char name;
    int age;
};

int main(){
    
    void *ptr = malloc(sizeof(struct student));
    struct student *sptr = (struct student*)ptr;
    
    sptr->name = 'C';
    sptr->id = 0x44eeff11;
    sptr->age = 0x663388dd;

    FILE *fh = fopen("students.std", "wb");
    if(fh != NULL){
        fwrite(ptr, sizeof(struct student), 1, fh);
        fclose(fh);
    }

    free(ptr);

    // struct student *aptr = (struct student*)malloc(sizeof(struct student));
    // void *ptr = malloc(8);
    // char *cptr = (char*)ptr;
    // short *sptr = (short*)ptr;
    // int *iptr = (int*)ptr;
    // long *lptr = (long*)ptr;

    // *(cptr) = 'C';
    // *(sptr+2) = 0xefaa;

    // free(ptr);
    return 0;
}
