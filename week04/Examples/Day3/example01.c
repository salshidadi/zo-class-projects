#include <stdio.h>
#include <stdbool.h>

#define MAX_FIELD_SIZE   64
#define MAX_TALBLE_NAME 128

struct field{
    char name[MAX_FIELD_SIZE];
    char type; // i c s b
    unsigned int size;
    void *value; // note
    void *defalut_value;
    bool is_unique;
    bool is_primary;
};

struct table{
    char name[MAX_TALBLE_NAME];
    unsigned char fileds_count;
    unsigned long rows_count;
    struct field *fields;
};

int main(void){
    struct table students;
    // students.name = "students";
    students.fileds_count = 0;
    students.rows_count = 0;
    students.fields = NULL;

    struct field students_fields[5] = {
        {"id", 'i', 0, NULL, NULL},
        {"name", 's', 40, NULL, NULL},

    };

    students.fields = students_fields;
    
    return 0;
}
