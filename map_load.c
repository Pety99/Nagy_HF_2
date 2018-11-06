#include <stdio.h>
#include <stdlib.h>

void beolvas(FILE ** fp, char* path)
{
    *fp = fopen(path, "rt");
    if (*fp == NULL)
    {
        perror("Nem siker�lt megnyitni a filet");
        return;
    }
}
int sorok_szama(char * path)
{
    // FONTOS!!! Lennie kell m�g egy enternek a file v�g�n.
    char c;
    int sorok = 0;
    FILE* fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Nem lehet megnyitni a filet-t: %s", path);
        return 0;
    }

    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // N�veli a c-t ha \n karaktert l�t
            sorok = sorok + 1;

    fclose(fp);
    return sorok;

}
int foglal(int*** p, int sor, int oszlop)
{
    int i;
    *p = malloc(sor*sizeof(int *));
    if (p == NULL) {
        printf("Nem siker�lt mem�ri�t foglalni!\n");
        return 1;
    }

    for(i = 0 ; i < sor ; i++)
        (*p)[i] = malloc( oszlop*sizeof(int) );
        if (p == NULL) {
        printf("Nem siker�lt mem�ri�t foglalni!\n");
        return 1;
    }

}
void fill(int** p, char* path)
{
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
        sscanf(sor, "%d %d %d", &p[i][0], &p[i][1], &p[i][2]);
        i++;
    }
    fclose(fp);
    if (sor)
        free(sor);
}

//Ezek a l�nyeges f�ggv�ny

void free2D_tomb(int** p, int sor)
{
    int i;
    for(i = 0 ; i < sor ; i++)
        free(p[i]);
    free(p);
}
void create(int***map, char *path)
{
    FILE* palya;
    beolvas(&palya, path);

    int sor_max = sorok_szama(path);
    int oszlop_max = 3;

    foglal(map,sor_max, 5);
    fill (*map, path);
}