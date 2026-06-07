#include <stdio.h>
#include <stdbool.h>

#define OPCODE_ADD 0
#define OPCODE_SUB 1
#define OPCODE_MUL 2
#define OPCODE_DIV 3
#define OPCODE_MOD 4

#define INSTRUCTIONS_COUNT  5


/* int(unsigned char, unsigned char) */

typedef int(*opcode_function_t)(unsigned char, unsigned char);

int opcode_add(unsigned char left_operand, unsigned char right_operand){
    return left_operand + right_operand;
}

int opcode_sub(unsigned char left_operand, unsigned char right_operand){
    return left_operand - right_operand;
}

int opcode_mul(unsigned char left_operand, unsigned char right_operand){
    return left_operand * right_operand;
}

int opcode_div(unsigned char left_operand, unsigned char right_operand){
    if(right_operand == 0){
                    printf("Exception: divide by zero\n");
                    return false;
                }
    return left_operand / right_operand;
}

int opcode_mod(unsigned char left_operand, unsigned char right_operand){
    return left_operand % right_operand;
}

static const opcode_function_t opcode_functions[INSTRUCTIONS_COUNT] = {
        opcode_add, opcode_sub, opcode_mul, opcode_div, opcode_mod
};

bool cpu(unsigned char *program, int size){
    int instruction_size = 3;
    int instructions_count = 0;

    unsigned char left_operand = 0;
    unsigned char right_operand = 0;

    int result = 0;

    if(size == 0){
        return true;
    }

    if((size % 3) != 0){
        printf("Invalid program\n");
        return false;
    }

    instructions_count = size / instruction_size;

    for(int IP = 0; IP < size; IP = IP + 3){
        if(program[IP] >= INSTRUCTIONS_COUNT){
            printf("Invalid instruction\n");
            return false;
        }

        left_operand = program[IP+1];
        right_operand = program[IP+2];
        result = opcode_functions[program[IP]](left_operand, right_operand);
        printf("result -> %d\n", result);
        // result = 0;
    }

    return true;
}

static int program_size = 15;
static unsigned char program [] = {
    0, 9, 7,   /* ADD 9, 7  */
    1, 8, 4,   /* SUB 8, 4  */
    2, 3, 6,   /* MUL 3, 6  */
    3, 9, 3,   /* DIV 9, 3  */
    4, 7, 2    /* MOD 7, 2  */
};


int main(void){
    if(cpu(program, program_size)){
        printf("Program has been executed successfully\n");
    }
    return 0;
}
