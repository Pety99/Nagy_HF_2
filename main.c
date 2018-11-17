

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
#include "charge_load.h"
#include "charge_draw.h"

typedef struct Palya_screeshot
{
    SDL_Rect meret;
    SDL_Texture *kep;
}Palya_screeshot;


Uint32 idozit(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}


void screenshot(Keprenyo prog_screen, Keprenyo def_screen, SDL_Renderer *renderer, SDL_Window* window, double scale)
{

}

int main(int argc, char *argv[])
{

    int number_of_maps = 3;                     /// A pályák számát majd át kell állítani annyire amennyi van!
    int palya = pick_map(number_of_maps);       // Kiválasszuk a pályánk számát.
    char * color = pick_color();                // Random színű pálya


    Map maps[number_of_maps];
    for (int i = 0; i < number_of_maps; i ++)           ///Betölti a pályákat
    {
        char path[200];
        sprintf(path,  "Maps/Map_%d.txt", i+1);
        load_maps(&maps[i], path);
    }

    Palya_screeshot palya_kep;                          /// majd ez fogja tárolni a pályát
    palya_kep.meret.x = 0;
    palya_kep.meret.y = 0;
    palya_kep.meret.w = GetSystemMetrics(SM_CXSCREEN);
    palya_kep.meret.h = GetSystemMetrics(SM_CYSCREEN);

    Charge c[number_of_maps];                                           ///Betölti a töltéseket
    for ( int i = 0; i < number_of_maps; i++)                           ///meghívásnál: c[palya].toltes[töltés szám].tulajdonság ( a palya egy int)
    {                                                                   ///pl: c[1].toltes[2].hatotav
        char toltes_helye[200];
        sprintf(toltes_helye, "Maps/Charges/Charge_%d.txt", i+1);
        load_charges(&c[i], toltes_helye);
    }

    int time = 5;
    enum { GOLYO_R=10 };
    printf("%f",c[2].toltes[2].hatotav);



    SDL_Window *window;
    SDL_Renderer *renderer;
    Keprenyo prog_screen = sdl_init(&window, &renderer); //Szeretnem fuggvenybe tenni, de nem megy.
    SDL_TimerID id = SDL_AddTimer(time, idozit, NULL);

    //A rajzolasnal barmilyen ertek kirajzolhato a def_screen es a scale segitsegevel.

    Keprenyo def_screen = {1536, 864, (double)16/(double)9};
    double scale = (double)prog_screen.szelesseg / (double) def_screen.szelesseg; // ez a scale a képernyõtõl függ
    boxRGBA(renderer, 0, 0, def_screen.szelesseg*scale, def_screen.magassag*scale, 0xFF, 0xFF, 0xFF, 0xFF);


    for ( int i = 0; i < number_of_maps; i++)               /// töltés adatok át scalelése NAGYON FONTOS
    {
        toltes_scale(&(c[palya-1].toltes[i]), scale);
    }


    for (int i = 0; i<maps[palya-1].meret; i++)             ///Páyla kirajzolása
    {
        int tile = maps[palya-1].map[i][0];
        int x = maps[palya-1].map[i][1];
        int y = maps[palya-1].map[i][2];
        char file_hely[200];

        calculate_path(file_hely, color, tile);
        rajzol(file_hely, scale, x, y);                // a file hely elöl kitöröltem egy & et
    }

    for (int i = 1; i<c[palya-1].meret; i++)             ///Töltések kirajzolása
    {
        int x = c[palya-1].toltes[i].x;                 // 5-6 sorral lejjebb komment
        int y = c[palya-1].toltes[i].y;
        char toltes_hely[200];
        charge_calculate_path(toltes_hely, c[palya-1].toltes[i].q);
        charge_rajzol(toltes_hely, scale, c[palya-1].toltes[i].x, c[palya-1].toltes[i].y);
    }

    // varunk a kilepesre
    SDL_Event event;
    int tries = 0;
    Toltes* px = &(c[palya-1].toltes[0]);                       /// 0. töltésre rámutat egy px pointer, csak a név miattt

    /// Csinál egy "screenshotot a rendrerről, hogy egy textúrában legyen"
    SDL_Surface* pScreenShot;
    pScreenShot = SDL_CreateRGBSurface(0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) , 32, NULL, NULL, NULL, NULL);
    if(pScreenShot)
    {
      SDL_RenderReadPixels(renderer, NULL, SDL_GetWindowPixelFormat(window), pScreenShot->pixels, pScreenShot->pitch);
      SDL_SaveBMP(pScreenShot, "Screenshot.bmp");
      palya_kep.kep = SDL_CreateTextureFromSurface(renderer, pScreenShot); /// majd később kell freezni (destory texture)
      SDL_FreeSurface(pScreenShot);


    }
    // töröljük a képernyőt
    boxRGBA(renderer, 0, 0, def_screen.szelesseg*scale, def_screen.magassag*scale, 0xFF, 0xFF, 0xFF, 0xFF);


    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT)
    {

        switch (event.type)
        {
        //felhasznaloi esemeny: ilyeneket general az idozito fuggveny
        case SDL_USEREVENT:
            // kitoroljuk az elozo poziciojabol (nagyjabol)
            ///filledCircleRGBA(renderer, px->x, px->y, GOLYO_R*scale, 0xFF, 0xFF, 0xFF, 0xFF);

        /// kiszamitjuk az uj helyet
        for (int i = 1; i < c[palya-1].meret; i++)
        {
            Toltes* tx = &(c[palya-1].toltes[i]);                   /// i. töltésre rámutat egy tx pointer

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


            ///visszapattanás
            if (px->x < GOLYO_R*scale || px->x > prog_screen.szelesseg-GOLYO_R*scale)
            {

                px->vx *= -1;
            }
            if (px->y < GOLYO_R*scale || px->y > prog_screen.magassag-GOLYO_R*scale)
                px->vy *= -1;

            // ujra kirajzolas, es mehet a kepernyore  EZ JELENIK MEG
            SDL_RenderCopy(renderer, palya_kep.kep, NULL, &palya_kep.meret);
            filledCircleRGBA(renderer, px->x, px->y, GOLYO_R*scale, 3, 165, 136, 220);

            SDL_RenderPresent(renderer);

            if (tries == 3)
                SDL_Quit();
            break;



        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            SDL_RemoveTimer(id);
            SDL_DestroyTexture(palya_kep.kep);
            SDL_Quit();

        }
    }

    for (int i = 0; i < number_of_maps; i ++)           ///Felszabadítja a pályákat
    {
        free_Map(maps[i], maps[i].meret);
    }

    free_Charge(c, number_of_maps);                     ///Felszabadítja a töltéseket



    /* ablak bezarasa */

    return 0;
}
