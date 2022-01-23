#ifndef FRAGMENTTORU_H
#define FRAGMENTTORU_H
#include<Punkt.h>
#include<vector>
#include<iostream>
#include<cstdlib>
#include<time.h>


/** Klasa opisujaca parametry danego odcinka toru */
class Fragmenttoru
{
private:
    Punkt start;
    std::string nawierzchnia;
    float dlugosc;
    std::vector<Punkt> pktszer;

public:
    /** Konstruktor klasy Fragmenttoru
     * @param st - okresla punkt startowy na srodku szerokosci trasy
     * */
    Fragmenttoru(Punkt st);

    /** Getter punktu startowego*/
    Punkt getstart() const;

    /** Setter punktu startowego*/
    void setstart(Punkt A);

    /** Setter wspolrzednej y punktu startowego*/
    void setstarty(float y);

    /** Setter wspolrzednej x punktu startowego*/
    void setstartx(float x);

    /** Getter rodzaju nawierzchni odcinka */
    std::string getnawierzchnia() const;

    /** Setter dlugosci odcinka */
    void setdlugosc(float dlugosc);

    /** Getter dlugosci odcinka */
    float getdlugoc() const;

    /** Metoda dodajaca pkt na wektorze punktow szerokosci*/
    void dodajpktszer(Punkt A);

    /** Getter punktu szerokosci
     * @param numer do punktu wektora */
    Punkt getpktszer(int i) const;

    /** Getter vectora punktow szerokosci*/
    std::vector<Punkt> getvectorpktszer() const;

};
#endif // FRAGMENTTORU_H
