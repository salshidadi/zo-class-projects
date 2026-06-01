# File Merger CLI

Part 3 of the C command-line file processing project.
The same program as Requirement 1 extended with a merge option that reconstructs the original file from its split parts.

## Overview

The program now supports two modes:

- `-p` : Split a file into blocks (Requirement 1)
- `-m` : Merge split blocks back into the original file

For the merge, the user only needs to provide the `.pmd` metadata file. The program reads it to find all the information required to locate and reassemble the split files.

## Concept

The project focuses on:

- Extending a CLI with multiple operation modes
- Reading and applying stored metadata
- Sequential file reading and writing
- Byte-accurate file reconstruction

The `.pmd` file from Requirement 2 contains everything needed: the original filename, block size, block count, and extra bytes — so the merger can locate and reassemble all parts without the user specifying them manually.

## How It Works

**Split mode (`-p`):**
1. The user passes the file path and number of blocks
2. The file is split into equal-sized blocks
3. A `.pmd` metadata file is saved

**Merge mode (`-m`):**
1. The user passes only the `.pmd` metadata file
2. The program reads the metadata to determine the block count, size, and filenames
3. Each block file is opened in order
4. Blocks are written sequentially into a single output file
5. Extra bytes are handled according to the metadata

## Example

### Split
```bash
./app -p movie.mp4 4
```

### Merge
```bash
./app -m movie.mp4.pmd
```

## Output
```text
movie.mp4  (identical to the original)
```
