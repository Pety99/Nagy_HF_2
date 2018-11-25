
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


int main(int argc, char *argv[])
{
    Result* eredmenyek;
    eredmenyek = load_Results(eredmenyek,"Results.txt");     ///Betölti az eredményeket  MAJD FREEZNI KELL
    Result*user = jatekos(eredmenyek);                       /// A jelenlegi játékos adatai
    bool new_user = is_new_user(user, eredmenyek);           /// Ezt még itt kell ellenőrizni, mielőtt beleíródik a listába

    int runs = 0;
    int number_of_maps = 8;
                                                /// A pályák számát majd át kell állítani annyire amennyi van!
    Map maps[number_of_maps];
    load_all_maps(maps, number_of_maps);        ///Betölti a pályákat

    Charge c[number_of_maps];                   ///Betölti a töltéseket
    load_all_charges(c, number_of_maps);        ///meghívásnál: c[palya].toltes[töltés szám].tulajdonság ( a palya egy int)

    enum { GOLYO_R=10 };


    Palya_screeshot palya_kep;                  /// majd ez fogja tárolni a háttereket
    fill_palya_kep(&palya_kep);

    while(number_of_maps)                       ///mindig igaz
    {
        int palya = pick_map(user->palya);       /// Kiválasszuk a pályánk számát.
        if (palya == -1)
            break;
        char * color = pick_color();                /// Random színű pálya

        char** background_path = background_foglal();                       ///betölti a hátterekt, még FREE() 8db, mert max annyi háttér van
        int number_of_bgs = fill_backgrounds(background_path, color);

    SDL_Window *window;
    SDL_Renderer *renderer;
    Keprenyo prog_screen = sdl_init(&window, &renderer);

    //A rajzolasnal barmilyen ertek kirajzolhato a def_screen es a scale segitsegevel.

    Keprenyo def_screen = {1536, 864, (double)16/(double)9};
    double scale = (double)prog_screen.szelesseg / (double) def_screen.szelesseg; // ez a scale a képernyõtõl függ

    for (int i = 0; i <= number_of_bgs; i ++)
    {
        background_rajzol1(background_path, scale, prog_screen, i);
    }



    for ( int i = 0; i < c[palya-1].meret; i++)               /// töltés adatok át scalelése NAGYON FONTOS
    {
        if (!scaled(&(c[palya-1].toltes[i])))                 /// ha már volt scalelve és mégegyszer megyönk nem scaeli ujra
        {
            toltes_scale(&(c[palya-1].toltes[i]), scale);
            c[palya-1].toltes[i].scaled = true;
        }
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
        int x = c[palya-1].toltes[i].x;
        int y = c[palya-1].toltes[i].y;
        char toltes_hely[200];
        char bubble_hely[200];

        charge_calculate_path(toltes_hely, bubble_hely, c[palya-1].toltes[i].q);
        charge_rajzol(toltes_hely, scale, c[palya-1].toltes[i].x, c[palya-1].toltes[i].y);
        bubble_rajzol(bubble_hely, scale, c[palya-1].toltes[i].x, c[palya-1].toltes[i].y, c[palya-1].toltes[i].hatotav);
    }

    /// Csinál egy "screenshotot" a rendrerről, hogy egy textúrában legyen az egész pálya
    screenshot(&window, &palya_kep, scale);
    Toltes* px = &(c[palya-1].toltes[0]);
    jatek(c, px, palya, scale, prog_screen, window, palya_kep, maps, user, number_of_maps);



    background_free(background_path);                   /// Felszabadítja a hátterket
    runs ++;
    }
    store_results(eredmenyek, user, "Results.txt");
    print_results(eredmenyek);
    for (int i = 0; i < number_of_maps; i ++)           /// Felszabadítja a pályákat
    {
        free_Map(maps[i], maps[i].meret);
    }
    free_Charge(c, number_of_maps);                     /// Felszabadítja a töltéseket
    if(new_user)
    {
        free(user);
    }
    free_results(eredmenyek);                           /// Felszabadítja az eredményeket


    return 0;
}

