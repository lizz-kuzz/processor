#ifndef UTILS_PROC_HPP_INCLUDED
#define UTILS_PROC_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "../utils.hpp"

#define SIGNATURE "CP"
#define VERSION "3"

#define SIZE_RAW 20
#define SIZE_REG 5

typedef struct {
    char    *text_buf;
    char   **arr_comand;
    int      ram[SIZE_RAW];
    int      reg[SIZE_REG];
    int     *cmd;
    int      NUMBER_OF_CMD;
    int      NUMBER_OF_ROW;
    long int SYMBOLS;
} prog;


#endif