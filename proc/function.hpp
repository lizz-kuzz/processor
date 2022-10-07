#ifndef FUNCTION_HPP_INCLUDED
#define FUNCTION_HPP_INCLUDED
#include "utils_proc.hpp"
#include "stack.hpp"
#include "debug.hpp"

int      check_version(prog *program);

void     create_arr_cmd(prog *text);

void     realization_program(prog *program, stack *stk);

long int count_symbols  (FILE *file);

int      num_of_rows    (char *text);

void     read_file      (const char *TEXT, prog *text);

void     text_normalize (prog *text);
#endif
