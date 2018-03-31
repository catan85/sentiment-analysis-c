#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "fileAccess.h"
#include "vocabulary.h"

void AddLineToFile(char* line, char* filename)
{
    char* temp = (char*) malloc(strlen(filename) + 4 + 1);
    strcpy(temp, filename);
    strcat(temp, ".tmp");

    // Creazione degli oggetti file, uno per la lettura del vecchio file ed uno 
    // per la scrittura nel nuovo file temporaneo
    FILE *fileRead;
    fileRead = fopen( filename , "r");
    FILE *fileWrite;
    fileWrite = fopen( temp, "w");

    // Inserimento della linea nel file di destinazione
    fputs(line, fileWrite);
    fputs("\n",fileWrite);

    // Lettura del file di origine e riscrittura delle righe diverse dalla nuova
    int len = 255;
    char *currentLine = malloc(sizeof(char) * len);
    if (fileRead == NULL) {
        printf("File not found\n");
        printf(filename);
        return;
    }
    while(fgets(currentLine, len, fileRead) != NULL) {
        RemoveNewLineFromString(currentLine);
        if (strcmp(currentLine, line) != 0)
        {
            fputs(currentLine, fileWrite);
            fputs("\n",fileWrite);
        }
    }
    free(currentLine);

    fclose(fileRead);
    fclose(fileWrite);

    // Rimuovo il vecchio file e rinomino quello temporaneo
    remove(filename);
    rename(temp,filename);
}

void RemoveLineFromFile(char* line, char* filename)
{
    char* temp = (char*) malloc(strlen(filename) + 4 + 1);
    strcpy(temp, filename);
    strcat(temp, ".tmp");

    // Creazione degli oggetti file, uno per la lettura del vecchio file ed uno 
    // per la scrittura nel nuovo file temporaneo
    FILE *fileRead;
    fileRead = fopen( filename , "r");
    FILE *fileWrite;
    fileWrite = fopen( temp, "w");

    // Lettura del file di origine e riscrittura delle righe diverse dalla nuova
    int len = 255;
    char *currentLine = malloc(sizeof(char) * len);
    if (fileRead == NULL) {
        printf("File not found\n");
        printf(filename);
        return;
    }
    while(fgets(currentLine, len, fileRead) != NULL) {
        RemoveNewLineFromString(currentLine);
        if (strcmp(currentLine, line) != 0)
        {
            fputs(currentLine, fileWrite);
            fputs("\n",fileWrite);
        }
    }
    free(currentLine);

    fclose(fileRead);
    fclose(fileWrite);

    // Rimuovo il vecchio file e rinomino quello temporaneo
    remove(filename);
    rename(temp,filename);
}

int FileContainsLine(char * line, char * filename)
{
    int result = 0;
    FILE *fileRead;
    fileRead = fopen( filename , "r");
    // Lettura del file
    int len = 255;
    char *currentLine = malloc(sizeof(char) * len);
    if (fileRead == NULL) {
        printf("File not found\n");
        printf(filename);
        return 0;
    }
    while(fgets(currentLine, len, fileRead) != NULL) {
        RemoveNewLineFromString(currentLine);
        if (strcmp(currentLine, line) == 0)
        {
            result = 1;
        }
    }
    free(currentLine);
    fclose(fileRead);
    return result;
}

void LoadVocabularyToMemory(char ** vocabulary, int bufferSize, int lines,  char * vocabularyFile )
{
    
    FILE *fileRead;
    fileRead = fopen( vocabularyFile , "r");
    int lineIndex = 0;

    // Lettura del file

    char *currentLine = malloc(sizeof(char) * bufferSize);
    if (fileRead == NULL) {
        printf("File not found\n");
        printf(vocabularyFile);
        return;
    }
    while(fgets(currentLine, bufferSize, fileRead) != NULL) {
        RemoveNewLineFromString(currentLine);
        strcpy(vocabulary[lineIndex],currentLine);
        lineIndex++;
    }
    
    vocabulary[lineIndex][0]=0;
    
    free(currentLine);
    fclose(fileRead);
}
