#ifndef MENADZERTOROW_H
#define MENADZERTOROW_H
#include <Tor.h>
#include <Scena.h>

/** Klasa Menadzera do tworzenia toru*/
class Menadzertorow
{
private:
    Tor* tor;
public:
    /** Konstruktor Menadzera torow
     * @param Wskaznik do sceny potrzebny przy wywolywaniu metody tej klasy tworzacej graficzny tor
     * */
    Menadzertorow(Scena*scena);

    /** Metoda tworzaca tor*/
    void utworztor(Scena*scena);

    /** Getter toru */
    Tor* gettor() const;
};

#endif // MENADZERTOROW_H
