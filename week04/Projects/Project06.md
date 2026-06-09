
# File Hash Storage

A C command-line utility that stores files in a hash-based directory structure, similar to how Git organizes its objects.

# Overview

The program takes a file, scrambles its content using a randomly generated key, and stores it in a directory organized by the hash of that key. The stored content can later be retrieved or extracted back into a file using its hash.

# Concept

The project focuses on:

- Hash-based file storage in C
- Organizing files in a directory structure derived from a hash
- Scrambling and reverting file content using a generated key
- Understanding how tools like Git store objects internally

Each file is identified by the hash of its key. The directory structure mirrors Git's object storage — the first bytes of the hash form the directory name and the rest form the filename inside it.

# How It Works

**Hash a file:**
1. The user provides a file
2. A random key is generated
3. The file content is scrambled using the key
4. The program checks if the hash-based directory already exists — if it does, it skips creation
5. The scrambled content is stored in the directory
6. The hash is printed to the terminal

**Get file content:**
1. The user provides a hash
2. The program locates the stored content using the hash
3. The content is displayed in the terminal

**Save reverted content to file:**
1. The user provides a hash and an output filename
2. The program locates and reverts the stored content
3. The original file content is written to the output file

# Example

## Hash a file
```bash
./app filename
```
```text
a3f9c2...  (hash of the stored content)
```

## Get content
```bash
./app a3f9c2...
```
```text
(file content displayed)
```

## Save to file
```bash
./app -f a3f9c2... output.txt
```
```text
output.txt  (original file content restored)
```
