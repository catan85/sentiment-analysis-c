/*
*   sentiment.h
*
*   Questo modulo ha lo scopo di lanciare la sentiment analisi su una frase
*   passata in ingresso
*
*/

// La struttura WordEvaluation viene utilizzata per valutare la corrispondenza di una certa 
// parola sui vocabolari
typedef struct WordEvaluation
{ 
    char * word;            // word è la parola corrispondente
    int rating;             // rating è un valore che indica il valore di questa corrispondenza (coincide con il numero di caratteri)
    double matchRate;       // matchRate è un valore da 0 a 100 che indica la percentuale di corrispondenza tra la parola in ingresso e quella trovata.
} WordEvaluation;

// metodo per eseguire la sentiment analysis su una frase
void LaunchSentimentAnalysis(char * statement);