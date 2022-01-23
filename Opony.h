#ifndef OPONY_H
#define OPONY_H
#include<iostream>
#include<Fragmenttoru.h>

/** Klasa opisujaca opony auta */
class Opony
{
private:
    float wytrzymalosc;
    float zuzycie;
    float wspv;
    std::string rodzaj;
    bool pekniete;
    std::string typ;

public:    
    /** Konstruktor opon
     * @param typ - okresa rodzaj opon
     * */
    Opony(std::string typ="twarde");

    /** Metoda aktualizujaca wspolczynniki opony w zaleznoci od nawierzchni na jakiej sie znajduje
     * @param nawierzchnia - nawierzchnia*/
    void update(std::string nawierzchnia);

    /** Metoda obliczajaca czy nastapilo pekniecie opony*/
    void czypeklo();

     /** Metoda obliczajaca zuzycie opony*/
    void obliczzuzycie();

    /** Getter wspolczynnika opony odpowiadajacego za predkosc auta*/
    float getwspv() const;

    /** Getter stanu opon(czy peknieta) */
    bool getstan() const;
};

#endif // OPONY_H
