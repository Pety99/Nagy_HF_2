

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "map_load.h"
#include "physics.h"
#include "charge_load.h"




bool toltes_foglal(Charge * c, int meret) {
    c->meret = meret;
    c->toltes = (Toltes*) malloc(meret * sizeof(Toltes));
    return c->toltes != NULL;
}


void toltes_fill(Charge c, char* toltes_helye)
{
    FILE* fp;
    beolvas(&fp, toltes_helye);

    char * sor = NULL;
    size_t hossz = 0;
    ssize_t olvas;
    int i = 0;
    int test;
    while ((olvas = getline(&sor, &hossz, fp)) != -1)
     {
        //printf("Retrieved sor of length %zu :\n", olvas);
        //printf("%s", sor);
        sscanf(sor, "%lf %lf %lf %lf %lf %lf", &(c.toltes[i].q), &(c.toltes[i].x), &(c.toltes[i].y), &(c.toltes[i].vx), &(c.toltes[i].vy), &(c.toltes[i].hatotav));
        i++;
    }
    fclose(fp);
}


void free_Charge(Charge *c, int number_of_maps)
{
    int j = 0;
    for (j = 0; j < number_of_maps; j++)
    {
        free(c[j].toltes);
    }

}


void load_charges(Charge *c, char *toltes_helye)
{
    FILE* toltes;
    beolvas(&toltes, toltes_helye);

    int sor_max = sorok_szama(toltes_helye);

    toltes_foglal(c, sor_max);
    toltes_fill(*c, toltes_helye);
    c->meret = sor_max;
}

