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

int main(int argc, char *argv[]) {


    int ** map;
    char path0[100] = "Maps/Map_1.txt";
    create(&map, path0);
    printf("%d", map[4][2]);




    SDL_Window *window;
    SDL_Renderer *renderer;
    Keprenyo prog_screen = sdl_init(&window, &renderer); //Szeretnem fuggvenybe tenni, de nem megy.

    //A rajzolasnal barmilyen ertek kirajzolhato a def_screen es a scale segitsegevel.

    Keprenyo def_screen = {1536, 864, (double)16/(double)9};
    double scale = (double)prog_screen.szelesseg / (double) def_screen.szelesseg;

    // Ezek csak proba rajzok.



    boxRGBA(renderer, 0, 0, def_screen.szelesseg*scale, def_screen.magassag*scale, 0xFF, 0xFF, 0xFF, 0xFF);
    const char path[200] = "Resources/Abstract Platformer/Assets/PNG/Tiles/Blue tiles/tileBlue_27.png";
    const char path2[200] = "Resources/Abstract Platformer/Assets/PNG/Tiles/Blue tiles/tileBlue_04.png";
    const char path3[200] = "Resources/Abstract Platformer/Assets/PNG/Tiles/Blue tiles/tileBlue_05.png";
    const char path4[200] = "Resources/Abstract Platformer/Assets/PNG/Tiles/Blue tiles/tileBlue_06.png";

    SDL_Rect destination = {0, 0, 64, 50};
    SDL_Rect destination2 = {1472, 0, 64, 50};
    SDL_Rect destination3 = {0, 814, 64, 50};
    SDL_Rect destination4 = {def_screen.szelesseg-64, def_screen.magassag-50, 64, 50};
    SDL_Rect destination5 = {128, 128, 64, 64};
    SDL_Rect destination6 = {192, 128, 64, 64};
    SDL_Rect destination7 = {256, 128, 64, 64};

    rajzol(&path, &destination, scale);
    rajzol(&path, &destination2, scale);
    rajzol(&path, &destination3, scale);
    rajzol(&path, &destination4, scale);
    rajzol(&path2, &destination5, scale);
    rajzol(&path3, &destination6, scale);
    rajzol(&path4, &destination7, scale);



    SDL_RenderPresent(renderer);

    /* varunk a kilepesre */
    SDL_Event event;
    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
            break;
        }
    }

    /* ablak bezarasa */

    return 0;
}
