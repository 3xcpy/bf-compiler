#include <stdio.h>
#include <stdlib.h>

size_t mem_size = 1048576;
const int stack_size = 1024;

int main(int argc, char** argv)
{
    FILE* output = fopen("out.asm", "w");

    FILE* input = fopen(argv[1], "r");

    if(!input)
    {
        printf("ERROR: Failed to open the input file\n");
        exit(2);
    }

    fprintf(output, "format ELF64 executable\n");
    fprintf(output, "segment readable executable\n");
    fprintf(output, "entry main\n");
    fprintf(output, "main:\n");
    fprintf(output, "\tmov r15, mem\n");

    int lcounter = -1;
    int lindex = -1;
    int lstack[stack_size];
    char c;
    while((c = getc(input)) > 0)
    {
        switch(c)
        {
            case '<':
                fprintf(output, "\tsub r15, 1\n");
                break;
            case '>':
                fprintf(output, "\tadd r15, 1\n");
                break;
            case '+':
                fprintf(output, "\tinc byte [r15]\n");
                break;
            case '-':
                fprintf(output, "\tdec byte [r15]\n");
                break;
            case '[':
                lindex++;
                lcounter++;
                lstack[lindex] = lcounter;
                fprintf(output, "start_%i:\n\tcmp byte [r15], 0\n\tje end_%i\n", lstack[lindex], lstack[lindex]);
                break;
            case ']':
                fprintf(output, "\tjmp start_%i\nend_%i:\n", lstack[lindex], lstack[lindex]);
                lindex--;
                break;
            case '.':
                fprintf(output, "\tmov rax, 1\n\tmov rdi, 1\n\tmov rsi, r15\n\tmov rdx, 1\n\tsyscall\n");
                break;
            case ',':
                fprintf(output, "\tmov rax, 0\n\tmov rdi, 0\n\tmov rsi, r15\n\tmov rdx, 1\n\tsyscall\n");
                break;
        }
    }

    fprintf(output, "\tmov rax, 60\n");
    fprintf(output, "\tmov rdi, 0\n");
    fprintf(output, "\tsyscall\n");

    fprintf(output, "segment readable writable\n");
    fprintf(output, "\tmem rb %zu\n", mem_size);

    return 0;
}
