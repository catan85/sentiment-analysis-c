#include "sentiment.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vocabulary.h"
#include "common.h"

#define MIN_RATIO 0.7
#define delimiters  ";'-+/\\_<>|!., "


int EvaluateStatement(char* statement);
int EvaluateWord(char * word);

WordEvaluation VocabolaryEvaluate(char * word, char ** vocabulary);
WordEvaluation PositiveVocabularyEvaluation(char * word);
WordEvaluation NegativeVocabularyEvaluation(char * word);
WordEvaluation IgnoreVocabularyEvaluation(char * word);

void PrintTableHeader();
void PrintWordEvaluation(WordEvaluation val, char * word, char * prefix);


void LaunchSentimentAnalysis(char * statement)
{
    int sentenceEvaluation = EvaluateStatement(statement);
    printf("\n\n");
    printf("Valutazione della frase inserita: \n");
    printf("%d\n\n",sentenceEvaluation);
    if (sentenceEvaluation > 0)
    {
        printf("[Sentiment positivo  ]\n");
    }else if (sentenceEvaluation == 0)
    {
        printf("[Sentiment neutro    ]\n");
    }else{
        printf("[Sentiment negativo  ]\n");
    }
    printf("\n\n");
}

int EvaluateStatement(char * statement)
{
    int sentenceEvaluation = 0;
    int negationInStatement = 0;

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
            (strlen(vocabulary[l]) * MIN_RATIO) < correspondingChars)
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
    if ((bestWordRating > (strlen(word) * MIN_RATIO))) 
    {
        strcpy(result.word, bestWord);
        result.rating = bestWordRating;
        int maxLength = Max(strlen(bestWord), strlen(word));
        result.matchRate = result.rating * 100.0 / maxLength;
    }

    return result;
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
