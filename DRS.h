#ifndef DRS_H
#define DRS_H
#include<Silnik.h>
#include<iostream>

/** Klasa DRS dziedziczaca po silniku */
class DRS : public Silnik
{
private:
    int wykorzystania;

public:
    /** Konstruktor klasy DRS
     *  @param moc - maksymalna moc silnika
     * */
    DRS(float moc);
    ~DRS();
     /** Metoda obliczajaca biezaca moc silnika */
    void obliczmoc() override;
};

#endif // DRS_H
