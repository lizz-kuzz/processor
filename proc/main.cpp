#include "function.hpp"

int main() {
    const char *FILE_ASS_OUTPUT = "/mnt/c/Users/User/Desktop/programs/processor/res/ass_output.txt";

    // const char *FILE_ASS_OUTPUT = "C://Users//User//Desktop//programs//processor//res//ass.output";
    
    prog program = {};
    stack stk = {};

    stack_ctor(stk, 5);
    
    read_file(FILE_ASS_OUTPUT, &program);

    if (check_version(&program) != 0) {
        return 0;
    }

    realization_program(&program, &stk);

    return 0;
}