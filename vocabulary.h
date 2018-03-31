/*
*   vocabylary.h
*
*   Lo scopo di questo modulo è quello di caricare dei file di vocabolari in memoria a partire da file esterni (txt)
*   Oltre a questo permette l'aggiunta e la rimozione di parole dai dizionari.
*   Viene anche fornito un metodo che permette di verificare se il dizionario delle negazioni contiene delle parole esatte
*   Espone i dizionari in modo che il blocco di analisi possa accedervi per valutare le corrispondenze con delle parole cercate
*/

#define WORD_BUFFER 50
#define MAX_LINES 100000

void LaunchVocabularyEditing(char * statement, char * vocabEditSplitter);

// Caricamento in memoria dei dizionari
void LoadAllVocabularies();
void FreeAllVocabularies();

// valutazione parole da memoria

int NegationVocabularyContains(char * word);

extern char ** positiveVocabulary;
extern char ** negativeVocabulary;
extern char ** ignoreVocabulary;