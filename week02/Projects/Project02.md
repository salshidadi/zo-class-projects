# Binary File I/O

A C program that demonstrates how to read and write binary data to and from files on disk.

# Overview

The program writes binary data to a file on disk and reads it back, showing how raw bytes are stored and retrieved using C.

# Concept

The project focuses on:

- Binary file I/O in C
- Understanding the difference between binary and text mode
- Working with raw bytes on disk

Unlike text files, binary files store data exactly as it exists in memory — no formatting or encoding is applied. This makes them suitable for storing structs, arrays, and other raw data types.

# How It Works

1. Open a file in binary write mode
2. Write data to the file
3. Close the file
4. Reopen the file in binary read mode
5. Read the data back into memory
6. Close the file

# Example

## Input
```text
Some data in memory (a number, struct, or array)
```

## Output
```text
data.bin  (the same data stored as raw bytes on disk)
```
