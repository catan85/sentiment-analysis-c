#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "vocabulary.h"
#include "sentiment.h"

#define VOCAB_EDIT_KEY "==>"
#define STATEMENT_BUFFER 255

int equalStrings(char* a, char* b);

void VocabularyEditing(char * statement, char * vocabEditSplitter);
void SentimentAnalysis(char * statement);
void PrintBanner();

int main()
{
    PrintBanner();

    // All'avvio si caricano tutti i vocabolari in memoria
    LoadAllVocabularies();
    
    while(1)
    {
        char *statement;
        size_t characters;
        size_t bufsize = STATEMENT_BUFFER;

        statement = (char *)malloc(STATEMENT_BUFFER * sizeof(char));
        if( statement == NULL)
        {
            perror("Unable to allocate statement");
            exit(1);
        }

        printf("Inserisci una frase / modifica un dizionario (sintassi: [parola]==>[+/-/0])\n");
        characters = getline(&statement, &bufsize, stdin);
        printf("\n");
        RemoveNewLineFromString(statement);

        // Se la frase contiene la stringa di editing (==>) allora esegue VocabularyEditing
        if (StringContains(statement, VOCAB_EDIT_KEY))
        {
            char *vocabEditSplitter = (char*)malloc(strlen(VOCAB_EDIT_KEY)+1);
            strcpy(vocabEditSplitter,VOCAB_EDIT_KEY);
            LaunchVocabularyEditing(statement, vocabEditSplitter);

            // A seguito della modica dei file dei vocabolari li ricarico in memoria
            // Non lo faccio ad ogni frase per avere migliori performance.
            // Prima di caricarli libero la loro memoria per evitare di continuare ad occuparne
            // inutilmente
            FreeAllVocabularies();
            LoadAllVocabularies();

            free(vocabEditSplitter);
        // Se la stringa inserita non contiene la stringa di editing eseguiamo la sentiment analysis
        }else{
            LaunchSentimentAnalysis(statement);
        }

        if (StringContains(statement,"/q"))
        {
            return(0);
        }

        
        free(statement);
    }
    return(0);
}

void PrintBanner()
{
    printf("\n");
    printf("    -----------------------------------------------------------------\n");
    printf("    |                                                               |\n");
    printf("    |    Sentiment Analysis     1.0                                 |\n");
    printf("    |    Author:                Andrea Cattaneo M.909227            |\n");
    printf("    |    Date:                  31/03/2018                          |\n");
    printf("    |                                                               |\n");
    printf("    -----------------------------------------------------------------\n");
    printf("\n\n");
    printf("Enter '/q' to quit.. \n\n\n");
}
