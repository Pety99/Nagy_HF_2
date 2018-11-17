

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include "screen.h"


Keprenyo  display(Keprenyo k)
{
    k.szelesseg = GetSystemMetrics(SM_CXSCREEN);
    k.magassag = GetSystemMetrics(SM_CYSCREEN);
    k.arany = (double)k.szelesseg / (double) k.magassag;
    return k;
}

void keperenyo_arany(double * arany,double* default_arany, double* arany_s, double* arany_m)
{
    if (*arany <= *default_arany)
    {
        *arany_s = 1;
        *arany_m = (double)*arany / (double)*default_arany;
    }
    else
    {
        *arany_s = (double)*default_arany/ (double)*arany;
        *arany_m = 1;
    }
}

Keprenyo keperenyo_convert(Keprenyo k)
{
    double arany_s;
    double arany_m;
    double default_arany = (double)16/ (double)9;
    keperenyo_arany(&k.arany, &default_arany, &arany_s, &arany_m);

    k.arany = default_arany;
    k.szelesseg = k.szelesseg * arany_s;
    k.magassag = k.magassag * arany_m;
    return k;
}


Keprenyo sdl_init(SDL_Window **pwindow, SDL_Renderer **prenderer)
{
    Keprenyo k = display(k);
    Keprenyo usr_screen = k;
    k = keperenyo_convert(k);
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("Main_ablak", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, k.szelesseg, k.magassag, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_SetWindowResizable(window, SDL_FALSE);
    SDL_SetWindowBordered(window, SDL_FALSE);
    SDL_SetWindowSize(window,usr_screen.szelesseg, usr_screen.magassag);
    SDL_SetWindowPosition(window, 0 , 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);
    *pwindow = window;
    *prenderer = renderer;
    return k;
}
