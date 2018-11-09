#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <string.h>

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

/*void draw_map(int**map, char * color, int scale) // NINCS HASZNÁLVA
{
    char path[200];

    // AZ INT 5 ÖT KI KELL CSERELNI A HOSSZRA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
     for (int i = 0; i<5; i++)
    {
        int tile = map[i][0];
        int x = map[i][1];
        int y = map[i][2];

        calculate_path(path, color, tile);


        //printf("%s\n", path);
    }
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
    destination.h = (int)height * scale +1;
    destination.w = (int)width * scale +1;
    destination.x = (int)destination.x * scale;
    destination.y = (int)destination.y * scale;

    SDL_RenderCopy(renderer, texture,NULL, &destination);
    SDL_DestroyTexture(texture);



}
*/
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
