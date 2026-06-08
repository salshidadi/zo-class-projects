# Bitmap Renderer

A C program that renders a colored pixel-art image directly in the terminal using a 2D grid where each cell encodes multiple visual properties in a single byte.

# Overview

The program reads a 2D grid of bytes and renders each cell as a colored symbol on the terminal. Every byte in the grid carries all the information needed to display that cell: whether it is visible, what color it has, and what symbol to show.

# Concept

The project focuses on:

- Bit-level data encoding in C
- Packing multiple attributes into a single byte
- 2D grid traversal
- Colored terminal output

Each cell in the grid is represented by one byte. That byte is divided into smaller bit segments, where each segment encodes a specific visual property of the cell. The program reads these segments and translates them into a visible, colored character on the terminal.

# How It Works

1. A 2D grid of bytes is defined, where each byte represents one pixel
2. The program iterates over every cell in the grid
3. For each cell, the byte is decoded into its visual properties
4. The corresponding colored symbol is printed to the terminal
5. The full grid is rendered as a pixel-art image

# Example

## Input
```text
A 2D grid of encoded byte values
```

## Output
```text
A colored pixel-art image rendered in the terminal
```
