# Virtual Machine — Requirement 2

Part 2 of the Virtual Machine project.
Extend the VM from Requirement 1 by adding a Stack memory area that enables the concept of functions through CALL and RET instructions.

# Overview

A stack is a region of memory that follows a Last-In First-Out (LIFO) order. This requirement adds a dedicated stack area to the VM to support function calls — allowing the program to jump to a function and return back to where it left off.

# Concept

The project focuses on:

- Stack memory design in a VM
- Managing a stack pointer
- Implementing CALL and RET to enable function calls
- Understanding how real processors handle function calls and returns

When a function is called, the return address is pushed onto the stack internally. When the function finishes, the return address is popped from the stack and execution resumes from that point. Push and pop are internal stack operations used by CALL and RET — they are not exposed as separate instructions.

# Requirements

## New Instructions

| Instruction | Description                                                       |
|-------------|-------------------------------------------------------------------|
| CALL        | Push the return address onto the stack and jump to a function     |
| RET         | Pop the return address from the stack and jump back to the caller |
