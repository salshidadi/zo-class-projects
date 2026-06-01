# File Splitter CLI

Part 1 of the C command line file processing project.
A command-line file splitting utility written in C that divides a file into smaller chunks based on a user-defined block size

## Overview 

The program takes:

1. A file path
2. A number of blocks

It then reads the file, divides it into equal-sized blocks based on that number, and stores each block as a separate file.


## Concept

The project focuses on:

- Command-line argument handling in C
- File I/O operations
- Dynamic file segmentation
- Buffer management
- File partitioning logic

Instead of specifying the chunk size directly, the user specifies how many parts the file should be divided into.

The program calculates the size of each block automatically.


## How It Works

1. The user runs the program from the terminal
2. The first argument is the target file
3. The second argument is the number of blocks
4. The program calculates the size of each block
5. The file is divided into multiple smaller files


## Example

### Input Arguments
```bash
movie.mp4 4
```

### Output Files
```text
movie_part1
movie_part2
movie_part3
movie_part4
```
