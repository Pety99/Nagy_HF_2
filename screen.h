#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

typedef struct Keprenyo
{
    DWORD szelesseg;
    DWORD magassag;
    double arany;
}Keprenyo;

Keprenyo  display(Keprenyo k);
void keperenyo_arany(double * arany,double* default_arany, double* arany_s, double* arany_m);
Keprenyo keperenyo_convert(Keprenyo k);
Keprenyo sdl_init(SDL_Window **pwindow, SDL_Renderer **prenderer);

#endif // SCREEN_H_INCLUDED
