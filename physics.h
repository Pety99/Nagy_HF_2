#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED
#include <stdbool.h>

typedef struct Toltes
    {
        double q; // töltés erõssége
        double x, y; // x,y koordináta
        double vx, vy; // x,y irányú sebesség
        double hatotav; // csak az állandó töltéseknek van!!
    } Toltes;

 typedef struct Charge
{
    Toltes* toltes;
    int meret;
}Charge;

void toltes_scale(Toltes* p, double scale);
void calc_v (Toltes *p, Toltes *t, int time, double scale);
void recalc_v(Toltes *p, Toltes *uj, char* irany);
bool in_hatotav( Toltes p, Toltes t, double hatotav);
bool in_hatotav2( Charge c, double hatotav);



#endif // PHYSICS_H_INCLUDED
