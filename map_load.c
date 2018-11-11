#include <stdio.h>
#include <stdlib.h>

#include "map_load.h"

void beolvas(FILE ** fp, char* path)
{
    *fp = fopen(path, "rt");
    if (*fp == NULL)
    {
        perror("Nem sikerült megnyitni a filet");
        return;
    }
}
int sorok_szama(char * path)
{
    // FONTOS!!! Lennie kell még egy enternek a file végén.
    char c;
    int sorok = 0;
    FILE* fp;
    beolvas(&fp, path);

    for (c = getc(fp); c != '#'; c = getc(fp))
        if (c == '\n') // Növeli a c-t ha \n karaktert lát
            sorok = sorok + 1;

    fclose(fp);
    return sorok;

}

int foglal(Map* p, int sor, int oszlop)
{
    int i;
    p->map = malloc(sor*sizeof(int *));
    if (p == NULL) {
        printf("Nem sikerült memóriát foglalni!\n");
        return 1;
    }

    for(i = 0 ; i < sor ; i++)
        p->map[i] = malloc( oszlop*sizeof(int) );
        if (p == NULL) {
            printf("Nem sikerült memóriát foglalni!\n");
            return 1;
    }

}



void fill(Map p, char* path)
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
        sscanf(sor, "%d %d %d", &(p.map[i][0]), &(p.map[i][1]), &(p.map[i][2]));
        i++;
    }
    fclose(fp);
    if (sor)
        free(sor);
}

//Ezek a lényeges függvény


void free_Map(Map p, int sor)
{
    int i;
    for(i = 0 ; i < sor ; i++)
        free(p.map[i]);
    free(p.map);
}

void load_maps(Map *map, char *path)
{
    FILE* palya;
    beolvas(&palya, path);

    int sor_max = sorok_szama(path);
    int oszlop_max = 3;

    foglal(map,sor_max, oszlop_max);
    fill(*map, path);
    map->meret = sor_max;
}


// ezek más kategória függvényei

int pick_map (int number_of_maps)
 {
     int palya = -1;
    while (palya < 1 || palya > number_of_maps)
    {
        printf("Valassz palyat 1 - %d: ", number_of_maps);
        scanf("%d",&palya);
    }
    return palya;
 }

 char* pick_color()
{
    char* colors[4] = {"Blue", "Brown", "Green", "Yellow"};

    char * color;
    srand(time(NULL));
    color = colors[rand() % 4];

    return color;
}
