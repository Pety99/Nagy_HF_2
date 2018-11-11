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



Uint32 idozit(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}


int main(int argc, char *argv[])
{
    int number_of_maps = 3;                     /// A pályák számát majd át kell állítani annyire amennyi van!
    int palya = pick_map(number_of_maps);       // Kiválasszuk a pályánk számát.
    char * color = pick_color();                // Random színű pálya


    Map maps[number_of_maps];
    for (int i = 0; i < number_of_maps; i ++)   //Betölti a pályákat
    {
        char path[200];
        sprintf(path,  "Maps/Map_%d.txt", i+1);
        load_maps(&maps[i], path);
    }


    Charge c;                                  //Betölti a töltéseket
    for ( int i = 0; i < number_of_maps; i++)
    {
        char* toltes_helye[200];
        sprintf(toltes_helye, "Maps/Charges/Charge_%d.txt", i+1);
        load_charges(&c, toltes_helye);
    }


    int time = 5;
    enum { GOLYO_R=10 };



    SDL_Window *window;
    SDL_Renderer *renderer;
    Keprenyo prog_screen = sdl_init(&window, &renderer); //Szeretnem fuggvenybe tenni, de nem megy.
    SDL_TimerID id = SDL_AddTimer(time, idozit, NULL);

    //A rajzolasnal barmilyen ertek kirajzolhato a def_screen es a scale segitsegevel.

    Keprenyo def_screen = {1536, 864, (double)16/(double)9};
    double scale = (double)prog_screen.szelesseg / (double) def_screen.szelesseg; // ez a scale a képernyõtõl függ
    boxRGBA(renderer, 0, 0, def_screen.szelesseg*scale, def_screen.magassag*scale, 0xFF, 0xFF, 0xFF, 0xFF);
    Toltes t;
    t.q = -6 * scale;
    t.vx = 0 * scale;
    t.vy =0 * scale;
    t.x = 500 * scale;
    t.y = 500 * scale;
    t.hatotav = 150 * scale;

    Toltes t2;
    t2.q = -5 * scale;
    t2.vx = 0 * scale;
    t2.vy =0 * scale;
    t2.x = 1150 * scale;
    t2.y = 400 * scale;
    t2.hatotav = 150 * scale;

    filledCircleRGBA(renderer, t.x, t.y, GOLYO_R * scale, 60, 178, 226, 255); // csak a töltés helyére egy kör
    filledCircleRGBA(renderer, t2.x, t2.y, GOLYO_R * scale, 60, 178, 226, 255); // csak a töltés helyére egy kör

    // animaciohoz
    Toltes p;
    p.x = 100 *scale;
    p.y = 580 *scale;
    p.vx = 3 * scale;
    p.vy = 0 * scale;
    p.q = 1; // Teljesen mindegy mekkora ettől nem függ



    for (int i = 0; i<maps[palya-1].meret; i++)
    {
        int tile = maps[palya-1].map[i][0];
        int x = maps[palya-1].map[i][1];
        int y = maps[palya-1].map[i][2];
        char file_hely[200];

        calculate_path(file_hely, color, tile);
        rajzol(&file_hely, scale, x, y);
    }


    // varunk a kilepesre
    SDL_Event event;
    int tries = 0;
    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT)
    {

        switch (event.type)
        {
        //felhasznaloi esemeny: ilyeneket general az idozito fuggveny
        case SDL_USEREVENT:
            // kitoroljuk az elozo poziciojabol (nagyjabol)
            filledCircleRGBA(renderer, p.x, p.y, GOLYO_R*scale, 0xFF, 0xFF, 0xFF, 0xFF);
            filledCircleRGBA(renderer, t.x, t.y, GOLYO_R * scale, 60, 178, 226, 255); // csak a töltés helyére egy kör
            filledCircleRGBA(renderer, t2.x, t2.y, GOLYO_R * scale, 60, 178, 226, 255); // csak a töltés helyére egy kör

            // kiszamitjuk az uj helyet
        if (in_hatotav(p, t, t.hatotav))
        {
                calc_dir(p, t, time);
                //printf("p.x: %f\n", p.x);
                //printf("p.y: %f\n", p.y);
                calc_v(&p, &t, time, scale);
        }

            p.x += p.vx;
            p.y += p.vy;

        if (in_hatotav(p, t2, t2.hatotav))
        {
                //printf("p.x: %f\n", p.x);
                //printf("p.y: %f\n", p.y);
            calc_v(&p, &t2, time, scale);
        }

            p.x += p.vx;            //EZ MIND 2 szer hozzáadódott javítani kell
            p.y += p.vy;            //!!!!!



            //visszapattanás
            if (p.x < GOLYO_R*scale || p.x > prog_screen.szelesseg-GOLYO_R*scale)
            {

                p.vx *= -1;
               // tries++;
            }
            if (p.y < GOLYO_R*scale || p.y > prog_screen.magassag-GOLYO_R*scale)
                p.vy *= -1;
            // ujra kirajzolas, es mehet a kepernyore
            filledCircleRGBA(renderer, p.x, p.y, GOLYO_R*scale, 3, 165, 136, 220);
            SDL_RenderPresent(renderer);
            if (tries == 3)
                SDL_Quit();
            break;



        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            SDL_RemoveTimer(id);
            SDL_Quit();


        }
    }



    /* ablak bezarasa */

    return 0;
}
