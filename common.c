#include "common.h"
#include <string.h>

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

