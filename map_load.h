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
int foglal2(Map* p, int sor, int oszlop);
void fill(int** p, char* path);
void fill2(Map p, char* path);

void free2D_tomb(int** p, int sor);
void free_Map(Map p, int sor);
void create(int***map, char *path, Map *terkep);
void create2(Map *map, char *path);

#endif // MAP_LOAD_H_INCLUDED
