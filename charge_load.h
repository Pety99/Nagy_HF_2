#ifndef CHARGE_LOAD_H_INCLUDED
#define CHARGE_LOAD_H_INCLUDED
#include "physics.h"
#include <stdbool.h>



///
/*

A Charge_x.txt file felépítése:
A sorok a töltések adatait tartalmazzák szóközzel elválasztva egymástól:
erõsség, x koordináta, y koordináta, x irányú sebesság, y irányú sebesség, hatótáv.
Az elsõ sor mindig a kilõni kívát töltés adatait jelenti, a többi pedig a statikus töltéseket

*/
///

typedef struct Charge
{
    Toltes* charge;
    int meret;

}Charge;

bool toltes_foglal(Charge * c, int meret);
void toltes_fill(Charge c, char* toltes_helye);
void free_Charge(Charge c, int sor);
void load_charges(Charge *c, char *toltes_helye);
#endif // CHARGE_LOAD_H_INCLUDED
