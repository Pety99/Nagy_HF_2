#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "map_load.h"
#include "physics.h"
#include "charge_load.h"




bool toltes_foglal(Charge * c, int meret) {
    c->meret = meret;
    c->charge = (Toltes*) malloc(meret * sizeof(Toltes));
    return c->charge != NULL;
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
        sscanf(sor, "%lf %lf %lf %lf %lf %lf", &(c.charge[i].q), &(c.charge[i].x), &(c.charge[i].y), &(c.charge[i].vx), &(c.charge[i].vy), &(c.charge[i].hatotav));
        i++;
    }
    fclose(fp);
    if (sor)
        free(sor);
}
void free_Charge(Charge c, int sor)
{
    int i;
    for(i = 0 ; i < sor ; i++)
        free(&c.charge[i]);
    free(c.charge);
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
