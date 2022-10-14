#ifndef ASSEMBLER_HPP_INCLUDED
#define ASSEMBLER_HPP_INCLUDED

#include "utils_ass.hpp"

void compail(const char *file, prog *text_program);

void printf_listing(prog *text_program, int count_cmd);

void get_args(prog *program, char *text_cmd, char *cmd, int *ip);

void my_strcpy_for_lable(char *text_for_cpy, char *text);

#endif