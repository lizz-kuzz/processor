#include "assembler.hpp"
#include "file.hpp"

#define LEN_ARR_LABLES 10

void assembler(const char *file, prog *text_program) {
    FILE *fp = fopen(file, "w+b");
    assert(fp != nullptr && "coudn't open file");

    fprintf(fp, "%s %d %d\n", SIGNATURE, VERSION, text_program->NUMBER);

    text_program->code = (int *) calloc(text_program->NUMBER * 2, sizeof(int));

    assert(text_program->code != nullptr && "null pointer");

    int lables[LEN_ARR_LABLES] = {0};
    char cmd[10]; 
    int ip = 0;
    int len = 0;
    int labl = 0;
    for (int i = 0; i < text_program->NUMBER; i++) {
        if (sscanf(text_program->text[i], "%d", &labl) != 0) {
            // printf("%d", ip);
            lables[labl] = i;
        } else {
        sscanf(text_program->text[i], "%s%n", cmd, &len);


        if (strncmp(cmd, "push", 4) == 0) {
            text_program->code[ip++] = PUSH;
            text_program->text[i] += len;

            int arg = 0;
            // char mem_arg[10];
            if (sscanf(text_program->text[i], "%d", &arg) != 0) {
                text_program->code[ip++] = arg;
            }
            // } else if (sscanf(text_program->text[i], "%s", mem_arg) != 0) {
            //     if (strncmp(mem_arg, "r", 1) == 0) {

            //     }
            // }

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

        } else if (strncmp(cmd, "dup", 3) == 0) {
            text_program->code[ip++] = DUP;

        } else if (strncmp(cmd, "jmp", 3) == 0) {
            text_program->code[ip++] = JMP;
            text_program->text[i] += len + 1;

            int arg = 0;
            if (sscanf(text_program->text[i], "%d", &arg) != 0) {
                text_program->code[ip++] = arg;
            } else if (*text_program->text[i] == ':') {
                text_program->text[i]++;
                sscanf(text_program->text[i], "%d", &labl);
                text_program->code[ip++] = lables[labl];
            }
        } else {
            printf("comand didn't found\n");
        }
        }
    }

    printf("%d", ip);
    for (int i = 0; i < ip; i++) {
        fprintf(fp, "%d ", text_program->code[i]);
    }

    printf_listing(text_program, ip);

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