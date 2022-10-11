#ifndef UTILS_ASS_HPP_INCLUDED
#define UTILS_ASS_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "../utils.hpp"

#define SIGNATURE "CP"
#define VERSION 3
#define LEN_ARR_LABLES 10


typedef struct {
    char    *text_buf;
    char   **text;
    int      lables[LEN_ARR_LABLES];
    int     *code;
    int      NUMBER;
    long int SYMBOLS;
} prog;


#endif