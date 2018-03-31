#include "sentiment.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vocabulary.h"

#define delimiters  ";'-+/\\_<>|!., "

int EvaluateWord(char * word);
void PrintTableHeader();

void PrintWordEvaluation(WordEvaluation val, char * word, char * prefix);

int EvaluateStatement(char * statement)
{
    int sentenceEvaluation = 0;
    int negationInStatement = 0;

    LoadAllVocabularies();
    
    PrintTableHeader();

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
        printf("\n!! Trovata negazione, il valore complessivo verra' ribaltato !!\n");
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

        if (positive.matchRate > negative.matchRate && 
            positive.matchRate > ignore.matchRate)
        {
            PrintWordEvaluation(positive, word, "[+]");
            return positive.rating;
        }else if (negative.matchRate > positive.matchRate && 
            negative.matchRate > ignore.matchRate)
        {
            PrintWordEvaluation(negative, word, "[-]");
            return (0 - negative.rating);
        }else if (ignore.matchRate > positive.matchRate && 
            ignore.matchRate > negative.matchRate)
        {
            PrintWordEvaluation(ignore, word, "[0]");
        }else{
            WordEvaluation empty = {"",0,0.0};
            empty.word = (char *) malloc(1);
            strcpy(empty.word, "");
            PrintWordEvaluation(empty, word, "[N]");
        }
    }
    return 0;
}

void PrintTableHeader()
{
    printf("%5.5s\t%20.20s\t%20.20s\t%5.5s\t%6.6s\n","Acc.","Parola", "Parola trovata", "Chars","(%)");
    printf("_______________________________________________________________________________\n");
}

void PrintWordEvaluation(WordEvaluation val, char * word, char * prefix)
{
    printf("%5.5s\t%20.20s\t%20.20s\t%5d\t%6.2f\n",prefix,word,val.word, val.rating,val.matchRate);
}
