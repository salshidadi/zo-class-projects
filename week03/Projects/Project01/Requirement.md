# Random Block Generator

Part 5 of the C command-line file processing project.
Extends the splitter to generate additional random-data blocks alongside the real file blocks.

# Overview

In addition to splitting the file into N blocks, the program can generate R extra blocks filled with random data. The total block count becomes N + R.

A 16-bit variable added to the metadata tracks which blocks are real and which are random using one bit per block position (1 = random, 0 = real).

# Concept

The project focuses on:

- Generating random byte data
- Bit-flag tracking using a 16-bit integer
- Updating the metadata struct from Requirement 2
- Interleaving real and random blocks

The 16-bit variable can represent up to 16 blocks. Since the maximum number of real partitions is 8 and the maximum number of random blocks is 8, 16 bits is exactly the right size.

# How It Works

1. The user runs the program with `-p` and `-R` flags
2. `-p` triggers split mode and divides the file into N blocks
3. `-R` followed by a number generates R additional random blocks
4. Each random block is filled with random bytes of the same block size
5. The metadata is updated:
   - Total block count = N + R
   - The 16-bit variable marks each block position: 0 = real, 1 = random

# Example

## Command
```bash
App -p File.file 6 -R 3
```

## 16-bit Block Map
```text
Total blocks: 9  (6 real + 3 random)

Bit position: 15 ... 8  7  6  5  4  3  2  1  0
Bit value:     0 ... 0  1  1  1  0  0  0  0  0

bit = 0 → real block
bit = 1 → random block
```

## Files
```text
File_part1  (real)
File_part2  (real)
File_part3  (real)
File_part4  (real)
File_part5  (real)
File_part6  (real)
File_part7  (random)
File_part8  (random)
File_part9  (random)
```
