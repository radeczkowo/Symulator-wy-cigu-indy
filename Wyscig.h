#ifndef WYSCIG_H
#define WYSCIG_H
#include <Menadzertorow.h>
#include <Parkmaszyn.h>
#include <Symulator.h>
#include <Scena.h>

/** Klasa odpowiadajaca za przygotowanie symulatora menadzera torow i parku maszyn*/
class Wyscig
{
private:
    Menadzertorow *mentorow;
    Parkmaszyn *pmaszyn;
    Symulator *symulator;

public:
    /** Konstruktor klasy Wyscig
     * @param - wskaznik do gaficznej sceny */
    Wyscig(Scena *scena);
};

#endif // WYSCIG_H
