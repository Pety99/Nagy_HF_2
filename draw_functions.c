#include "physics.h"
#include "charge_load.h"
#include "map_load.h"


void mindet_rajzol(Map* maps, int palya, char* color, double scale)
{
    for (int i = 0; i<maps[palya-1].meret; i++)             ///Páyla kirajzolása
    {
        int tile = maps[palya-1].map[i][0];
        int x = maps[palya-1].map[i][1];
        int y = maps[palya-1].map[i][2];
        char file_hely[200];

        calculate_path(file_hely, color, tile);
        rajzol(file_hely, scale, x, y);                // a file hely elöl kitöröltem egy & et
    }
}
