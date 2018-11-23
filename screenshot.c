#include "debugmalloc.h"

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <windows.h>

#include "screenshot.h"
#include "screen.h"

void fill_palya_kep(Palya_screeshot* palya_kep)
{
    palya_kep->meret.x = 0;
    palya_kep->meret.y = 0;
    palya_kep->meret.w = GetSystemMetrics(SM_CXSCREEN);
    palya_kep->meret.h = GetSystemMetrics(SM_CYSCREEN);

}

void screenshot(SDL_Window **window, Palya_screeshot *palya_kep, double scale)
{
    //bet�lti a renderert
    auto renderer = SDL_GetRenderer(*window);

    // Csin�l egy �res RGB surfacet
    SDL_Surface * screen_shot = SDL_CreateRGBSurface(0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) , 32, NULL, NULL, NULL, NULL);
    if(screen_shot)
    {
        // Beolvassa a pixeleket a rendererr�l �s a surfacere m�solja
        SDL_RenderReadPixels(renderer, NULL, SDL_GetWindowPixelFormat(window), screen_shot->pixels, screen_shot->pitch);

        SDL_SaveBMP(screen_shot, "Screenshot.bmp");      //Ez csak a k�p elment�s�re volt j�
        palya_kep->kep = SDL_CreateTextureFromSurface(renderer, screen_shot); /// majd k�s�bb kell freezni (destory texture)
        SDL_FreeSurface(screen_shot);
    }

}


