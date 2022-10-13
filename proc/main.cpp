#include "function.hpp"

int main() {
    const char *FILE_ASS_OUTPUT = "/mnt/c/Users/User/Desktop/programs/processor/res/ass.output";

    // const char *FILE_ASS_OUTPUT = "C://Users//User//Desktop//programs//processor//res//ass.output";
    
    prog program = {};
    for (int i = 0; i < 20; i++) {
        program.ram[i] = i;
    }
    program.reg[1] = 5;
    program.reg[2] = 8;
    program.reg[3] = 9;
    program.reg[4] = 33;
    stack stk = {};

    stack_ctor(stk, 5);
    
    read_file(FILE_ASS_OUTPUT, &program);

    if (check_version(&program) != 0) {
        stack_dtor(&stk);
        free_all(&program);
        return 0;
    }

    run_program(&program, &stk);
    free_all(&program);

    return 0;
}