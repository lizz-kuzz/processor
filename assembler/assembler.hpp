#ifndef ASSEMBLER_HPP_INCLUDED
#define ASSEMBLER_HPP_INCLUDED

#include "utils_ass.hpp"

void assembler(const char *file, prog *text_program);

void disassembler(const char *file_input, const char *file_output);

char *check_cmd(char *cmd);
#endif