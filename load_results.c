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

void lista_kiir(Result *eleje)
{
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
    if (strcmp(sor, "\n") != 0)
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
    if (user->pontszam > 0);
    {
    if(is_new_user(user, eredmeny))
    {
        beszur(eredmeny, user->pontszam, user->palya, user-> nev);
    }
    Result *futo;

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

Result * jatekos(Result* eredmenyek)                /// Ellenőrzi, hogy az általunk megadott felhasználónév létezik e, ha nem csinál egyet
{
    char nev[20+1];
    char * c = &nev;
    bool beker = true;
    while(beker)
    {
        printf("Nev: (max 20 karakter) ");
        scanf(" %[^\n]", &nev);

        for (int i = 0; i < strlen(nev); i++)
        {
            if ( c[i] == ' ')
            {
                printf("Nem lehet space a nevben\n");
                beker = true;
                break;
            }
            beker = false;
        }
    }


    Result *mozgo;
    for (mozgo = eredmenyek; mozgo != NULL; mozgo = mozgo->kov)
    {
        if ( strcmp((mozgo->nev), nev) == 0)
        {
            printf("Letezo felhasznalo\n");
            return mozgo;
        }
    }
    // Ha még nem létezik a felhasználó, csinál egyet
    Result *uj = (Result *)malloc(sizeof(Result));
    strcpy(uj->nev, nev);
    uj->pontszam = 0;
    uj->palya = 1;
    return uj;
}


bool is_new_user(Result *user, Result *eredmenyek)
{
    bool new_usr = true;
    Result *mozgo;
    for (mozgo = eredmenyek; mozgo != NULL; mozgo = mozgo->kov)
    {
        if ( strcmp((mozgo->nev), (user->nev)) == 0)
        {
            new_usr = false;
            break;
        }
    }
    return new_usr;
}

void free_user(Result *user, Result *eredmenyek)
{
    bool new_usr = true;
    Result *mozgo;
    for (mozgo = eredmenyek; mozgo != NULL; mozgo = mozgo->kov)
    {
        if ( strcmp((mozgo->nev), (user->nev)) == 0)
        {
            new_usr = false;
            //break;
        }
    }
    if (new_usr && user->pontszam != 0);
        free(user);
}

void print_results(Result* eredmenyek)
{
    Result *mozgo;
    int i = 1;
    printf("Eredmenyek\n\n");
    for (mozgo = eredmenyek; mozgo->kov != NULL; mozgo = mozgo->kov)
    {
        printf("%d. %-20s pontszam: %-10d feloldott palyak: %d\n", i,  mozgo->nev, mozgo->pontszam, mozgo->palya);
        i++;
    }
}


