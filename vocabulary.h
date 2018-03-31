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