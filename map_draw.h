#ifndef MAP_DRAW_H_INCLUDED
#define MAP_DRAW_H_INCLUDED

void rajzol(char const *path, SDL_Rect * destination, double scale);
void draw_map(int**map, char * color, int scale);


#endif // MAP_DRAW_H_INCLUDED
