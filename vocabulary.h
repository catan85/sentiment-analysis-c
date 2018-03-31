#define WORD_BUFFER 50
#define MAX_LINES 100000


// Aggiunta e modifica di parole sui vocabolari
void AddWordToPositiveVocabulary(char* word);
void AddWordToNegativeVocabulary(char* word);
void AddWordToIgnoreVocabulary(char* word);


// Caricamento in memoria dei dizionari
void LoadAllVocabularies();

// valutazione parole da memoria

int NegationVocabularyContains(char * word);

extern char ** positiveVocabulary;
extern char ** negativeVocabulary;
extern char ** ignoreVocabulary;