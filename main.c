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

int main()
{
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
        RemoveNewLineFromString(statement);

        char *vocabEditSplitter = (char*)malloc(strlen(VOCAB_EDIT_KEY)+1);
        strcpy(vocabEditSplitter,VOCAB_EDIT_KEY);

        // Se la frase contiene la stringa di editing (==>) allora esegue VocabularyEditing
        if (StringContains(statement, vocabEditSplitter))
        {
            LaunchVocabularyEditing(statement, vocabEditSplitter);

            // A seguito della modica dei file dei vocabolari li ricarico in memoria
            // Non lo faccio ad ogni frase per avere migliori performance.
            // Prima di caricarli libero la loro memoria per evitare di continuare ad occuparne
            // inutilmente
            FreeAllVocabularies();
            LoadAllVocabularies();

        // Se la stringa inserita non contiene la stringa di editing eseguiamo la sentiment analysis
        }else{
            LaunchSentimentAnalysis(statement);
        }

        free(vocabEditSplitter);
        free(statement);
    }
    return(0);
}

