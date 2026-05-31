# Archive Files Project

A C command-line tool that bundles multiple files into a single `.arc` archive file and manages them through a set of option flags.

# Overview

The program takes a command-line option and performs the corresponding archive operation. Each option controls a different aspect of managing the archive and the files stored inside it.
![Archive Tool Diagram](./images/Archive Tool.png)

# Concept

The project focuses on:

- Command-line argument handling in C
- Binary file I/O operations
- Archive file format design
- Storing and managing file metadata inside a single binary file

The archive file is divided into two sections:

**Header**
- Archive metadata: Magic Number, Version, and Files Count
- Files metadata table: one entry per stored file, each containing the File Size, Name Length, and File Name

**Data**
- The raw content of each file stored sequentially, in the same order as their entries in the files metadata table

# How It Works

1. The user runs the program from the terminal with an option flag
2. The program parses the option and any additional arguments (archive name, filenames)
3. The corresponding operation is performed on the archive file
4. The archive's header and data section are updated to reflect the change

# Options

| Option | Description                    |
|--------|--------------------------------|
| `-c`   | Create a new archive           |
| `-i`   | Insert a file into the archive |
| `-d`   | Delete a file from the archive |
| `-l`   | List all files in the archive  |
| `-x`   | Extract a file from the archive|
| `-h`   | Show help reference            |

# Example

```bash
Arch -c abc.arc
Arch -i abc.arc file1.txt
Arch -l abc.arc
```

```text
file1.txt
```
