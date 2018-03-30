#include <stdlib.h>
#include <string.h>
#include "vocabulary.h"
#include "fileAccess.h"

#define POSITIVE_VOCABULARY_PATH "./data/positive.txt"
#define NEGATIVE_VOCABULARY_PATH "./data/negative.txt"
#define IGNORE_VOCABULARY_PATH "./data/ignore.txt"
#define WORD_BUFFER 50
#define MAX_LINES 100000

// Vocabolari in memoria (per velocizzare l'elaborazione di più parole)
char ** positiveVocabulary;
char ** negativeVocabulary;
char ** ignoreVocabulary;

void AddToVocabulary(char * word, char * vocabularyFile);
void RemoveFromVocabulary(char * word, char * vocabularyFile);
int VocabularyFileContains(char * word, char * vocabularyFile);
void AllocateMemoryToVocabulary(char ** vocabulary);
int VocabularyContains(char * word, char ** vocabulary);


// Functions to add words to vocabularies

void AddWordToPositiveVocabulary(char * word)
{
    AddToVocabulary(word, POSITIVE_VOCABULARY_PATH);
    RemoveFromVocabulary(word, NEGATIVE_VOCABULARY_PATH);
    RemoveFromVocabulary(word, IGNORE_VOCABULARY_PATH);
}

void AddWordToNegativeVocabulary(char * word)
{
    AddToVocabulary(word, NEGATIVE_VOCABULARY_PATH);
    RemoveFromVocabulary(word, POSITIVE_VOCABULARY_PATH);
    RemoveFromVocabulary(word, IGNORE_VOCABULARY_PATH);
}

void AddWordToIgnoreVocabulary(char * word)
{
    AddToVocabulary(word, IGNORE_VOCABULARY_PATH);
    RemoveFromVocabulary(word, POSITIVE_VOCABULARY_PATH);
    RemoveFromVocabulary(word, NEGATIVE_VOCABULARY_PATH);
}

void LoadAllVocabularies()
{

    // LOADING POSITIVE VOCABULARY
    positiveVocabulary = malloc(MAX_LINES * sizeof(char*));
    for (int i = 0; i < MAX_LINES; i++)
    {
        positiveVocabulary[i] = malloc((WORD_BUFFER) * sizeof(char));
    }
    char * vocabularyPath = (char *) malloc(strlen(POSITIVE_VOCABULARY_PATH)+1);
    strcpy(vocabularyPath, POSITIVE_VOCABULARY_PATH);
    LoadVocabularyToMemory(positiveVocabulary, WORD_BUFFER, MAX_LINES, vocabularyPath);

    // LOADING NEGATIVE VOCABULARY
    negativeVocabulary = malloc(MAX_LINES * sizeof(char*));
    for (int i = 0; i < MAX_LINES; i++)
    {
        negativeVocabulary[i] = malloc((WORD_BUFFER) * sizeof(char));
    }
    vocabularyPath = (char *) malloc(strlen(NEGATIVE_VOCABULARY_PATH)+1);
    strcpy(vocabularyPath, NEGATIVE_VOCABULARY_PATH);
    LoadVocabularyToMemory(negativeVocabulary, WORD_BUFFER, MAX_LINES, vocabularyPath);

    // LOADING IGNORED VOCABULARY
    ignoreVocabulary = malloc(MAX_LINES * sizeof(char*));
    for (int i = 0; i < MAX_LINES; i++)
    {
        ignoreVocabulary[i] = malloc((WORD_BUFFER) * sizeof(char));
    }
    vocabularyPath = (char *) malloc(strlen(IGNORE_VOCABULARY_PATH)+1);
    strcpy(vocabularyPath, IGNORE_VOCABULARY_PATH);
    LoadVocabularyToMemory(ignoreVocabulary, WORD_BUFFER, MAX_LINES, vocabularyPath);
}


int PositiveVocabularyFileContains(char * word)
{
    return VocabularyFileContains(word, POSITIVE_VOCABULARY_PATH);
}

int NegativeVocabularyFileContains(char * word)
{
    return VocabularyFileContains(word, NEGATIVE_VOCABULARY_PATH);
}

int IgnoreVocabularyFileContains(char * word)
{
    return VocabularyFileContains(word, IGNORE_VOCABULARY_PATH);
}

int PositiveVocabularyContains(char * word)
{
    return VocabularyContains(word, positiveVocabulary);
}

int NegativeVocabularyContains(char * word)
{
    return VocabularyContains(word, negativeVocabulary);
}

int IgnoreVocabularyContains(char * word)
{
    return VocabularyContains(word, ignoreVocabulary);
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

int VocabularyFileContains(char * word, char * vocabularyFile)
{
    char * destinationFile = (char *) malloc(strlen(vocabularyFile)+1);
    strcpy(destinationFile, vocabularyFile);
    int result = FileContainsLine(word, vocabularyFile);
    free(destinationFile);
    return result;
}

int VocabularyContains(char * word, char ** vocabulary)
{
    for (int i = 0; i < MAX_LINES; i++)
    {
        if (strcmp(word, vocabulary[i])==0)
        {
            return 1;
        }
        if (vocabulary[i]== "")
        {
            return 0;
        }
    }
}

