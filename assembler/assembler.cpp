#include "assembler.hpp"
#include "file.hpp"

void assembler(const char *file, prog *text_program) {
    FILE *fp = fopen(file, "w+b");
    assert(fp != nullptr && "coudn't open file");

    fprintf(fp, "%s %d %d\n", SIGNATURE, VERSION, text_program->NUMBER);

    text_program->code = (int *) calloc(text_program->NUMBER * 2, sizeof(int));

    assert(text_program->code != nullptr && "null pointer");
    
    char cmd[10]; 
    int ip = 0;
    for (int i = 0; i < text_program->NUMBER; i++) {
            sscanf(text_program->text[i], "%s", cmd);
        if (strncmp(cmd, "push", 4) == 0) {
            text_program->code[ip++] = PUSH;
            text_program->text[i] += strlen(cmd);

            int arg = 0;
            sscanf(text_program->text[i], "%d", &arg);
            text_program->code[ip++] = arg;

        } else if (strncmp(cmd, "hlt", 3) == 0) {
            text_program->code[ip++] = HLT;

        } else if (strncmp(cmd, "add", 3) == 0) {
            text_program->code[ip++] = ADD;

        } else if (strncmp(cmd, "sub", 3) == 0) {
            text_program->code[ip++] = SUB;

        } else if (strncmp(cmd, "mul", 3) == 0) {
            text_program->code[ip++] = MUL;

        } else if (strncmp(cmd, "div", 3) == 0) {
            text_program->code[ip++] = DIV;
        
        } else if (strncmp(cmd, "out", 3) == 0) {
            text_program->code[ip++] = OUT;

        } else if (strncmp(cmd, "dump", 4) == 0) {
            text_program->code[ip++] = DUMP;

        } else if (strncmp(cmd, "in", 2) == 0) {
            text_program->code[ip++] = IN;

        } else if (strncmp(cmd, "dup", 2) == 0) {
            text_program->code[ip++] = DUP;

        } else if (strncmp(cmd, "jmp", 2) == 0) {
            text_program->code[ip++] = JMP;

            int arg = 0;
            sscanf(text_program->text[i], "%d", &arg);
            text_program->code[ip++] = arg;

        } else {
            printf("comand didn't found\n");
        }
    }

    for (int i = 0; i < ip; i++) {
        fprintf(fp, "%d ", text_program->code[i]);
    }
    fprintf(fp, "\n");
    fclose(fp);
}

