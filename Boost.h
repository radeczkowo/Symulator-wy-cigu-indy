#ifndef BOOST_H
#define BOOST_H
#include<Silnik.h>

/** Klasa Boost dziedziczaca po silniku */
class Boost : public Silnik
{
public:
    /** Konstruktor klasy Boost
     *  @param moc - maksymalna oc silnika
     * */
    Boost(float moc);
    ~Boost();

    /** Metoda obliczajaca biezaca moc silnika */
    void obliczmoc() override;
};

#endif // BOOST_H
