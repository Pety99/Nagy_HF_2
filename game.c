
#include "debugmalloc.h"

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
#include "load_results.h"
#include "game.h"

Uint32 idozit(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
}

void visszapattanas(Charge* c, Toltes* px, int palya, double scale, int GOLYO_R, Keprenyo prog_screen) ///NINCS HASZNÁLVA
{
    if (px->x < GOLYO_R*scale || px->x > prog_screen.szelesseg-GOLYO_R*scale)
            {

                px->vx *= -1;
            }
            if (px->y < GOLYO_R*scale || px->y > prog_screen.magassag-GOLYO_R*scale)
                px->vy *= -1;
}

bool tavozas(Toltes* px, double scale, int GOLYO_R, Keprenyo prog_screen)
{
    bool crash = false;
    if (px->x < -2*GOLYO_R*scale || px->x > prog_screen.szelesseg+2*GOLYO_R*scale)
            {
                Sleep(500);
                crash = true;
            }
            if (px->y < -2*GOLYO_R*scale || px->y > prog_screen.magassag+2*GOLYO_R*scale)
                {
                Sleep(500);
                crash = true;
                }

    return crash;
}


void draw_aim(SDL_Window **window, Toltes* mozgo, double scale)
{
    SDL_Renderer* renderer = SDL_GetRenderer(*window);
    double szog = atan(mozgo->vy / mozgo->vx);
    int x = mozgo->x + (int)(mozgo->vx*cos(szog)* 30 * scale);
    int y = mozgo->y + (int)(mozgo->vy*cos(szog)* 30 * scale);
    thickLineRGBA (renderer, (int)mozgo->x, (int)mozgo->y, x, y, 4,3, 165, 136, 220);
}

bool cel(Toltes* px, int palya, Map* maps, double scale, int sugar)
{
    if (px->x > maps[palya-1].map[0][1] *64 *scale && px->x < (maps[palya-1].map[0][1] + 1) *64 *scale)
        if (px->y > maps[palya-1].map[0][2] *64 *scale && px->y < (maps[palya-1].map[0][2] + 1) *64 *scale)
        {
            Sleep(500);
            /// WIN SCREEN KIRAJZOLÁSA ESETLEG
            return true;
        }
    return false;

}

int calc_score(int tries)
{
        /*Ez a függvény e,õször csökken utánna nõ és egyre nyújtottabb intevallumokon ismétli ezt
        Az függvény érték 20000 - 6000 között vannak*/
        return (int)(((pow(2,sin(sqrt((tries/3)+2)))) + 0.1 ) *10000);
}

void jatek(Charge* c, Toltes* px, int palya, double scale, Keprenyo prog_screen, SDL_Window* window, Palya_screeshot palya_kep, Map* maps, Result *user, int number_of_maps)
{
    int tries = 0;
    int time = 8;
    SDL_TimerID id = SDL_AddTimer(time, idozit, NULL);
    SDL_Renderer* renderer = SDL_GetRenderer(window);
    enum { GOLYO_R=10 };
    bool win = false;
    bool kiloves = false;
    bool aim = false;
    bool crash = false;
    Toltes mozgo = *px;         /// Ezt a töltést fogjuk kirajzolni

    // varunk a kilepesre
    SDL_Event event;
    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT)
    {
        switch (event.type)
        {
        // Felhasznaloi esemeny: ilyeneket general az idozito fuggveny

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                kiloves = true;
                aim = false;
                break;
            case SDLK_UP:
                recalc_v(px, &mozgo, "up");
                aim = true;
                break;
            case SDLK_DOWN:
                recalc_v(px, &mozgo, "down");
                aim = true;
                break;
            case SDLK_r:
                reset(px, &mozgo);
                tries ++;
                aim = true;
                kiloves = false;
                break;
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
            win = cel(&mozgo, palya, maps, scale, GOLYO_R);

            //nincs használva
            //visszapattanas(c, &mozgo, palya, scale, GOLYO_R, prog_screen);

            check_crash2(c, &mozgo, maps, palya, scale, GOLYO_R);
            crash = tavozas(&mozgo, scale, GOLYO_R, prog_screen);
            if (crash)
            {
                reset(px, &mozgo);
                tries ++;
                aim = true;
                kiloves = false;
                crash = false;
            }

            // ujra kirajzolas, es mehet a kepernyore  EZ JELENIK MEG
            SDL_RenderCopy(renderer, palya_kep.kep, NULL, &palya_kep.meret);
            filledCircleRGBA(renderer, mozgo.x, mozgo.y, GOLYO_R*scale, 3, 165, 136, 220);
            if (aim)
                draw_aim(&window, &mozgo, scale);
            // Kirajzolunk mindent
            SDL_RenderPresent(renderer);
            break;

        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            SDL_RemoveTimer(id);
            printf("Pontszam: %d\n", user->pontszam);
            SDL_DestroyTexture(palya_kep.kep);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
        if (win)
            {
                win = false;
                user->pontszam += calc_score(tries);
                if(palya == user->palya && palya < number_of_maps)
                    user->palya += 1;
                printf("Pontszam: %d\n", user->pontszam);

                SDL_DestroyTexture(palya_kep.kep);
                SDL_DestroyWindow(window);
                SDL_Quit();

            }
    }
}
bool scaled(Toltes* p)
{
    return p->scaled;
}
