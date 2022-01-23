#include "Menadzertorow.h"

Menadzertorow::Menadzertorow(Scena *scena)
{
    utworztor(scena);
}

void Menadzertorow::utworztor(Scena*scena)
{
    tor = new Tor();
    scena->dodajtor(tor);
}

Tor *Menadzertorow::gettor() const
{
    return tor;
}
