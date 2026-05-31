# File Metadata

Part 2 of the C command-line file processing project.
An extension of the File Splitter CLI that saves metadata about the split operation into a separate `.pmd` file.

# Overview

After splitting a file, the program generates a `.pmd` metadata file named after the original file. This file stores all the information needed by the merger in Requirement 3 to correctly reconstruct the original file.

# Concept

The project focuses on:

- Struct design in C
- Writing structured metadata to a file
- Handling uneven block sizes
- Preparing data for the merge operation

The `.pmd` file captures everything needed to reverse the split: the original filename, total file size, block size, and how many extra bytes exist if the file didn't divide evenly.

# How It Works

1. The user runs the program with `-p`, a file path, and a number of blocks
2. The file is split into equal-sized blocks (Requirement 1 behavior)
3. The program creates a `.pmd` metadata file named after the original file
4. The `.pmd` file stores:
   - File name
   - Total file size
   - Block size
   - Number of extra bytes (remainder from uneven division)
   - Which block index holds the extra bytes

# Example

## Command
```bash
./app -p movie.mp4 3
```

## Output Files
```text
movie_part1.mp4
movie_part2.mp4
movie_part3.mp4
movie.mp4.pmd
```
