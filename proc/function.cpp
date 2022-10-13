#include "function.hpp"

#define HEADER_SIZE 2

#define MASK_CMD       0x1f
#define MASK_ARG_REG   0x40
#define MASK_ARG_RAM   0x80
#define MASK_ARG_IMMED 0x20


void read_file(const char *TEXT, prog *text) {
    FILE *file = fopen(TEXT, "r");

    assert(file != nullptr && "coudn't open file");

    if (file == NULL)
        printf("Could not open file.\n");
    
    text->SYMBOLS = count_symbols(file);

    text->text_buf = (char *) calloc(text->SYMBOLS + 1, sizeof(char)); 

    assert(text->text_buf != nullptr && "null pointer");

    fread(text->text_buf, sizeof(char), text->SYMBOLS, file);

    fclose(file);

    program_text_normalize(text);
}

int num_of_rows(char *text)  {
    int count = 0;
    char *point = text;

    while (*point != '\0')  {
        if (*point == '\n' || *point == ' ')
            count++;
        point++;
    }
    return count;
}

long int count_symbols(FILE *file)  {
    fseek(file, 0, SEEK_END);
    
    long int number = ftell(file);

    fseek(file, 0, SEEK_SET);

    return number;
}

void program_text_normalize(prog *text)  {
    assert(text != nullptr && "null pointer");

    text->NUMBER_OF_ROW = num_of_rows(text->text_buf);
   
    char *point = text->text_buf;
    text->arr_comand = (char **) calloc(text->NUMBER_OF_ROW + 1, sizeof(char *));

    assert(text->arr_comand != nullptr && "null pointer");

    text->arr_comand[0] = point;

    for (int i = 1; (i <= text->NUMBER_OF_ROW) && *(point) != '\0'; point++)  { 
        if (*point == '\n' || *point == ' ')  {
            *point = '\0';
            text->arr_comand[i] = point + 1;
            i++;
        }
    }
}


int check_version(prog *program) {
    assert(program != nullptr && "null pointer");
    
    if (strcmp(program->arr_comand[0], SIGNATURE) != 0) {
        printf("the signature does not match, it is impossible to execute the program\n");
        return 1;
    }
    if (strcmp(program->arr_comand[1], VERSION) != 0) {
        printf("the processor does not support this version of the program, buy coffee to the developer or a new processor\n");
        return 1;
    }
    program->NUMBER_OF_CMD = atoi(program->arr_comand[2]);

    return 0;
}

void create_cmd(prog *program) {
    assert(program != nullptr && "null pointer");
    int ip = 0;
    program->cmd = (int *) calloc(program->NUMBER_OF_ROW, sizeof(int));
    for (int i = HEADER_SIZE + 1; i < program->NUMBER_OF_ROW - 1; i++) {
        sscanf(program->arr_comand[i], "%d", &program->cmd[ip]);
        ip++;
    }
}
int get_arg(prog *program, int cmd, int *ip) {
    assert(program != nullptr && "null pointer");
    int arg = 0;
        *ip += 1;
    
    if (cmd & MASK_ARG_IMMED) {
        arg += program->cmd[*ip];
    }
    if (cmd & MASK_ARG_REG) {
        arg += program->reg[program->cmd[*ip]];
    }
    if (cmd & MASK_ARG_RAM) {
        arg = program->ram[arg];
    }
    // printf("%d\n", arg);
    // *ip+= 1;
    return arg;

}
void run_program(prog *program, stack *stk) {
    assert(program != nullptr && "null pointer");

    create_cmd(program);

    for (int ip = 0; ip < program->NUMBER_OF_ROW; ip++) {
        switch (program->cmd[ip] & MASK_CMD)
        {
        case HLT: {
            stack_dtor(stk);
            break;
        }
        case PUSH: {
            int arg = get_arg(program, program->cmd[ip], &ip);
            stack_push(stk, arg);
            break;
        }
        case ADD: {
            int a = stack_pop(stk);
            int b = stack_pop(stk);
            stack_push(stk, a + b);    
            break;
        }
        case SUB: {
            int a = stack_pop(stk);
            int b = stack_pop(stk);

            stack_push(stk, a - b);  
            break;
        }
        case MUL: {
            int a = stack_pop(stk);
            int b = stack_pop(stk);
            stack_push(stk, a * b);  
            break;
        }
        case DIV: {
            int a = stack_pop(stk);
            int b = stack_pop(stk);
            stack_push(stk, b / a);  
            break;
        }
        case OUT: {
            int a = stack_pop(stk);
            printf("result %d\n", a);
            break;
        }
        case IN: {
            int a = 0;
            scanf("%d", &a);
            stack_push(stk, a);
            break;
        }  
        case JMP: {
            ip++;
            int a = program->cmd[ip];
            ip = a;
            break;
        }
        case DUP: {
            int a = stack_pop(stk);
            stack_push(stk, a);
            stack_push(stk, a);
            break;
        }
        default:
            printf("comand didn't found");
            break;
        }
    }
}

void free_all(prog *program) {
    assert(program != nullptr && "null pointer"); 
    free(program->arr_comand);
    free(program->cmd);
    free(program->text_buf);
}