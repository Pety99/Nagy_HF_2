#ifndef SCREENSHOT_H_INCLUDED
#define SCREENSHOT_H_INCLUDED

typedef struct Palya_screeshot
{
    SDL_Rect meret;
    SDL_Texture *kep;
}Palya_screeshot;

void screenshot(SDL_Window **window, Palya_screeshot *palya_kep, double scale);


#endif // SCREENSHOT_H_INCLUDED
