#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL_image.h>


void rajzol(char const *path, SDL_Rect * destination, double scale)
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
    destination->h = (int)height * scale +1;
    destination->w = (int)width * scale +1;
    destination->x = (int)destination->x * scale;
    destination->y = (int)destination->y * scale;

    SDL_RenderCopy(renderer, texture,NULL, destination);
    SDL_DestroyTexture(texture);
}
