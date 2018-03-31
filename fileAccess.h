/*
*   fileAccess.h
*
*   Lo scopo di questo modulo è quello di accedere ai file esterni e di prelevarne o modificarne il contenuto
*
*/


void AddLineToFile(char* line, char* filename);
void RemoveLineFromFile(char* line, char* filename);
void LoadVocabularyToMemory(char ** vocabulary, int bufferSize, int lines,  char * vocabularyFile );
int FileContainsLine(char * line, char * filename);