
#include <stdio.h>
#include <stdlib.h>

#include "map_load.h"
#include "physics.h"
#include "charge_load.h"

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
    {

        p->map[i] = malloc( oszlop*sizeof(int) );
        if (p == NULL)
        {
            printf("Nem sikerült memóriát foglalni!\n");
            return 1;
        }
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

void load_all_maps(Map* maps, int number_of_maps)
{
    for (int i = 0; i < number_of_maps; i ++)           ///Betölti a pályákat
    {
        char path[200];
        sprintf(path,  "Maps/Map_%d.txt", i+1);
        load_maps(&maps[i], path);
    }
}

char** background_foglal()
{
    char** backgrounds = (char**) malloc(8 * sizeof(char*));
    for (int y = 0; y < 8; ++y)
    backgrounds[y] = (char*) malloc(200 * sizeof(char));
    return backgrounds;
}

void background_free(char** background_path)
{
    int i;
    for(i = 0 ; i < 8 ; i++)
        free(background_path[i]);
    free(background_path);
}


// ezek más kategória függvényei

int pick_map (int number_of_maps)
{
    char palya[10];
    int betu = -1;
    bool beker = true;
    while (beker && betu < 1 || beker > number_of_maps)
    {
        bool exit = true;
        printf("(-1 a kilepeshez)\nValassz palyat 1 - %d: ", number_of_maps);
        scanf("%s",&palya);

        betu = atoi(&palya);
        if (betu == 0)
        {
            printf("Ne betuket irj be...\n");
            exit = false;
            betu = -1;
        }

        if (betu > number_of_maps)
        {
             printf("Ez a palya nem elerheto\n");
             exit = false;
             betu = -1;
        }


        if (exit && (betu != 0 || betu == -1) )
            beker = false;
    }
    return betu;
}

 char* pick_color()
{
    srand(time(NULL));
    char* colors[4] = {"Blue", "Brown", "Green", "Yellow"};

    char * color;
    color = colors[rand() % 4];

    return color;
}
