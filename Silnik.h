#ifndef SILNIK_H
#define SILNIK_H
#include<time.h>
#include<cstdlib>
#include<iostream>

/** Klasa silnika auta*/
class Silnik
{
private:
     float wytrzymalosc;
     float mocmaksyalna;
     float moc;
     bool popsuty;

public:
     /** Konstruktor silnika okreslajacy parametry startowe */
    Silnik();
    virtual ~Silnik();

    /** Metoda wirtualna liczaca moc silnika */
    virtual void obliczmoc();

    /** Metoda oblcizajaca czy silnik sie popsul*/
    void czydziala();

    /** Getter mocy maksymalnej */
    float getmocmaks() const;

    /** Setter mocy maksymalnej */
    void setmocmaks(float mocmaks);

    /** Getter mocy biezacej*/
    float getmoc() const;

    /** Setter mocy biezacej*/
    void setmoc(float moc);

    /** Getter stanu silnika*/
    bool getstan() const;


};

#endif // SILNIK_H
