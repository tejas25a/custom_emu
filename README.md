# Custom Emu
Custom emulator is a small CPU emulator written in C.It simulates a Accumulator (A), a General-purpose register (B), a Program Counter, a Stack pointer, a byte size flag.

The emulator has 1024 bytes of memory and supports 11 instructions(opcodes).It fetches instruction from memory and executes one by one, similar to a real CPU.

## Supported Opcodes.

Opcode Description
NOP     No operation
LDI     Load immediate value into A
LDB     Load immediate value into B
LDA     Load A from memory
STA     Store A to memory
ADD     A = A + B
SUB     A = A - B
JMP     Jump to address
JZ      Jump if zero
OUT     print A
HLT     Halt CPU

## Requirements
- C-compiler - developed and test with gcc 16.2.1 
- GNU Make 4.4.1 

## Project Structure
.
├── Makefile
├── README.md
└── src
    └── main.c

## Build & Test

### Build the project
make       

### Run the binary
make test  

### Remove the binary
make clean 

### Quick Start
make && make test

The emulator should build and run from the terminal-emulator

## Why I Built This

This project is mainly built for a small experiment with the idea of emulating things.
