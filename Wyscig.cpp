#include "Wyscig.h"

Wyscig::Wyscig(Scena *scena)
{
    mentorow = new Menadzertorow(scena);
    pmaszyn = new Parkmaszyn(scena);
    symulator = new Symulator(scena,pmaszyn,mentorow,5);
}




