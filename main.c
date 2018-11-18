

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
#include "screenshot.h"

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

char** background_foglal()
{
    char** backgrounds = (double**) malloc(8 * sizeof(char*));
    for (int y = 0; y < 8; ++y)
    backgrounds[y] = (char*) malloc(200 * sizeof(char));
    return backgrounds;
}

void visszapattanas(Charge* c, Toltes* px, int palya, int time, double scale, int GOLYO_R, Keprenyo prog_screen)
{
    if (px->x < GOLYO_R*scale || px->x > prog_screen.szelesseg-GOLYO_R*scale)
            {

                px->vx *= -1;
            }
            if (px->y < GOLYO_R*scale || px->y > prog_screen.magassag-GOLYO_R*scale)
                px->vy *= -1;
}

void draw_aim(SDL_Window **window, Toltes* mozgo, double scale)
{
    auto renderer = SDL_GetRenderer(*window);
    double szog = atan(mozgo->vy / mozgo->vx);
    int x = mozgo->x + (int)(mozgo->vx*cos(szog)* 30 * scale);
    int y = mozgo->y + (int)(mozgo->vy*cos(szog)* 30 * scale);
    thickLineRGBA (renderer, (int)mozgo->x, (int)mozgo->y, x, y, 4,3, 165, 136, 220);
}

Uint32 idozit(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

int main(int argc, char *argv[])
{
    int runs = 0;
    int number_of_maps = 3;
                                                /// A pályák számát majd át kell állítani annyire amennyi van!
    Map maps[number_of_maps];
    load_all_maps(maps, number_of_maps);        ///Betölti a pályákat

    Charge c[number_of_maps];                   ///Betölti a töltéseket
    load_all_charges(c, number_of_maps);        ///meghívásnál: c[palya].toltes[töltés szám].tulajdonság ( a palya egy int)

    enum { GOLYO_R=10 };


    Palya_screeshot palya_kep;                  /// majd ez fogja tárolni a pályát
    fill_palya_kep(&palya_kep);

    while( runs < number_of_maps)
    {

        int palya = pick_map(number_of_maps);       // Kiválasszuk a pályánk számát.
        char * color = pick_color();                // Random színű pálya

        char** background_path = background_foglal();                       ///betölti a töltéseket, még FREE() zni kell
        int number_of_bgs = fill_backgrounds(background_path, color);

    SDL_Window *window;
    SDL_Renderer *renderer;
    Keprenyo prog_screen = sdl_init(&window, &renderer); //Szeretnem fuggvenybe tenni, de nem megy.
    int time = 8;
    SDL_TimerID id = SDL_AddTimer(time, idozit, NULL);

    //A rajzolasnal barmilyen ertek kirajzolhato a def_screen es a scale segitsegevel.

    Keprenyo def_screen = {1536, 864, (double)16/(double)9};
    double scale = (double)prog_screen.szelesseg / (double) def_screen.szelesseg; // ez a scale a képernyõtõl függ

    for (int i = 0; i <= number_of_bgs; i ++)
    {
        background_rajzol1(background_path, scale, prog_screen, i);
    }

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
        char bubble_hely[200];

        charge_calculate_path(toltes_hely, bubble_hely, c[palya-1].toltes[i].q);
        charge_rajzol(toltes_hely, scale, c[palya-1].toltes[i].x, c[palya-1].toltes[i].y);
        bubble_rajzol(bubble_hely, scale, c[palya-1].toltes[i].x, c[palya-1].toltes[i].y, c[palya-1].toltes[i].hatotav);
    }


    // varunk a kilepesre
    SDL_Event event;
    Toltes* px = &(c[palya-1].toltes[0]);                       /// 0. töltésre rámutat egy px pointer, csak a név miattt

    /// Csinál egy "screenshotot" a rendrerről, hogy egy textúrában legyen az egész pálya
    screenshot(&window, &palya_kep, scale);

    bool kiloves = false;
    bool aim = false;
    Toltes mozgo = c[palya-1].toltes[0];                        /// Ezt a töltést fogjuk kirajzolni

    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT)
    {
        switch (event.type)
        {
        // Felhasznaloi esemeny: ilyeneket general az idozito fuggveny

        case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE: kiloves = true; aim = false; break;
                    case SDLK_UP: recalc_v(px, &mozgo, "up"); aim = true; break;
                    case SDLK_DOWN: recalc_v(px, &mozgo, "down"); aim = true; break;
                }
                break;


        case SDL_USEREVENT:
            // kitoroljuk az elozo poziciojabol (nagyjabol)
            ///filledCircleRGBA(renderer, px->x, px->y, GOLYO_R*scale, 0xFF, 0xFF, 0xFF, 0xFF);

            // kiszamitjuk a golyó uj helyét
            if (kiloves)
            {
                mozgas(c, &mozgo, palya, time, scale);
            }

            //visszapattanás
            visszapattanas(c, &mozgo, palya, time, scale, GOLYO_R, prog_screen);

            // ujra kirajzolas, es mehet a kepernyore  EZ JELENIK MEG
            SDL_RenderCopy(renderer, palya_kep.kep, NULL, &palya_kep.meret);
            filledCircleRGBA(renderer, mozgo.x, mozgo.y, GOLYO_R*scale, 3, 165, 136, 220);
            if (aim)
                draw_aim(&window, &mozgo, scale);


            SDL_RenderPresent(renderer);
            break;



        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            SDL_RemoveTimer(id);
            SDL_DestroyTexture(palya_kep.kep);
            SDL_Quit();

        }
    }
    runs ++;
    }


/*

    for (int i = 0; i < number_of_maps; i ++)           ///Felszabadítja a pályákat
    {
        free_Map(maps[i], maps[i].meret);
    }

    free_Charge(c, number_of_maps);                     ///Felszabadítja a töltéseket

*/

    /* ablak bezarasa */

    return 0;
}
