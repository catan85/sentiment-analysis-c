
typedef struct WordEvaluation
{ 
    char * word;
    int correspondingChars;
    double matchRate;
} WordEvaluation;

// Aggiunta e modifica di parole sui vocabolari
void AddWordToPositiveVocabulary(char* word);
void AddWordToNegativeVocabulary(char* word);
void AddWordToIgnoreVocabulary(char* word);


// ricerca parola da file
/*
int PositiveVocabularyFileContains(char * word);
int NegativeVocabularyFileContains(char * word);
int IgnoreVocabularyFileContains(char * word);
*/
// Caricamento in memoria dei dizionari
void LoadAllVocabularies();

// valutazione parole da memoria
WordEvaluation PositiveVocabularyEvaluation(char * word);
WordEvaluation NegativeVocabularyEvaluation(char * word);
WordEvaluation IgnoreVocabularyEvaluation(char * word);