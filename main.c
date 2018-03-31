#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "vocabulary.h"
#include "sentiment.h"

#define vocabDelimiter "==>"

int equalStrings(char* a, char* b);

int main()
{
    while(1)
    {
        char *statement;
        size_t bufsize = 100;
        size_t characters;

        statement = (char *)malloc(bufsize * sizeof(char));
        if( statement == NULL)
        {
            perror("Unable to allocate statement");
            exit(1);
        }

        printf("Inserisci una frase / modifica un dizionario (sintassi: [parola]==>[+/-/0])\n");
        characters = getline(&statement,&bufsize,stdin);
        RemoveNewLineFromString(statement);
        printf("Hai scritto:\n%s\n",statement);
        printf("\n");
        // Inserzione nei dizionari
        char *vocDelimTokens = (char*)malloc(strlen(vocabDelimiter)+1);
        strcpy(vocDelimTokens,vocabDelimiter);
        if (StringContains(statement,vocDelimTokens))
        {
            // Estrazione delle parole
            char *word = (char*)malloc(bufsize);
            char *destination = (char*)malloc(2);

            char *current;
            current = strtok(statement, vocDelimTokens);
            strcpy(word,current);
            int i = 0;
            while (current != NULL) 
            {
                current = strtok(NULL, vocDelimTokens);
                if (i==0)
                {
                    destination[0] = current[0];
                    destination[1] = 0;
                }
                i++;
            }

            if (StringContains(destination,"+"))
            {
                printf("Adding to positive dictionary\n");
                AddWordToPositiveVocabulary(word);
            }else if(StringContains(destination, "-"))
            {
                printf("Adding to negative dictionary\n");
                AddWordToNegativeVocabulary(word);
            }else if(StringContains(destination, "0"))
            {
                printf("Adding to ignore dictionary\n");
                AddWordToIgnoreVocabulary(word);
            }
            free(destination);
            free(word);
            printf("Vocabolari aggiornati.\n");
            printf("\n\n");
        
        // Valutazione del sentiment della frase
        }else{
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

        free(vocDelimTokens);
        free(statement);
    }
    return(0);
}