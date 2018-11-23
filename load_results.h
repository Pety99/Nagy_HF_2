#ifndef LOAD_RESULTS_H_INCLUDED
#define LOAD_RESULTS_H_INCLUDED


typedef struct Result
{
    int pontszam;
    int palya;
    char nev[20+1];
    struct Result *kov;
} Result;



int nevek_szama(char * path);
Result* load_Results(Result* eredmenyek, char* path);
void store_results(Result *eredmeny, Result *user, char*path);


#endif // LOAD_RESULTS_H_INCLUDED
