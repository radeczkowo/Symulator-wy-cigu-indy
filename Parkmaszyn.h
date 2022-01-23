#ifndef PARKMASZYN_H
#define PARKMASZYN_H
#include<Auto.h>
#include<iostream>
#include<vector>
#include<Scena.h>

/** Klasa dodajaca auta */
class Parkmaszyn
{
private:
    Auto *car;
    std::vector<Auto*> Auta;

public:
    /** Konstruktor Parku maszyn
     * @param Wskaznik do sceny potrzebny przy wywolywaniu metody tej klasy tworzacej graficzne auta
     * */
    Parkmaszyn(Scena *scena);

    /** Metoda dodajaca auto
     * @param car - wskaznik do auta
     * @param scena - wskaznik do sceny
     * @param sc - sciezka do pliku grafiki auta
     * @param kierunek - startowy zwrot auta
     * */
    void dodajauto(Auto *car, Scena *scena, QString sc, float kierunek);

    /** Metoda usuwajaca auto
     * @param i - numer auta w vectorze aut
     * */
    void usunauto(int i);

    /** Getter vectora aut */
    std::vector<Auto *> getvectoraut() const;

    /** Setter vectora aut */
    void setvectoraut(std::vector<Auto*> auta);

    /** Getter auta
     * @param i - numer auta w wektorze
     * */
    Auto* getAuto(int i) const;


};

#endif // PARKMASZYN_H
