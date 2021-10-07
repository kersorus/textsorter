#ifndef _TEXT_H_
#define _TEXT_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <wctype.h>

//*************************************************************************************************

typedef struct String
{
    wchar_t *str;
    size_t slen;
}Str;

//*************************************************************************************************

typedef struct File
{
    wchar_t *buf;
    char *buf_char;
    FILE *text;
    size_t nstr;
    size_t size;
    Str *strs;    
}File;

//*************************************************************************************************

int isalpha_ru    (wchar_t letter);
int line_chk      (wchar_t *line);
int decode        (File *file);
int opener        (File *file, int argc, char **argv);
void str_data     (File *file);
void get_file     (File *file);
void print_file   (File *file, char *name, int param);
wchar_t *formater (wchar_t *str_start);

//*************************************************************************************************

#endif
