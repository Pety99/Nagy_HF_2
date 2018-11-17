

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <string.h>
#include <stdio.h>

void charge_calculate_path(char* path, int q)
{
    if ( q < 0)
        sprintf(path, "Resources/Abstract Platformer/Assets/PNG/Items/discGreen.png");
    else
        sprintf(path, "Resources/Abstract Platformer/Assets/PNG/Items/discRed.png");

}

void charge_rajzol(char const *path, double scale, int x, int y)
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
    destination.x = x - width/2;
    destination.y = y - height/2;
    destination.h = (int)height * scale ;
    destination.w = (int)width * scale ;
    destination.x = (int)destination.x;
    destination.y = (int)destination.y;

    SDL_RenderCopy(renderer, texture,NULL, &destination);
    SDL_DestroyTexture(texture);
}



