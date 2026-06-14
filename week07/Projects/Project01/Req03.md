# Virtual Machine — Requirement 3

Part 3 of the Virtual Machine project.
Extend the VM from Requirement 2 by adding a Heap memory area with allocate and free operations.

# Overview

A heap is a region of memory used for dynamic allocation. Unlike the stack, heap memory is allocated and freed explicitly. This requirement adds a dedicated heap area to the VM along with two new instructions to manage it.

# Concept

The project focuses on:

- Heap memory design in a VM
- Dynamic memory allocation and deallocation
- Implementing alloc and free as VM instructions
- Understanding how dynamic memory is managed in real processors

The heap allows the program to request memory at runtime and release it when it is no longer needed. The VM must track which regions of the heap are in use and which are free.

# Requirements

## New Instructions

| Instruction | Description                                              |
|-------------|----------------------------------------------------------|
| ALLOC       | Allocate a block of memory on the heap, return its address |
| FREE        | Free a previously allocated block of heap memory         |



