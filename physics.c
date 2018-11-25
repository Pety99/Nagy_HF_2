#include "debugmalloc.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>

#include "screen.h"
#include "map_load.h"
#include "map_draw.h"
#include "physics.h"

void toltes_scale(Toltes* p, double scale)
{
    p->hatotav *= scale;
    p->q *= scale;
    p->vx *= scale;
    p->vy *= scale;
    p->x *= scale;
    p->y *= scale;
}

void calc_v (Toltes *p, Toltes *t, int time, double scale)
{

    double szog = atan((p->y-t->y)/(p->x-t->x));
    double r = sqrt(pow((p->x-t->x),2) + pow((p->y-t->y),2));
    double k = 90; // ARÁNYOSÁGI TÉNYWZÕ
    double f = k*p->q*t->q/(r);                 //Lehet nem r*r lesz mert így szebb íveken megy, nem lesz túl nagy a gyorsulás
    double fx = f* cos(szog) * scale; //ax
    double fy = f* sin(szog) * scale; //ay
    if ( p->x > t->x)  // Töltéstől jobbra van a mozgó töltés
    {
        fx *= -1;
        fy *= -1;
    }
    if (p->q > 0) //Pozitív töltés, taszít
    {
        p->vx += fx / p->q * 0.01 * -1;  // a /200 az 5ms os main időzítőjében miatt van
        p->vy += fy / p->q * 0.01 * -1;
    }
    else
    {
       // p->vx += fx / p->q * 0.01;
       // p->vy += fy / p->q * 0.01;
    }
}

void mozgas(Charge* c, Toltes* px, int palya, int time, double scale)
{
    for (int i = 1; i < c[palya-1].meret; i++)
                {
                    Toltes* tx = &(c[palya-1].toltes[i]);           /// i. töltésre rámutat egy tx pointer

                    if (in_hatotav(*px, *tx, tx->hatotav))
                    {
                        //printf("p.x: %f\n", p.x);
                        //printf("p.y: %f\n", p.y);
                        calc_v(px, tx, time, scale);
                    }
                }
                px->x += px->vx;
                px->y += px->vy;

                px->x += px->vx;
                px->y += px->vy;
}

void recalc_v(Toltes *p, Toltes *uj, char * irany)
{
    double szog = atan(uj->vy / uj->vx);
    if (strcmp(irany, "down") == 0)
        szog += 0.02;
    else if(strcmp(irany, "up") == 0)
        szog -= 0.02;
    uj->vx = p->vx* cos(szog);
    uj->vy = p->vy* sin(szog);

}

bool in_hatotav( Toltes p, Toltes t, double hatotav)
{
    double r = sqrt(pow((p.x-t.x),2) + pow((p.y-t.y),2));
    if ( r < hatotav)
        return true;
    else
        return false;
}

void reset(Toltes *p, Toltes *uj)
{
    uj->vx = p->vx;
    uj->vy = p->vy;
    uj->x = p-> x;
    uj->y = p-> y;
}

void check_crash2(Charge* c, Toltes* mozgo, Map* maps, int palya, double scale, int sugar)
{
    for (int i = 1; i< maps[palya-1].meret; i++)
    {
        int tx = maps[palya-1].map[i][1]; // egy tile felső sarkának x koordinátája, még nem pixelekben.
        int ty = maps[palya-1].map[i][2]; // ... alsó...

        if (mozgo->x +sugar > tx*64*scale && mozgo->x -sugar< (tx+1)*64*scale)               /// Fontről - Lentről ütközés
        {
            /// ((fent-1pixel) > p < (fent+1pixel) vagy (lent-1pixel) > p < (lent+1pixel))
            if (mozgo->y +sugar >= ty*64*scale -5 && mozgo->y +sugar <= ty*64*scale +5 || mozgo->y -sugar >= (ty+1)*64*scale -5 && mozgo->y -sugar <= (ty+1)*64*scale +5)
                mozgo->vy *= -1;
        }

        if (mozgo->y +sugar> ty*64*scale && mozgo->y -sugar < (ty+1)*64*scale)              /// JObbrol - Balról ütközik
        {
            /// ((bal-1pixel) > p < bal+1pixel) vagy (jobb-1pixel) > p < (jobb+1pixel))
            if (mozgo->x +sugar >= tx*64*scale -5 && mozgo->x +sugar <= tx*64*scale +5 || mozgo->x -sugar >= (tx+1)*64*scale -5 &&mozgo->x -sugar <= (tx+1)*64*scale +5)
                mozgo->vx *= -1;
        }
    }
}
