#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED
#include <stdbool.h>

typedef struct Toltes
    {
        double q; // töltés erõssége
        double x, y; // x,y koordináta
        double vx, vy; // x,y irányú sebesség
        double hatotav; // csak az állandó töltéseknek van!!
        bool scaled;
    } Toltes;

 typedef struct Charge
{
    Toltes* toltes;
    int meret;
}Charge;

void toltes_scale(Toltes* p, double scale);
void calc_v (Toltes *p, Toltes *t, int time, double scale);
void mozgas(Charge* c, Toltes* px, int palya, int time, double scale);
void recalc_v(Toltes *p, Toltes *uj, char* irany);
bool in_hatotav( Toltes p, Toltes t, double hatotav);
void reset(Toltes *p, Toltes *uj);
void check_crash2(Charge* c, Toltes* mozgo, Map* maps, int palya, double scale, int sugar);




#endif // PHYSICS_H_INCLUDED
