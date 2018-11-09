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
    if ( p->x > t->x)
    {
        //printf("P:X %f\n",p->x);
        fx *= -1;
        fy *= -1;
    }
    if (p->q > 0) //Pozitív töltés, taszít
    {
        p->vx += fx / p->q * time/200 * -1;
        p->vy += fy / p->q * time/200 * -1;
    }
    else
    {
        p->vx += fx / p->q * time/200;
        p->vy += fy / p->q * time/200;
    }

     //printf("vx: %f\nvy: %f\n",p->vx,p->vy);
}

int calc_dir(Toltes  p, Toltes t, int time) // Gyalázatos haszontalan függvény
{
    double szog = atan((p.y-t.y)/(p.x-t.x));
    //printf("DIR.SZOG:  %f\n", szog* 180 / 3.14);
    //Azért nem pointerként kapja az elemeket. hogy véletlenül se változtassakrajta
}


bool in_hatotav( Toltes p, Toltes t, double hatotav)
{
    double r = sqrt(pow((p.x-t.x),2) + pow((p.y-t.y),2));
    if ( r < hatotav)
        return true;
    else
        return false;

}

