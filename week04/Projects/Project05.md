# File Integrity Checker

A C command-line tool that verifies whether a file has been modified by generating and comparing a visual key derived from the file's content.

# Overview

The program operates in two modes:

- `-g` : Generate a key file from a given file
- `-c` : Check a file's integrity by comparing it against a previously generated key

# Concept

The project focuses on:

- File integrity verification in C
- Deriving a unique key from file content
- Visualizing the key as a colored grid in the terminal
- Comparing keys to detect modifications

The key is produced by processing the file's content against a built-in cipher. The result is both saved as a `.key` file and visualized as a colored grid printed to the terminal. If the file is later modified, regenerating the key will produce a different result — revealing that the file's integrity has been compromised.

# How It Works

**Generate mode (`-g`):**
1. The user provides a file
2. The program processes the file's content against the built-in cipher
3. The resulting key is saved as a `.key` file
4. The key is visualized as a colored grid in the terminal

**Check mode (`-c`):**
1. The user provides a file and its previously generated `.key` file
2. The program re-derives the key from the current file content
3. Both the stored key and the new key are visualized in the terminal
4. The two keys are compared and the result is reported

# Example

## Generate
```bash
./app -g filename.file
```

## Check
```bash
./app -c filename.file filename.file.key
```

## Output
```text
The given key:   [colored grid]
The gen key:     [colored grid]

The key matched!
```
or
```text
The key doesn't match!
```
