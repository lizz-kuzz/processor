#include "assembler.hpp"
#include "file.hpp"

#define MASK_CMD    0x1f
#define BIT_CONST   5
#define BIT_REG     6
#define BIT_RAM     7

void get_args(prog *program, char *text_cmd, char *cmd, int *ip) {

    if (strcmp(cmd, "PUSH") == 0) {
        text_cmd += strlen(cmd) + 1;
        *ip -= 1;

        int arg = 0;
        char arg_reg_ram[10];

        if (sscanf(text_cmd, "%s", arg_reg_ram) != 0) {
            if (strncmp(arg_reg_ram, "[", 1) == 0) {
            program->code[*ip] = program->code[*ip] | (1 << BIT_RAM);
            text_cmd++;
            }
        }
        if (sscanf(text_cmd, "%s", arg_reg_ram) != 0) {
            if (strncmp(arg_reg_ram, "rax", 3) == 0) {
                program->code[*ip] = program->code[*ip] | (1 << BIT_REG);
                arg = 1;
            } else if (strncmp(arg_reg_ram, "rbx", 3) == 0) {
                program->code[*ip] = program->code[*ip] | (1 << BIT_REG);
                arg = 2;
            } else if (strncmp(arg_reg_ram, "rcx", 3) == 0) {
                program->code[*ip] = program->code[*ip] | (1 << BIT_REG);
                arg = 3;
            } else if (strncmp(arg_reg_ram, "rdx", 3) == 0) {
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

    } else if (strncmp(cmd, "J", 1) == 0) {
        printf("kjhg");
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

#define DEF_CMD(cmd_name, number_cmd, args, ...)                        \
    if (strcmp(cmd, #cmd_name) == 0) {                                  \
        program->code[ip++] = number_cmd;                               \
        if (args) get_args(program, program->text[i], cmd, &ip);        \
    } else


void compail(const char *file, prog *program) {
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
            program->lables[labl] = ip;
        } else if (sscanf(program->text[i], "%s", cmd) != 0) {

            #include "/mnt/c/Users/User/Desktop/programs/processor/config.hpp"
            /*else*/ printf("comand didn't found\n");
        
        }
    }

    for (int i = 0; i < ip; i++) {
        fprintf(fp, "%d ", program->code[i]);
    }

    printf_listing(program, ip);

    fprintf(fp, "\n");
    fclose(fp);
}
#undef DEF_CMD


#define DEF_CMD(cmd_name, number_cmd, args, ...)                                        \
    case cmd_name:                                                                      \
        fprintf(fp, "%02x", text_program->code[ip]);                                    \
        if (args)  {                                                                    \
            ip++;                                                                       \
            fprintf(fp, "%10d %20s\n", text_program->code[ip], #cmd_name);              \
        } else  {                                                                       \
            fprintf(fp, "%30s\n", #cmd_name); }                                         \
        break;                                                                          \
    


void printf_listing(prog *text_program, int count_cmd) {

    const char *FILE_LISTING = "/mnt/c/Users/User/Desktop/programs/processor/res/listing.txt"; 
    // const char *FILE_LISTING = "C://Users//User//Desktop//programs//processor//res//listing.txt"; 


    FILE *fp = fopen(FILE_LISTING, "w");
    assert(fp != nullptr && "coudn't open file");

    for (int ip = 0; ip < count_cmd; ip++) {
        fprintf(fp, "%05d    ", ip);
        switch (text_program->code[ip] & MASK_CMD)
        {
            #include "/mnt/c/Users/User/Desktop/programs/processor/config.hpp"      
        default:
            fprintf(fp, "didn't found comand\n");
            break;
        }

    }

    fclose(fp);

}

#undef DEF_CMD