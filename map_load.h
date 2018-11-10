#ifndef MAP_LOAD_H_INCLUDED
#define MAP_LOAD_H_INCLUDED
typedef struct Map
{
    int ** map;
    int meret;
}Map;

void beolvas(FILE ** fp, char* path);
int sorok_szama(char * path);
int foglal(Map* p, int sor, int oszlop);
void fill(Map p, char* path);

void free_Map(Map p, int sor);
void load_map(Map *map, char *path);

int chose_map (int number_of_maps);

#endif // MAP_LOAD_H_INCLUDED
