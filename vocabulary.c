#include <stdlib.h>
#include <string.h>
#include "vocabulary.h"
#include "fileAccess.h"

#define positiveVocabulary "./data/positive.txt"
#define negativeVocabulary "./data/negative.txt"
#define ignoreVocabulary "./data/ignore.txt"

void AddToVocabulary(char * word, char * vocabularyFile);
void RemoveFromVocabulary(char * word, char * vocabularyFile);


// Functions to add words to vocabularies

void AddWordToPositiveVocabulary(char * word)
{
    AddToVocabulary(word, positiveVocabulary);
    RemoveFromVocabulary(word, negativeVocabulary);
    RemoveFromVocabulary(word, ignoreVocabulary);
}

void AddWordToNegativeVocabulary(char * word)
{
    AddToVocabulary(word, negativeVocabulary);
    RemoveFromVocabulary(word, positiveVocabulary);
    RemoveFromVocabulary(word, ignoreVocabulary);
}

void AddWordToIgnoreVocabulary(char * word)
{
    AddToVocabulary(word, ignoreVocabulary);
    RemoveFromVocabulary(word, positiveVocabulary);
    RemoveFromVocabulary(word, negativeVocabulary);
}


void AddToVocabulary(char * word, char * vocabularyFile)
{
    char * destinationFile = (char *) malloc(strlen(vocabularyFile)+1);
    strcpy(destinationFile, vocabularyFile);
    AddLineToFile(word, destinationFile);
    free(destinationFile);
}

void RemoveFromVocabulary(char * word, char * vocabularyFile)
{
    char * destinationFile = (char *) malloc(strlen(vocabularyFile)+1);
    strcpy(destinationFile, vocabularyFile);
    RemoveLineFromFile(word, vocabularyFile);
    free(destinationFile);
}
