#ifndef LOAD_RESULTS_H_INCLUDED
#define LOAD_RESULTS_H_INCLUDED


typedef struct Result
{
    int pontszam;
    int palya;
    char nev[20+1];
    struct Result *kov;
} Result;


void eredmeny_beolvas(FILE ** fp, char* path);
Result *beszur(Result *elso, int pontszam, int palya, char* nev);
void free_results(Result *elso);
void lista_kiir(Result *eleje);
Result* load_Results(Result* eredmenyek, char* path);
void store_results(Result *eredmeny, Result *user, char*path);

Result * jatekos(Result* eredmenyek);
bool is_new_user(Result *user, Result *eredmenyek);
void free_user(Result *user, Result *eredmenyek);
void print_results(Result* eredmenyek);

#endif // LOAD_RESULTS_H_INCLUDED
