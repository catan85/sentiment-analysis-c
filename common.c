#include "common.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void RemoveNewLineFromString(char* input)
{
    int chars = strlen(input);
    chars = chars - 1;
    if (input[chars] == '\n') {
        input[chars] = '\0';
    }
}

int StringContains(char * text, char * search)
{
    if (strstr(text,search)==NULL)
    {
        return 0;
    }else{
        return 1;
    }
}

int Max(int a, int b)
{
    if (a>=b){return a;}
    if (b>a){return b;}
}