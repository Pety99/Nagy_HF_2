#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

Uint32 idozit(Uint32 ms, void *param);
void visszapattanas(Charge* c, Toltes* px, int palya, double scale, int GOLYO_R, Keprenyo prog_screen);
bool tavozas(Toltes* px, double scale, int GOLYO_R, Keprenyo prog_screen);
void draw_aim(SDL_Window **window, Toltes* mozgo, double scale);
bool cel(Toltes* px, int palya, Map* maps, double scale, int sugar);
int calc_score(int tries);
void jatek(Charge* c, Toltes* px, int palya, double scale, Keprenyo prog_screen, SDL_Window* window, Palya_screeshot palya_kep, Map* maps, Result *user, int number_of_maps);
bool scaled(Toltes* p);

#endif // GAME_H_INCLUDED
