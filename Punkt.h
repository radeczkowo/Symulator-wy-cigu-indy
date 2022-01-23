#ifndef PUNKT_H
#define PUNKT_H

/** Struktura punktu w przestrzeni */
struct Punkt
{
    float x;
    float y;

    /** Konstruktor uwzgledniajacy podane wspolrzedne
     * @param x - wspolrzedna na osi x
     * @param y - wspolrzedna na osi y
     * */
    Punkt(float x, float y);

    /** Konstruktor przypisujacy x i y wartosc 0*/
    Punkt();
};

#endif // PUNKT_H
