# Virtual Machine — Requirement 2

Part 2 of the Virtual Machine project.
Extend the VM from Requirement 1 by adding a Stack memory area that enables the concept of functions through CALL and RET instructions.

# Overview

A stack is a region of memory that follows a Last-In First-Out (LIFO) order. This requirement adds a dedicated stack area to the VM to support function calls — allowing the program to jump to a function and return back to where it left off.

# Concept

The project focuses on:

- Stack memory design in a VM
- Managing a stack pointer
- Implementing PUSH and POP as the underlying stack operations
- Implementing CALL and RET to enable function calls
- Understanding how real processors handle function calls and returns

When a function is called, the return address is pushed onto the stack. When the function finishes, the return address is popped from the stack and execution resumes from that point.

# Requirements

## New Instructions

| Instruction | Description                                                        |
|-------------|--------------------------------------------------------------------|
| PUSH        | Push a value or register onto the top of the stack                 |
| POP         | Pop the top value from the stack into a register                   |
| CALL        | Push the return address onto the stack and jump to a function      |
| RET         | Pop the return address from the stack and jump back to the caller  |

