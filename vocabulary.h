
typedef struct WordEvaluation
{ 
    char * word;
    int rating;
    double matchRate;
} WordEvaluation;

// Aggiunta e modifica di parole sui vocabolari
void AddWordToPositiveVocabulary(char* word);
void AddWordToNegativeVocabulary(char* word);
void AddWordToIgnoreVocabulary(char* word);


// Caricamento in memoria dei dizionari
void LoadAllVocabularies();

// valutazione parole da memoria

int NegationVocabularyContains(char * word);

WordEvaluation PositiveVocabularyEvaluation(char * word);
WordEvaluation NegativeVocabularyEvaluation(char * word);
WordEvaluation IgnoreVocabularyEvaluation(char * word);