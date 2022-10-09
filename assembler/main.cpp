#include <stdio.h>
#include "file.hpp"
#include "utils_ass.hpp"
#include "assembler.hpp"

int main() {
    prog program = {};
    const char *FILE_PROG = "/mnt/c/Users/User/Desktop/programs/processor/res/ass_input.txt";
    const char *FILE_ASS_OUTPUT = "/mnt/c/Users/User/Desktop/programs/processor/res/ass.output";

    // const char *FILE_PROG = "C://Users//User//Desktop//programs//processor//res//ass_input.txt";
    // const char *FILE_ASS_OUTPUT = "C://Users//User//Desktop//programs//processor//res//ass.output";

    read_file(FILE_PROG, &program);

    // char cmd[20];
    // int n = 0;
    // int k = 0;
    // sscanf("4:", "%d%n", &k, &n);
    // printf("%d\n%d", k, n);
 
    assembler(FILE_ASS_OUTPUT, &program);
    
    free(program.code);
    free(program.text);
    free(program.text_buf);
    return 0;
}