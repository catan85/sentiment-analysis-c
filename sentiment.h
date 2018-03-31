

typedef struct WordEvaluation
{ 
    char * word;
    int rating;
    double matchRate;
} WordEvaluation;

int EvaluateStatement(char* statement);