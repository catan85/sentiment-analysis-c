#include "sentiment.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vocabulary.h"

#define delimiters  ";'-+/\\_<>|!., "

int EvaluateWord(char * word);
void PrintWordEvaluation(WordEvaluation val, char * word, char * prefix);

int EvaluateStatement(char * statement)
{
    int sentenceEvaluation = 0;
    int negationInStatement = 0;

    LoadAllVocabularies();
    
    // Estrazione delle parole
    char *word;
    char *tokens = malloc(strlen(delimiters)+1);
    strcpy(tokens, delimiters);

    word = strtok(statement, tokens);    
    while (word != NULL) 
    {
        if (NegationVocabularyContains(word)==1)
        {
            negationInStatement = 1;
        }else{
            sentenceEvaluation += EvaluateWord(word);
        }
        word = strtok(NULL, tokens);
    }
    
    if (negationInStatement == 0)
    {
        return sentenceEvaluation;
    }else{
        return 0 -  sentenceEvaluation;
    }
    
}


int EvaluateWord(char * word)
{
    
    if (word != NULL)
    {
        WordEvaluation positive,negative,ignore; 
        positive = PositiveVocabularyEvaluation(word);
        negative = NegativeVocabularyEvaluation(word);
        ignore = IgnoreVocabularyEvaluation(word);

        if (positive.rating > negative.rating && 
            positive.rating > ignore.rating)
        {
            PrintWordEvaluation(positive, word, "[+]");
            return positive.rating;
        }else if (negative.rating > positive.rating && 
            negative.rating > ignore.rating)
        {
            PrintWordEvaluation(negative, word, "[-]");
            return (0 - negative.rating);
        }else if (ignore.rating > positive.rating && 
            ignore.rating > negative.rating)
        {
            PrintWordEvaluation(ignore, word, "[0]");
        }else{
            printf("[N]\t");
            printf("%20.20s", word);
            printf("\t%20.20s\t0\n", "NOT_FOUND");
        }

    }

    return 0;
}

void PrintWordEvaluation(WordEvaluation val, char * word, char * prefix)
{
    printf(prefix);
    printf("\t");
    printf("%20.20s",word);
    printf("\t");
    printf("%20.20s",val.word);
    printf("\t");
    printf("%d", val.rating);
    printf("\n");
}
