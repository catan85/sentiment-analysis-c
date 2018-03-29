#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RemoveNewLineFromString(char* input);
void AddLineToFile(char* line, char* filename);

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
    printf("%d characters were read.\n", characters);
    RemoveNewLineFromString(buffer);
    printf("You typed: '%s'\n",buffer);

    printf("Scrittura della frase su file");

    char *testFileName;
    strcpy(testFileName, "test.txt");
    
    AddLineToFile(buffer, testFileName);
    AddLineToFile(buffer, testFileName);
    AddLineToFile(buffer, testFileName);

    getchar();

    return(0);
}


void RemoveNewLineFromString(char* input)
{
    int chars = strlen(input);
    chars = chars - 1;
    if (input[chars] == '\n') {
        input[chars] = '\0';
    }
}


void AddLineToFile(char* line, char* filename)
{

    char* temp = (char*)    malloc(strlen(filename) + 1);
    strcpy(temp, filename);
    strcat(temp, ".tmp");

    FILE *fileRead;
    fileRead = fopen( filename , "r");

    FILE *fileWrite;
    fileWrite = fopen( temp, "w");


    fputs(line, fileWrite);

    
    fclose(fileRead);
    fclose(fileWrite);

}