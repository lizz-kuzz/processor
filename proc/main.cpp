#include "function.hpp"

int main() {
    const char *FILE_ASS_OUTPUT = "/mnt/c/Users/User/Desktop/programs/processor/res/ass.output";

    // const char *FILE_ASS_OUTPUT = "C://Users//User//Desktop//programs//processor//res//ass.output";
    
    prog program = {};
    for (int i = 0; i < 20; i++) {
        program.ram[i] = i;
    }
    program.reg[1] = 0;
    program.reg[2] = 0;
    program.reg[3] = 0;
    program.reg[4] = 0;
    stack stk = {};

    stack_ctor(stk, 1);
    
    read_file(FILE_ASS_OUTPUT, &program);

    if (check_version(&program) != 0) {
        stack_dtor(&stk);
        free_all(&program);
        return 0;
    }

    run_program(&program, &stk);
    for (int i = 0; i <= 4; i++) {
        printf("coef %d\n", program.reg[i]);
    }
    stack_dtor(&stk);
    free_all(&program);


    return 0;
}