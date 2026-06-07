#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define OPCODE_ADD 0
#define OPCODE_SUB 1
#define OPCODE_MUL 2
#define OPCODE_DIV 3
#define OPCODE_MOD 4

#define INSTRUCTIONS_COUNT  5
#define INSTRUCTION_SIZE 3

#define PROGRAM_SIZE 15

static unsigned char program [] = {
    0, 9, 7,   /* ADD 9, 7  */
    1, 8, 4,   /* SUB 8, 4  */
    2, 3, 6,   /* MUL 3, 6  */
    3, 9, 3,   /* DIV 9, 3  */
    4, 7, 2,    /* MOD 7, 2  */
};

/* fetch -> decode -> execute */

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

/* Registers */
static int IP = 0;
static unsigned char IR[INSTRUCTION_SIZE] = {0, 0, 0};
static int OUTPUT = 0;

static opcode_function_t current_instruction = NULL;

#define LEFT_OPERAND  IP + 1
#define RIGHT_OPERAND IP + 2

static bool cpu_fetch(void){
    int byte = 0;
    if(IP >= PROGRAM_SIZE){
        /* HALT */
        exit(0);
    }

    /* Fetch */
    IR[0] = program[IP];
    IR[1] = program[LEFT_OPERAND];
    IR[2] = program[RIGHT_OPERAND];

    /* Move to the next insturction */
    IP += INSTRUCTION_SIZE;
    
    return true;
}

static bool cpu_decode(void){
    if(IR[0] >= INSTRUCTIONS_COUNT){
        printf("Invalid instruction\n");
        // IR[0] = 10; // rewrite
        IR[0] = IR[1] = IR[2] = 0;
        exit(0);
    }

    current_instruction = opcode_functions[IR[0]];

    return true;
}

static bool cpu_execute(void){
    OUTPUT = current_instruction(IR[1], IR[2]);
    return true;
}

int main(void){
    // reset
    IP = 0;
    IR[0] = IR[1] = IR[2] = 0;

    while(true){
        cpu_fetch();
        cpu_decode();
        cpu_execute();
        printf("output -> %d\n", OUTPUT);
    }

    return 0;
}