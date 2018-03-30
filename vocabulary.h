

// Aggiunta e modifica di parole sui vocabolari
void AddWordToPositiveVocabulary(char* word);
void AddWordToNegativeVocabulary(char* word);
void AddWordToIgnoreVocabulary(char* word);


// ricerca parola da file
int PositiveVocabularyFileContains(char * word);
int NegativeVocabularyFileContains(char * word);
int IgnoreVocabularyFileContains(char * word);

// Caricamento in memoria dei dizionari
void LoadAllVocabularies();

// ricerca parola da memoria
int PositiveVocabularyContains(char * word);
int NegativeVocabularyContains(char * word);
int IgnoreVocabularyContains(char * word);