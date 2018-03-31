#include <stdlib.h>
#include <string.h>
#include "vocabulary.h"
#include "fileAccess.h"
#include "common.h"

#define POSITIVE_VOCABULARY_PATH "./data/positive.txt"
#define NEGATIVE_VOCABULARY_PATH "./data/negative.txt"
#define IGNORE_VOCABULARY_PATH "./data/ignore.txt"
#define NEGATION_VOCABULARY_PATH "./data/negation.txt"
#define WORD_BUFFER 50
#define MAX_LINES 100000
#define MIN_RATIO 0.7

// Vocabolari in memoria (per velocizzare l'elaborazione di più parole, vengono caricati
// prima di analizzare l'intera frase)
char ** positiveVocabulary;
char ** negativeVocabulary;
char ** ignoreVocabulary;
char ** negationVocabulary;

void AddToVocabulary(char * word, char * vocabularyFile);
void RemoveFromVocabulary(char * word, char * vocabularyFile);
int VocabularyFileContains(char * word, char * vocabularyFile);
void AllocateMemoryToVocabulary(char ** vocabulary);
int VocabularyContains(char * word, char ** vocabulary);
WordEvaluation VocabolaryEvaluate(char * word, char ** vocabulary);

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


WordEvaluation PositiveVocabularyEvaluation(char * word)
{
    return VocabolaryEvaluate(word, positiveVocabulary);
}

WordEvaluation NegativeVocabularyEvaluation(char * word)
{
    return VocabolaryEvaluate(word, negativeVocabulary);
}

WordEvaluation IgnoreVocabularyEvaluation(char * word)
{
    return VocabolaryEvaluate(word, ignoreVocabulary);
}

int NegationVocabularyContains(char * word)
{
    VocabularyContains(word, negationVocabulary);
}

WordEvaluation VocabolaryEvaluate(char * word, char ** vocabulary)
{
    int bestWordRating = 0;
    char bestWord[WORD_BUFFER];

    for (int l = 0; l < MAX_LINES; l++)
    {
        int correspondingChars = 0;
        for (int c = 0; c < strlen(word); c++ )
        {
            if (word[c] == vocabulary[l][c])
            {
                correspondingChars++;
            }else{
                break;
            }
        }

        // Il 70% della lunghezza della parola trovata deve essere più corto della parola cercata
        // se trovo una stringa molto lunga che inizia con una corrispondenza esatta (o quasi) va ignorata perchè la
        // parte successiva potrebbe cambiare significato alla parola
        if (correspondingChars > bestWordRating &&
            (strlen(vocabulary[l]) * MIN_RATIO) < strlen(word))
        {
            bestWordRating = correspondingChars;
            strcpy(bestWord, vocabulary[l]);
        }else if (strcmp(word, vocabulary[l])==0)
        {
            // la corrispondenza esatta ha la meglio su quelle più lunghe
            bestWordRating = correspondingChars;
            strcpy(bestWord, vocabulary[l]);
            break;
        }

        if (vocabulary[l][0]==0)
        {
            break;
        }

    }

    WordEvaluation result = { "", 0, 0.0 };
    result.word = (char *) malloc(WORD_BUFFER);

    // la corrispondenza trovata deve avere almeno il 70% dei caratteri della parola cercata
    if ((bestWordRating >= (strlen(word) * MIN_RATIO))) 
    {
        strcpy(result.word, bestWord);
        result.rating = bestWordRating;
        int maxLength = Max(strlen(bestWord), strlen(word));
        result.matchRate = result.rating * 100 / maxLength;
    }

    return result;
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



