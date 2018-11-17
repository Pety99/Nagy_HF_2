

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

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
    //szog = szog * 180 / 3.14;
   // if (p->y > t->y )
     //   szog *= -1;
    //printf("SZOG: %f\n",szog* 180 / 3.14);
    double r = sqrt(pow((p->x-t->x),2) + pow((p->y-t->y),2));
    double k = 90; // ARÁNYOSÁGI TÉNYWZÕ
    double f = k*p->q*t->q/(r);                 //Lehet nem r*r lesz mert így szebb íveken megy, nem lesz túl nagy a gyorsulás
    //printf("%f\n",f);
    double fx = f* cos(szog) * scale; //ax
    double fy = f* sin(szog) * scale; //ay
    //printf("fx: %f\nfy: %f\n",fx,fy);
    //printf("%f\n%f\n",fx,fy);
    if ( p->x > t->x)  // Töltéstől jobbra van a mozgó töltés
    {

        //printf("P:X %f\n",p->x);
        fx *= -1;
        fy *= -1;
    }
    if (p->q > 0) //Pozitív töltés, taszít
    {
        p->vx += fx / p->q * time/200 * -1;  // a /200 az 5ms os main időzítőjében miatt van
        p->vy += fy / p->q * time/200 * -1;
    }
    else
    {
        p->vx += fx / p->q * time/200;
        p->vy += fy / p->q * time/200;
    }

     //printf("vx: %f\nvy: %f\n",p->vx,p->vy);
}



bool in_hatotav( Toltes p, Toltes t, double hatotav)
{
    double r = sqrt(pow((p.x-t.x),2) + pow((p.y-t.y),2));
    if ( r < hatotav)
        return true;
    else
        return false;
}

/*
bool in_hatotav2( Charge c, int palya double hatotav)
{
    for (int i = 1; i <meret; i++)
        int px = c[palya].toltes[i].x;                      ///mozgó töltés x koord
        int py = c[palya].toltes[i].y;                      ///mozgó töltés y koord
        int tx = c[palya].toltes[0].x;                      ///álló töltés x koord
        int ty = c[palya].toltes[0].y;                      ///álló töltés y koord
    {
        double r = sqrt(pow((px-tx),2) + pow((py-ty),2));
    }
}
*/
