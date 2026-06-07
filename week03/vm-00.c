#include <stdio.h>
#include <stdbool.h>

/*
  24-bit instruction
  opcode operand1 operand2
  5 sum
  6 sub
  7 mul
  8 div
*/

#define OPCODE_ADD 5
#define OPCODE_SUB 6
#define OPCODE_MUL 7
#define OPCODE_DIV 8

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
        left_operand = program[IP+1];
        right_operand = program[IP+2];

        switch(program[IP]){
            case OPCODE_ADD:
                result = left_operand + right_operand;
            break;
            case OPCODE_SUB:
                result = left_operand - right_operand;
            break;
            case OPCODE_MUL:
                result = left_operand * right_operand;
            break;
            case OPCODE_DIV:
                if(right_operand == 0){
                    printf("Exception: divide by zero\n");
                    return false;
                }
                result = left_operand / right_operand;
            break;
            default:
                printf("Invalid instruction\n");
                return false;
        }

        printf("result -> %d\n", result);
        // result = 0;
    }

    return true;
}

static int program_size = 15;
static unsigned char program [] = {
    5, 9, 7,   /* ADD 9, 7  */
    6, 8, 4,   /* SUB 8, 4  */
    7, 3, 6,   /* MUL 3, 6  */
    8, 9, 3,   /* DIV 9, 3  */
    8, 5, 0    /* DIV 5, 0  */

};


int main(void){
    if(cpu(program, program_size)){
        printf("Program has been executed successfully\n");
    }
    return 0;
}