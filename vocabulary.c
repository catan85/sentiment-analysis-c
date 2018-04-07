#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vocabulary.h"
#include "fileAccess.h"
#include "common.h"
#define MEMORY_DEALLOCATION 1 // Se sono in debug la deallocazione è molto lenta, la lascio impostabile
#define POSITIVE_VOCABULARY_PATH "./data/positive.txt"
#define NEGATIVE_VOCABULARY_PATH "./data/negative.txt"
#define IGNORE_VOCABULARY_PATH "./data/ignore.txt"
#define NEGATION_VOCABULARY_PATH "./data/negation.txt"

// Vocabolari in memoria (per velocizzare l'elaborazione di più parole, vengono caricati
// prima di analizzare l'intera frase)
char ** positiveVocabulary;
char ** negativeVocabulary;
char ** ignoreVocabulary;
char ** negationVocabulary;



// Aggiunta e modifica di parole sui vocabolari
void AddWordToPositiveVocabulary(char* word);
void AddWordToNegativeVocabulary(char* word);
void AddWordToIgnoreVocabulary(char* word);
void AddToVocabulary(char * word, char * vocabularyFile);
void RemoveFromVocabulary(char * word, char * vocabularyFile);
int VocabularyFileContains(char * word, char * vocabularyFile);
int VocabularyContains(char * word, char ** vocabulary);

void FreeVocabulary(char ** vocabulary);

void LaunchVocabularyEditing(char * statement, char * vocabEditSplitter)
{
    // Inserzione nei dizionari

    // Estrazione delle parole
    char *word = (char*)malloc(WORD_BUFFER);
    char *destination = (char*)malloc(2);
    char *current;
    current = strtok(statement, vocabEditSplitter);
    int i = 0;
    while (current != NULL) 
    {
        if (i==0)
        {
            strcpy(word,current);
        }else if (i==1)
        {
            destination[0] = current[0];
            destination[1] = 0;
        }
        i++;
        current = strtok(NULL, vocabEditSplitter);
    }

    free(destination);
    free(word);

    if (StringContains(destination,"+"))
    {
        printf("Aggiunta al vocabolario delle parole positive..\n");
        AddWordToPositiveVocabulary(word);
    }else if(StringContains(destination, "-"))
    {
        printf("Aggiunta al vocabolario delle parole negative..\n");
        AddWordToNegativeVocabulary(word);
    }else if(StringContains(destination, "0"))
    {
        printf("Aggiunta al vocabolario delle parole da ignorare..\n");
        AddWordToIgnoreVocabulary(word);
    }else{
        printf("Errore: attributo non riconosciuto.\n\n\n");
        return;
    }

    printf("Editing vocabolari completato.\n");
    printf("\n\n");

}



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


    // LOADING NEGATION VOCABULARY
    negationVocabulary = malloc(MAX_LINES * sizeof(char*));
    for (int i = 0; i < MAX_LINES; i++)
    {
        negationVocabulary[i] = malloc((WORD_BUFFER) * sizeof(char));
    }
    vocabularyPath = (char *) malloc(strlen(NEGATION_VOCABULARY_PATH)+1);
    strcpy(vocabularyPath, NEGATION_VOCABULARY_PATH);
    LoadVocabularyToMemory(negationVocabulary, WORD_BUFFER, MAX_LINES, vocabularyPath);
}

void FreeAllVocabularies()
{
    if (MEMORY_DEALLOCATION)
    {
        FreeVocabulary(positiveVocabulary);
        FreeVocabulary(negativeVocabulary);
        FreeVocabulary(ignoreVocabulary);
        FreeVocabulary(negationVocabulary);
    }
}

void FreeVocabulary(char ** vocabulary)
{
    for (int i = 0; i < MAX_LINES; i++)
    {
        free(vocabulary[i]);
    }
    free(vocabulary);
}

int NegationVocabularyContains(char * word)
{
    VocabularyContains(word, negationVocabulary);
}

int VocabularyContains(char * word, char ** vocabulary)
{
    for (int l = 0; l < MAX_LINES; l++)
    {
        if (strcmp(vocabulary[l],word)==0)
        {
            return 1;
        }
        if (vocabulary[l][0]==0)
        {
            return 0;
        }
    }
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
