# Block Rotation

Part 4 of the C command-line file processing project.
An extension of the merger that rotates the block order before reassembling the file.

# Overview

Before merging, the program shifts the block sequence by a specified number of positions. This is a circular rotation: blocks wrap around from one end to the other, and then the rotated sequence is merged into the output file.

# Concept

The project focuses on:

- Circular array/block rotation logic
- Combining multiple CLI flags in one command
- Modifying merge order without altering block content

Rotation shifts the block sequence by N positions before the merge step. This changes the order in which blocks are written to the output file without touching the data inside each block.

# How It Works

1. The user runs the program with `-m`, the `.pmd` metadata file, `-r`, the rotation count, and the output filename
2. `-m` activates merge mode and reads the metadata file
3. `-r` followed by a number specifies how many positions to rotate the block sequence
4. The block sequence is rotated by that many positions
5. The rotated block order is used when merging into the output file

# Example

## Command
```bash
App -m file.mp4.pmd -r 2 output.mp4
```

## Block Order (4 blocks, rotated by 2)
```text
Before rotation:  part1  part2  part3  part4
After rotation:   part3  part4  part1  part2
```

## Output
```text
output.mp4
```
