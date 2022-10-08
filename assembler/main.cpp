#include <stdio.h>
#include "file.hpp"
#include "utils_ass.hpp"
#include "assembler.hpp"
// sistem 
// header size
// if -> swich case
// binfile
// переименовать функции
// listing

int main() {
    prog program = {};
    const char *FILE_PROG = "/mnt/c/Users/User/Desktop/programs/processor/res/ass_input.txt";
    const char *FILE_ASS_OUTPUT = "/mnt/c/Users/User/Desktop/programs/processor/res/ass.output";

    // const char *FILE_PROG = "C://Users//User//Desktop//programs//processor//res//ass_input.txt";
    // const char *FILE_ASS_OUTPUT = "C://Users//User//Desktop//programs//processor//res//ass.output";
    // const char *FILE_DISASS_OUTPUT = "C://Users//User//Desktop//programs//processor//res//disass.output";

    read_file(FILE_PROG, &program);

    assembler(FILE_ASS_OUTPUT, &program);
    
    free(program.code);
    free(program.text);
    free(program.text_buf);
    return 0;
}