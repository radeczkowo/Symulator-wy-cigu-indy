#ifndef KIEROWCA_H
#define KIEROWCA_H
#include<iostream>

/** Klasa opisujaca kierowce auta*/
class Kierowca
{
private:
    std::string typ;
    std::string nazwa;
    float wspagresji;

public:
    /** Konstruktor kierowcy okeslajacy jego parametry
     * @param imie - nazwa kierowcy ktora wyswietli sie na tablicy wynikow
     * @param typ - okresla zachowanie kierowcy na torze
     * */
    Kierowca(std::string imie="Robert", std::string typ="umiarkowany");

    /** Getter nazwy kierowcy*/
    std::string getnazwa() const;

    /** Getter wspolczynnika agresji kierowcy*/
    float getwspagresji() const;
};

#endif // KIEROWCA_H
