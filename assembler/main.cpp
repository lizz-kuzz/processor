#include <stdio.h>
#include "file.hpp"
#include "utils_ass.hpp"
#include "assembler.hpp"

#include <string.h>

int main() {
    prog program = {};

    // const char *FILE_PROG = "/mnt/c/Users/User/Desktop/programs/processor/res/ass_input.txt";
    // const char *FILE_PROG = "/mnt/c/Users/User/Desktop/programs/processor/res/square_equation.txt";
    // const char *FILE_PROG = "/mnt/c/Users/User/Desktop/programs/processor/res/factorial.txt";
    const char *FILE_PROG = "/mnt/c/Users/User/Desktop/programs/processor/res/aaa.txt";

    const char *FILE_ASS_OUTPUT = "/mnt/c/Users/User/Desktop/programs/processor/res/ass.output";
    // system("ls");
    // const char *FILE_PROG = "C://Users//User//Desktop//programs//processor//res//ass_input.txt";
    // const char *FILE_ASS_OUTPUT = "C://Users//User//Desktop//programs//processor//res//ass.output";

    read_file(FILE_PROG, &program);

    compile(FILE_ASS_OUTPUT, &program);
    
    dtor(&program);
  
    return 0;
}