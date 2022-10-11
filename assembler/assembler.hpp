#ifndef ASSEMBLER_HPP_INCLUDED
#define ASSEMBLER_HPP_INCLUDED

#include "utils_ass.hpp"

void assembler(const char *file, prog *text_program);


char *check_cmd(char *cmd);

void printf_listing(prog *text_program, int count_cmd);

void get_args(prog *program, char *text_cmd, char *cmd, int *ip);
#endif