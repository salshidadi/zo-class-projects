#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int(*opcode_function_t)(unsigned char, unsigned char);

#define OPCODE_ADD 0
#define OPCODE_SUB 1
#define OPCODE_MUL 2
#define OPCODE_DIV 3
#define OPCODE_MOD 4
#define OPCODE_STP 5
#define OPCODE_LDI 6
#define OPCODE_ADR 7
#define OPCODE_SUR 8
#define OPCODE_INC 9
#define OPCODE_DEC 10
#define OPCODE_JMP 11
#define OPCODE_CMP 12

#define OPCODE_JE  13
#define OPCODE_JZ  13

#define PROGRAM_CODE_SIZE     sizeof(program) - CR
#define PROGEAM_DATA_SIZE     CR - DR    
#define INSTRUCTIONS_COUNT    14
#define INSTRUCTION_SIZE      3

#define LEFT_OPERAND  CR + IP + 1
#define RIGHT_OPERAND CR + IP + 2

#define RX_COUNT 4


static unsigned char program [] = {
/* DATA: */
      0, 0, 0, 0,
/* CODE: */
  /* 00 */  0, 9, 7,    /* ADD 9, 7   */
  /* 03 */  1, 8, 4,    /* SUB 8, 4   */
  /* 06 */  0, 5, 8,    /* ADD 5, 8   */
  /* 09 */  6, 2, 77,   /* LDI R2, 77 */
  /* 12 */  7, 2, 23,   /* ADR R2, 23 */
  /* 15 */  8, 2, 5,    /* SUR R2, 5  */
  /* 18 */  2, 3, 6,    /* MUL 3, 6   */
  /* 21 */  3, 9, 3,    /* DIV 9, 3   */
  /* 24 */  4, 7, 2,    /* MOD 7, 2   */
  /* 27 */  6, 0, 20,   /* LDI R0, 20 */
  /* 30 */  6, 1, 20,   /* LDI R1, 20 */
  /* 33 */  11, 45, 0,  /* JMP 45     */
  /* 36 */  6, 0, 70,   /* LDI R0, 70 */
  /* 39 */  9, 0, 0,    /* INC R0     */
  /* 42 */  10, 0, 0,   /* DEC R0     */
  /* 45 */  12, 0, 1,   /* CMP R0, R1 */
  /* 48 */  13, 36, 0,  /* JE  36     */
  /* 51 */  5, 0, 0     /* STP 0      */
};



/* Registers */
static int IP = 0;
static unsigned char IR[INSTRUCTION_SIZE] = {0, 0, 0};
static int OUTPUT = 0;

static unsigned char FLAGS = 0;

#define FLAG_POSITIVE 0
#define FLAG_ZERO     1
#define FLAG_NEGATIVE 2

/* 0000 0000 */
/* xxxx xxNZ */

static unsigned char R0 = 0;
static unsigned char R1 = 0;
static unsigned char R2 = 0;
static unsigned char R3 = 0;

static unsigned char DR = 0; /* data register */
static unsigned char CR = 0; /* code register */


static opcode_function_t current_instruction = NULL;

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

static unsigned char get_rx_value(unsigned char operand){
     switch(operand){
        case 0: return R0;
        case 1: return R1;
        case 2: return R2;
        case 3: return R3;
        // skip default case
    }

    return 255;
}

static void set_rx_value(unsigned char operand, unsigned char value){
     switch(operand){
        case 0: R0 = value; return;
        case 1: R1 = value; return;
        case 2: R2 = value; return;
        case 3: R3 = value; return;
        // skip default case
    }
}

int opcode_ldi(unsigned char left_operand, unsigned char right_operand){
    switch(left_operand){
        case 0: R0 = right_operand; break;
        case 1: R1 = right_operand; break;
        case 2: R2 = right_operand; break;
        case 3: R3 = right_operand; break;
        default:
            printf("Invalid register address\n");
            exit(0);
    }

    return right_operand;
}

int opcode_stp(unsigned char left_operand, unsigned char right_operand){
    OUTPUT = left_operand;
    exit(left_operand);
}

int opcode_adr(unsigned char left_operand, unsigned char right_operand){
    if(left_operand >= RX_COUNT){
        printf("Invlaid Rx register address\n");
        exit(0);
    }

    unsigned char Rx = get_rx_value(left_operand) + right_operand;
    set_rx_value(left_operand, Rx);
    return Rx;
}

int opcode_sur(unsigned char left_operand, unsigned char right_operand){
    if(left_operand >= RX_COUNT){
        printf("Invlaid Rx register address\n");
        exit(0);
    }

    unsigned char Rx = get_rx_value(left_operand) - right_operand;
    set_rx_value(left_operand, Rx);
    return Rx;
}


int opcode_inc(unsigned char left_operand, unsigned char right_operand){
    if(left_operand >= RX_COUNT){
        printf("Invlaid Rx register address\n");
        exit(0);
    }

    unsigned char Rx = get_rx_value(left_operand);
    Rx++;
    set_rx_value(left_operand, Rx);
    return Rx;
}

int opcode_dec(unsigned char left_operand, unsigned char right_operand){
    if(left_operand >= RX_COUNT){
        printf("Invlaid Rx register address\n");
        exit(0);
    }

    unsigned char Rx = get_rx_value(left_operand);
    Rx--;
    set_rx_value(left_operand, Rx);
    return Rx;
}

int opcode_jmp(unsigned char left_operand, unsigned char right_operand){
    IP = left_operand;
    return left_operand;
}

int opcode_cmp(unsigned char left_operand, unsigned char right_operand){
    unsigned char Rx = get_rx_value(left_operand);
    unsigned char Ry = get_rx_value(right_operand);

    OUTPUT = Rx - Ry;
    FLAGS = FLAG_POSITIVE;

    if(OUTPUT == 0){
        FLAGS = FLAG_ZERO;
    }else if (OUTPUT < 0){
        FLAGS = FLAG_NEGATIVE;
    }

    return FLAGS;
}

int opcode_je(unsigned char left_operand, unsigned char right_operand){

    if(FLAGS == FLAG_ZERO){
        IP = left_operand;
        return left_operand;
    }
    
    return 255;
}

static const opcode_function_t opcode_functions[INSTRUCTIONS_COUNT] = {
        opcode_add, opcode_sub, opcode_mul,
        opcode_div, opcode_mod, opcode_stp,
        opcode_ldi, opcode_adr, opcode_sur,
        opcode_inc, opcode_dec, opcode_jmp,
        opcode_cmp, opcode_je
};


static bool cpu_fetch(void){
    int byte = 0;
    if(IP >= PROGRAM_CODE_SIZE){
        /* HALT */
        exit(0);
    }

    /* Fetch */
    IR[0] = program[CR + IP];
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

void vm_init(void){
    // reset
    IR[0] = IR[1] = IR[2] = 0;

    DR = 0;
    CR = 4;

    IP = 0;
}

int main(void){
    vm_init();
    while(true){
        cpu_fetch();
        cpu_decode();
        cpu_execute();
        printf("output -> %d\n", OUTPUT);
    }

    return 0;
}
