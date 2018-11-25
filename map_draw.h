#ifndef MAP_DRAW_H_INCLUDED
#define MAP_DRAW_H_INCLUDED

void calculate_path(char* path, char* color,int tile);
void rajzol(char const *path, double scale, int x, int y);
int fill_backgrounds(char **backgrounds, char* color);
void background_rajzol1(char const **path, double scale, Keprenyo prog_screen, int i);




#endif // MAP_DRAW_H_INCLUDED
