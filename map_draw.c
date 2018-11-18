

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <string.h>
#include <windows.h>

#include "screen.h"

void calculate_path(char* path, char* color,int tile)
{
    char temp[25];
        sprintf(temp, "tile%s_%02d",color, tile);
        sprintf(path, "Resources/Abstract Platformer/Assets/PNG/Tiles/");
        strcat(path, color);
        strcat(path, " tiles/");
        strcat(path, temp);
        strcat(path, ".png");
}

void rajzol(char const *path, double scale, int x, int y)
{
    SDL_Renderer *renderer;
    SDL_Surface* surface = IMG_Load(path);
    if (!surface)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        exit(1);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    int width = surface ->w;
    int height = surface ->h;
    SDL_FreeSurface(surface);
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;
    destination.h = (int)height * scale +1;
    destination.w = (int)width * scale +1;
    destination.x = (int)destination.x* 64 * scale; // a 64 et még javítani kell csak a nagy képeket rajzolja jól
    destination.y = (int)destination.y * 64 * scale;

    SDL_RenderCopy(renderer, texture,NULL, &destination);
    SDL_DestroyTexture(texture);
}

int fill_backgrounds(char **backgrounds, char* color)
{
    char def_path[200] = "Resources/Abstract Platformer/Assets/PNG/Backgrounds/";
    char temp[30];
    int i;
    if (strcmp(color, "Brown")== 0)
        i = 3;
    if (strcmp(color, "Blue")== 0)
        i = 4;
    if (strcmp(color, "Green")== 0)
        i = 6;
    if (strcmp(color, "Yellow")== 0)
        i = 5;

    for (int j = 0; j <= i; j++)
    {
        sprintf(backgrounds[j], &def_path);
        strcat(backgrounds[j], color);
        sprintf(temp, "/layers/%d.png", j+1);
        strcat(backgrounds[j], &temp);
    }
    return i;
}

void background_rajzol1(char const **path, double scale, Keprenyo prog_screen, int i)
{
    SDL_Renderer *renderer;


        printf("%s",path);
        SDL_Surface* surface = IMG_Load(path[i]);
        if (!surface)
        {
            printf("IMG_Load: %s\n", IMG_GetError());
            exit(1);
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        SDL_Rect destination;
        destination.h = prog_screen.magassag;
        destination.w = prog_screen.szelesseg;
        destination.x = 0;
        destination.y = 0;

        SDL_RenderCopy(renderer, texture,NULL, &destination);
        SDL_DestroyTexture(texture);

}

void all_rajzol(char const **path, double scale, Keprenyo prog_screen)
{
    for (int i = 0; i < 4; i ++)
    {
        background_rajzol1(path, scale, prog_screen, i);
    }
}
