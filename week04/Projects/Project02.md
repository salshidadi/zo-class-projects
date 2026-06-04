# Generic Data Structure

A C program that implements a data structure capable of storing and managing any data type.

# Overview

Unlike Project 1 which was built for a specific record type, this project generalizes the data structure so it can work with any type of data.

# Concept

The project focuses on:

- Working with `void` pointers to handle any data type
- Implementing core data operations independently of the stored type
- Reusability and abstraction in C

The data structure does not assume anything about the data it holds. Instead, it uses generic pointers and size information to store, retrieve, and manage any type of record.

# How It Works

1. The program initializes a generic data structure
2. The user defines the type and size of the data to store
3. The user performs one of the supported operations:
   - **Insert**: Add a new record of any type
   - **Delete**: Remove an existing record
   - **Update**: Modify an existing record
   - **Retrieve**: Look up and return a record
4. The data structure handles the operation without knowing the underlying data type

# Example

## Insert (integer)
```text
> Insert: 42
Record added successfully
```

## Insert (string)
```text
> Insert: "Ahmed"
Record added successfully
```

## Retrieve
```text
> Retrieve index: 0
Record: 42
```
