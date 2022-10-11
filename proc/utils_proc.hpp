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



typedef struct {
    char    *text_buf;
    char   **arr_comand;
    int     *cmd;
    int      NUMBER_OF_CMD;
    int      NUMBER_OF_ROW;
    long int SYMBOLS;
} prog;


#endif