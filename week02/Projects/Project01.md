# Project01
A C project that demonstrates how the C Preprocessor can be used to compose and control program behavior using directives such as:

#include, #define, #ifdef, #ifndef, #else, #endif


## Overview 

This project explores how the C preprocessor can affect program structure before compilation.

Instead of focusing on runtime logic only, the project demonstrates how source files and macros can be combined to dynamically enable or disable sections of code.

The implementation uses nested loops distributed across multiple .c files and controlled through conditional compilation. 


## Concept

The project demonstrates:

- Conditional compilation using macro directives
- Including .c files inside other source files
- Building nested loop behavior through the preprocessor
- Enabling or disabling logic branches at compile time

The goal is to understand how preprocessing works before the actual compilation stage.

## Source Flow

### Main File
```c
#include<stdio.h>

int main(){
    #include "example12.a.c"
    return 0;
}
```
### Outer Loop
```c
for(int y = 0; y < 10; y++){
    printf("y: %d\n", y);

    #include "example12.b.c"
}
```
### Inner Loop
```c
for(int i = 0; i < 10; i++){
    printf("result = %d\n", (i * y));
}
```

## How It Works

The project demonstrates three compilation scenarios:

Case 1 — Inner Loop Only

Only the inner loop logic is enabled through macro configuration.

Case 2 — Outer Loop Only

Only the outer loop executes.

Case 3 — Both Loops Enabled

Both loops are compiled, creating nested loop behavior.
