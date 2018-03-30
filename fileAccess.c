#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "fileAccess.h"

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