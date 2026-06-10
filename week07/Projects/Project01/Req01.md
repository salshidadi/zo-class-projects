# Virtual Machine — Requirement 1

Part 1 of the Virtual Machine project.
Extend a provided base VM implementation by adding new instructions, a new flag, a data segment, and memory operations.

# Overview

You are given a working base Virtual Machine written in C that implements a basic fetch-decode-execute cycle with a set of registers, flags, and instructions.

The provided source code is located at: `week07/Examples/vm-08.c`

Your task is to extend the VM by implementing the following requirements on top of the provided source code.

# Base VM

The base VM includes:

- **Registers**: R0–R3, IP (Instruction Pointer), IR (Instruction Register), OUTPUT
- **Flags**: POSITIVE, ZERO, NEGATIVE
- **Fetch-Decode-Execute cycle**

## Base Instruction Set

| Opcode | Instruction | Description                        |
|--------|-------------|------------------------------------|
| 0      | ADD         | Add two values                     |
| 1      | SUB         | Subtract two values                |
| 2      | MUL         | Multiply two values                |
| 3      | DIV         | Divide two values                  |
| 4      | MOD         | Modulo of two values               |
| 5      | STP         | Stop execution                     |
| 6      | LDI         | Load immediate value into register |
| 7      | ADR         | Add value to register              |
| 8      | SUR         | Subtract value from register       |
| 9      | INC         | Increment register                 |
| 10     | DEC         | Decrement register                 |
| 11     | JMP         | Unconditional jump                 |
| 12     | CMP         | Compare two registers              |
| 13     | JE / JZ     | Jump if equal / jump if zero       |

# Requirements

## 1 — All Jump Condition Instructions
Extend the VM with the remaining conditional jump instructions based on the FLAGS register:

| Instruction | Description              |
|-------------|--------------------------|
| JNE / JNZ   | Jump if not equal / not zero |
| JG          | Jump if greater          |
| JL          | Jump if less             |
| JGE         | Jump if greater or equal |
| JLE         | Jump if less or equal    |

## 2 — New Flag
Add a new flag to the FLAGS register to handle an additional condition beyond POSITIVE, ZERO, and NEGATIVE.

## 3 — Data Segment
Introduce a dedicated data segment in the VM — a separate memory region for storing named data values, distinct from the program instructions.

## 4 — Memory Store
Add an instruction that allows storing a value from a register into a memory address.

## 5 — Memory Operations
Add arithmetic instructions that operate directly on memory values:

| Instruction | Description                    |
|-------------|--------------------------------|
| ADDM        | Add a value to a memory address |
| SUBM        | Subtract a value from a memory address |
| MULM        | Multiply a memory address value |
| DIVM        | Divide a memory address value  |



