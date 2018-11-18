

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <string.h>
#include <stdio.h>
#include <math.h>



void charge_calculate_path(char* path, char* path_bubble, int q)
{
    if ( q < 0)
        sprintf(path, "Resources/Abstract Platformer/Assets/PNG/Items/discGreen.png");
    else
        sprintf(path, "Resources/Abstract Platformer/Assets/PNG/Items/discRed.png");
    sprintf(path_bubble, "Resources/Bubble.png");

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
    destination.h = (int)height * scale ;
    destination.w = (int)width * scale ;
    destination.x = x - width/2;
    destination.y = y - height*scale/2;
    destination.x = (int)destination.x;
    destination.y = (int)destination.y;

    SDL_RenderCopy(renderer, texture,NULL, &destination);
    SDL_DestroyTexture(texture);
}

void bubble_rajzol(char const *path, double scale, int x, int y, int hatotav)
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
    double bubble_scale = (double)hatotav * 2 / (double)width ;
    SDL_FreeSurface(surface);
    SDL_Rect destination;
    destination.x = ((x - width/2 * bubble_scale));
    destination.y = ((y - height/2 * bubble_scale));
    destination.h = (int)height  * bubble_scale ;
    destination.w = (int)width  * bubble_scale ;
    destination.x = (int)destination.x;
    destination.y = (int)destination.y;

    SDL_RenderCopy(renderer, texture,NULL, &destination);
    SDL_DestroyTexture(texture);
}



