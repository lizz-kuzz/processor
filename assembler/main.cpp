#include <stdio.h>
#include "file.hpp"
#include "utils_ass.hpp"
#include "assembler.hpp"

#include <string.h>

int main() {
    prog program = {};
    program.lables[10] = {-1};
    const char *FILE_PROG = "/mnt/c/Users/User/Desktop/programs/processor/res/ass_input.txt";
    const char *FILE_ASS_OUTPUT = "/mnt/c/Users/User/Desktop/programs/processor/res/ass.output";

    // const char *FILE_PROG = "C://Users//User//Desktop//programs//processor//res//ass_input.txt";
    // const char *FILE_ASS_OUTPUT = "C://Users//User//Desktop//programs//processor//res//ass.output";

    read_file(FILE_PROG, &program);
    printf("%d", strcmp("push", "PUSH"));
    compail(FILE_ASS_OUTPUT, &program);
    compail(FILE_ASS_OUTPUT, &program);

    free(program.code);
    free(program.text);
    free(program.text_buf);
    return 0;
}