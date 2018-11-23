#include "debugmalloc.h"

#include <stdio.h>
#include <stdlib.h>

#include "load_results.h"
#include "map_load.h"

void eredmeny_beolvas(FILE ** fp, char* path)
{
    *fp = fopen(path, "rt+");
    if (*fp == NULL)
    {
        perror("Nem sikerült megnyitni a filet");
        return;
    }
}

int nevek_szama(char * path)  ///HASZOINTALAN
{
    // FONTOS!!! Lennie kell még egy enternek a file végén.
    char c;
    int nevek = 0;
    FILE* fp;
    beolvas(&fp, path);

    for (c = getc(fp); c != 'EOF'; c = getc(fp))
        if (c == '\n') // Növeli a c-t ha \n karaktert lát
            nevek = nevek + 1;

    fclose(fp);
    return nevek;
}

Result *beszur(Result *elso, int pontszam, int palya, char* nev)
{
    Result *uj = (Result *)malloc(sizeof(Result));
    strcpy(uj->nev, nev);
    uj->pontszam = pontszam;
    uj->palya = palya;

    if (elso == NULL || elso->pontszam < pontszam)
    {
        uj->kov = elso;
        elso = uj;
    }
    else
    {
        Result *mozgo;
        Result *lemarado;
        for (mozgo = elso; mozgo->kov != NULL && mozgo->pontszam >= pontszam; mozgo = mozgo->kov)  /// a mozgo ->kov  elöl lehet nem jo
            lemarado = mozgo;
        uj->kov = mozgo;
        lemarado->kov = uj;
    }
    return elso;
}

void free_results(Result *elso)
{
    Result *mozgo = elso, *lemarado;
    while (mozgo->kov != NULL)
    {
        lemarado = mozgo;
        mozgo = mozgo->kov;
        free(lemarado);
    }
}

void lista_kiir(Result *eleje) {
    Result *p;
    int i = 1;
    for (p = eleje; p->kov != NULL; p = p->kov)
    {
        printf("%d. %s,  pontszam: %d,  feloldott palyak: %d\n", i, p->nev, p->pontszam, p->palya);
        i++;
    }
}

Result* load_Results(Result* eredmenyek, char* path)
{
    int pontszam;
    int palya;
    char nev[20+1];

    FILE* fp;
    beolvas(&fp, path);

    char * sor = NULL;
    size_t hossz = 0;
    ssize_t olvas;
    int i = 0;
    while ((olvas = getline(&sor, &hossz, fp)) != -1)
    {
        //printf("Retrieved sor of length %zu :\n", olvas);
        //printf("%s", sor);
    if (sor != "\n")
    {

        sscanf(sor, "%s %d %d", &nev, &pontszam, &palya);
        eredmenyek = beszur(eredmenyek, pontszam, palya, &nev);
        i++;
    }
    }
    fclose(fp);
    return eredmenyek;
}

void store_results(Result *eredmeny, Result *user,  char*path)
{
    if (user->pontszam > 0)
    {
    beszur(eredmeny, user->pontszam, user->palya, user-> nev);
    Result *futo;
    for (futo = eredmeny; futo != NULL; futo = futo->kov) {
        printf("%d", futo->palya);
    }

    FILE *fp;
    eredmeny_beolvas(&fp, path);
    Result *mozgo;
    for (mozgo = eredmeny; mozgo->kov != NULL; mozgo = mozgo->kov)
    {
        fprintf(fp, "%s %d %d\n", mozgo->nev, mozgo->pontszam, mozgo->palya);
    }
    fclose(fp);
    }
}
