#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "vocabulary.h"

int equalStrings(char* a, char* b);

int main()
{
    char *buffer;
    size_t bufsize = 100;
    size_t characters;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    printf("Inserire una frase da valutare oppure codificare un inserimento nei dizionari (word==>[+/-/0])\n");
    characters = getline(&buffer,&bufsize,stdin);
    RemoveNewLineFromString(buffer);
    printf("You typed:\n%s\n",buffer);

    // Inserzione nei dizionari
    if (StringContains(buffer,"==>"))
    {

        AddWordToNegativeVocabulary(buffer);

    // Valutazione della frase
    }else{
        printf("Nothing to do\n");
    }

    //AddWordToPositiveVocabulary(buffer);

    //AddWordToIgnoreVocabulary(buffer);
    getchar();

    return(0);
}