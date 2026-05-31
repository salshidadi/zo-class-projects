# File Format Parser

A C program that reads a binary file and parses its header according to a specific file format layout.

# Overview

Every file format has a defined binary structure where each field is stored at a specific byte offset with a fixed size. The program reads a file in binary and maps its raw bytes to meaningful data based on that layout.

# Concept

The project focuses on:

- Understanding binary file layouts and byte offsets
- Mapping raw bytes to structured data
- Memory alignment and struct packing
- Reading format specifications and applying them in code

Each file format defines its own header structure. By reading the bytes at the right offsets, the program can extract meaningful information such as file type, size, dimensions, or version — without relying on any external library.

# How It Works

1. Choose a file format (image, audio, executable, etc.)
2. Study its binary layout specification and identify the fields and their offsets
3. Open a file of that format in binary mode
4. Read and parse at least the first four fields from the header
5. Display the extracted data

# Example

## Generic File Header Layout

| Offset | Size    | Field      | Description                     |
|--------|---------|------------|---------------------------------|
| 0      | 2 bytes | Signature  | Magic number identifying the format |
| 2      | 4 bytes | File Size  | Total size of the file in bytes |
| 6      | 4 bytes | Field 3    | Format-specific field           |
| 10     | 4 bytes | Field 4    | Format-specific field           |

## Output
```text
Signature : ...
File Size : ... bytes
Field 3   : ...
Field 4   : ...
```
