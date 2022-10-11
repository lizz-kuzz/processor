#include "assembler.hpp"
#include "file.hpp"

#define BIT_CONST 5
#define BIT_REG 6
#define BIT_RAW 7
void get_args(prog *program, char *text_cmd, char *cmd, int *ip) {
    if (strcmp(cmd, "push") == 0) {
        text_cmd += strlen(cmd) + 1;
        *ip -= 1;

        int arg = 0;
        char arg_reg_raw[10];

        if (sscanf(text_cmd, "%s", arg_reg_raw) != 0) {
            if (strncmp(arg_reg_raw, "[", 1) == 0) {
            program->code[*ip] = program->code[*ip] | (1 << BIT_RAW);
            text_cmd++;
            }
        }

        if (sscanf(text_cmd, "%s", arg_reg_raw) != 0) {
            if (strncmp(arg_reg_raw, "rax", 3) == 0) {
                program->code[*ip] = program->code[*ip] | (1 << BIT_REG);
                arg = 1;
            } else if (strncmp(arg_reg_raw, "rbx", 3) == 0) {
                program->code[*ip] = program->code[*ip] | (1 << BIT_REG);
                arg = 2;
            } else if (strncmp(arg_reg_raw, "rcx", 3) == 0) {
                program->code[*ip] = program->code[*ip] | (1 << BIT_REG);
                arg = 3;
            } else if (strncmp(arg_reg_raw, "rdx", 3) == 0) {
                program->code[*ip] = program->code[*ip] | (1 << BIT_REG);
                arg = 4;
            }
        }

        if (sscanf(text_cmd, "%d", &arg) != 0) {
            program->code[*ip] = program->code[*ip] | (1 << BIT_CONST);
        } 

        *ip += 1;
        program->code[*ip] = arg;
        *ip += 1;

    } else if (strcmp(cmd, "jmp") == 0) {
        text_cmd += strlen(cmd) + 1;
        int arg = 0;
        if (sscanf(text_cmd, "%d", &arg) != 0) {
            ;
        } else if (*text_cmd == ':') {
            text_cmd++;
            int labl = 0;
            sscanf(text_cmd, "%d", &labl);
            arg = program->lables[labl];
        }
        program->code[*ip] = arg;
        *ip += 1;

    }
}

void assembler(const char *file, prog *program) {
    FILE *fp = fopen(file, "w+b");
    assert(fp != nullptr && "coudn't open file");

    fprintf(fp, "%s %d %d\n", SIGNATURE, VERSION, program->NUMBER);

    program->code = (int *) calloc(program->NUMBER * 2, sizeof(int));

    assert(program->code != nullptr && "null pointer");

    
    char cmd[10]; 
    int ip = 0;
    int labl = 0;

    for (int i = 0; i < program->NUMBER; i++) {
        if (sscanf(program->text[i], "%d", &labl) != 0) {
            program->lables[labl] = i;
        } else if (sscanf(program->text[i], "%s", cmd) != 0) {
            if (strcmp(cmd, "push") == 0) {
                program->code[ip++] = PUSH;
                get_args(program, program->text[i], cmd, &ip);
            } else if (strcmp(cmd, "hlt") == 0) {
                program->code[ip++] = HLT;

            } else if (strcmp(cmd, "add") == 0) {
                program->code[ip++] = ADD;

            } else if (strcmp(cmd, "sub") == 0) {
                program->code[ip++] = SUB;

            } else if (strcmp(cmd, "mul") == 0) {
                program->code[ip++] = MUL;

            } else if (strcmp(cmd, "div") == 0) {
                program->code[ip++] = DIV;
            
            } else if (strcmp(cmd, "out") == 0) {
                program->code[ip++] = OUT;

            } else if (strcmp(cmd, "dump") == 0) {
                program->code[ip++] = DUMP;

            } else if (strcmp(cmd, "in") == 0) {
                program->code[ip++] = IN;

            } else if (strcmp(cmd, "dup") == 0) {
                program->code[ip++] = DUP;

            } else if (strcmp(cmd, "jmp") == 0) {
                program->code[ip++] = JMP;
                get_args(program, program->text[i], cmd, &ip);
            } else {
                printf("comand didn't found\n");
            }
        }
    }

    for (int i = 0; i < ip; i++) {
        fprintf(fp, "%d ", program->code[i]);
    }

    printf_listing(program, ip);

    fprintf(fp, "\n");
    fclose(fp);
}

void printf_listing(prog *text_program, int count_cmd) {

    const char *FILE_LISTING = "/mnt/c/Users/User/Desktop/programs/processor/res/listing.txt"; 
    // const char *FILE_LISTING = "C://Users//User//Desktop//programs//processor//res//listing.txt"; 


    FILE *fp = fopen(FILE_LISTING, "w");
    assert(fp != nullptr && "coudn't open file");

    for (int ip = 0; ip < count_cmd; ip++) {
        fprintf(fp, "%05d    ", ip);
        switch (text_program->code[ip])
        {
        case HLT:
            fprintf(fp, "%02x           %s\n", text_program->code[ip], "HLT");
            break;
        case PUSH:
            fprintf(fp, "%02x   ", text_program->code[ip]);
            ip++;
            fprintf(fp, "%02d      %s\n", text_program->code[ip], "PUSH");
            break;
        case (PUSH | (1 << BIT_CONST)):
            fprintf(fp, "%02x   ", text_program->code[ip]);
            ip++;
            fprintf(fp, "%02d      %s\n", text_program->code[ip], "PUSH");
            break;
        case (PUSH | (1 << BIT_RAW)):
            fprintf(fp, "%02x   ", text_program->code[ip]);
            ip++;
            fprintf(fp, "%02d      %s\n", text_program->code[ip], "PUSH");
            break;
        case (PUSH | (1 << BIT_REG)):
            fprintf(fp, "%02x   ", text_program->code[ip]);
            ip++;
            fprintf(fp, "%02d      %s\n", text_program->code[ip], "PUSH");
            break;
        case ADD:
            fprintf(fp, "%02x           %s\n", text_program->code[ip], "ADD");
            break;
        case SUB:
            fprintf(fp, "%02x           %s\n", text_program->code[ip], "SUB");
            break;
        case MUL:
            fprintf(fp, "%02x           %s\n", text_program->code[ip], "MUL");
            break;
        case DIV:
            fprintf(fp, "%02x           %s\n", text_program->code[ip], "DIV");
            break;
        case OUT:
            fprintf(fp, "%02x           %s\n", text_program->code[ip], "OUT");
            break;
        case DUMP:
            fprintf(fp, "%02x           %s\n", text_program->code[ip], "DUMP");
            break;
        case IN:
            fprintf(fp, "%02x           %s\n", text_program->code[ip], "IN");
            break;
        case JMP:
            fprintf(fp, "%02x   ", text_program->code[ip]);
            ip++;
            fprintf(fp, "%02d     %s\n", text_program->code[ip], "JMP");
            break;
        case DUP:
            fprintf(fp, "%02x           %s\n", text_program->code[ip++], "DUP");
            break;      
        default:
            fprintf(fp, "didn't found comand\n");
            break;
        }

    }

    fclose(fp);

}