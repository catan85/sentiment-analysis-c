#include "sentiment.h"
#include <stdlib.h>
#include <string.h>
#include "vocabulary.h"

#define delimiters  ";'-+/\\_<>|!., "

int EvaluateWord(char * word);

int EvaluateStatement(char * statement)
{
    int sentenceEvaluation = 0;

    LoadAllVocabularies();
    
    // Estrazione delle parole
    char *word;
    char *tokens = malloc(strlen(delimiters)+1);
    strcpy(tokens, delimiters);
    word = strtok(statement, tokens);
    sentenceEvaluation += EvaluateWord(word);
    while (word != NULL) 
    {
        word = strtok(NULL, tokens);
        if (word != NULL)
        {
            sentenceEvaluation += EvaluateWord(word);
        }
    }

    return sentenceEvaluation;
}

int EvaluateWord(char * word)
{
    int p,n,i = 0; 
    p = PositiveVocabularyContains(word);
    n = NegativeVocabularyContains(word);
    i = IgnoreVocabularyContains(word);
    return 0;
}