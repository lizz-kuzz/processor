#ifndef UTILS_ASS_HPP_INCLUDED
#define UTILS_ASS_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define SIGNATURE "CP"
#define VERSION 2

typedef struct {
    char    *text_buf;
    char   **text;
    int      NUMBER;
    long int SYMBOLS;
} prog;


enum comand_ass { 
    HLT   = '0',
    PUSH  = '1',
    ADD   = '2',
    SUB   = '3',
    MUL   = '4',
    DIV   = '5',
    OUT   = '6',
    DUMP  = '7',
    IN    = '8',
};

#endif