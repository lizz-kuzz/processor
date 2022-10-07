#include "assembler.hpp"
#include "file.hpp"

char *check_cmd(char *cmd) {
    assert(cmd != nullptr && "null pointer");

    if (strncmp(cmd, "push", 4) == 0) {
         cmd += 3;
        *cmd = PUSH;
         return cmd;

    } else if (strncmp(cmd, "hlt", 3) == 0) {
         cmd += 2;
        *cmd = HLT;
         return cmd;

    } else if (strncmp(cmd, "add", 3) == 0) {
         cmd += 2;
        *cmd = ADD;
         return cmd;

    } else if (strncmp(cmd, "sub", 3) == 0) {
         cmd += 2;
        *cmd = SUB;
         return cmd;

    } else if (strncmp(cmd, "mul", 3) == 0) {
         cmd += 2;
        *cmd = MUL;
         return cmd;

    } else if (strncmp(cmd, "div", 3) == 0) {
         cmd += 2;
        *cmd = DIV;
         return cmd;

    } else if (strncmp(cmd, "out", 3) == 0) {
         cmd += 2;
        *cmd = OUT;
         return cmd;

    } else if (strncmp(cmd, "dump", 4) == 0) {
         cmd += 3;
        *cmd = DUMP;
         return cmd;

    } else if (strncmp(cmd, "in", 2) == 0) {
         cmd += 1;
        *cmd = IN;
         return cmd;

    } else {
        printf("comand didn't found\n");
        return 0;
    }
}


void assembler(const char *file, prog *text_program) {
    FILE *fp = fopen(file, "w");
    assert(fp != nullptr && "coudn't open file");

    const char *sign = SIGNATURE;
    const int version = VERSION;
    fprintf(fp, "%s %d %d\n", sign, version, text_program->NUMBER);

    for (int i = 0; i < text_program->NUMBER; i++) {
        char *cmd = check_cmd(text_program->text[i]);
        fprintf(fp, "%s ", cmd);
    }
    fprintf(fp, "\n");

    fclose(fp);
}

void disassembler(const char *file_input, const char *file_output) {
    prog program = {};
    
    read_file(file_input, &program);


    FILE *file = fopen(file_output, "w");
    assert(file != nullptr && "coudn't open file");

    char *point = program.text_buf;
    fprintf(file, "%s\n", point);

    size_t len_first_line = strlen(point);
    point += len_first_line + 1;
    
    for (; *point != '\0'; point++) {
        if (isalnum(*point) != 0) {
            if (*point == PUSH) {
                fprintf(file, "push ");
                point += 2;
                for (; isalnum(*point) != 0;) {
                    fputc(*point, file);
                    point++;
                }
                fprintf(file, "\n");
            } else if (*point == ADD) {
                fprintf(file, "add\n");
                point += 1;
            } else if (*point == SUB) {
                fprintf(file, "sub\n");
                point += 1;
            } else if (*point == MUL) {
                fprintf(file, "mul\n");
                point += 1;
            } else if (*point == DIV) {
                fprintf(file, "div\n");
                point += 1;
            } else if (*point == OUT) {
                fprintf(file, "out\n");
                point += 1;
            } else if (*point == HLT) {
                fprintf(file, "hlt\n");
                point += 1;
            } else if (*point == DUMP) {
                fprintf(file, "dump\n");
                point += 1;
            } else if (*point == IN) {
                fprintf(file, "in\n");
                point += 1;
            } 
        }
    }
    fclose(file);
    free(program.text_buf);
    free(program.text);
}