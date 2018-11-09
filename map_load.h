#ifndef MAP_LOAD_H_INCLUDED
#define MAP_LOAD_H_INCLUDED
typedef struct Map
{
    int ** map;
    int meret;
}Map;

void beolvas(FILE ** fp, char* path);
int sorok_szama(char * path);
int foglal(int*** p, int sor, int oszlop);
void fill(int** p, char* path);

void free2D_tomb(int** p, int sor);
void create(int***map, char *path, Map *terkep);

#endif // MAP_LOAD_H_INCLUDED
