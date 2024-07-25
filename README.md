# The simplest Brainfuck compiler I could think of

This project should not be used as a Brainfuck implementation (many programs don't even work with it), but if you want to make a Brainfuck compiler, this is probably the simplest way to do so.

## Requirements
- x64 Linux
- [fasm](https://flatassembler.net/)
- A C compiler

## Usage
Compile the compiler
```shell
cc bfc.c
```
Compile the Brainfuck source file
```
./a.out <source>.bf
```
Assemble the output
```
fasm out.asm
```
Mark it as executable
```
chmod +x out
```
