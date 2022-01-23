#ifndef AUTOGRAF_H
#define AUTOGRAF_H
#include<Auto.h>
#include<Tor.h>
#include<QGraphicsScene>
#include<QGraphicsItem>

 /** Klasa opisujaca zachowanie auta na grafice*/
class Autograf
{
private:
    float px, py;
    QGraphicsPixmapItem *pix;
    float bazowykierunek;
    Auto *car;

public:
    /** Konstruktor klasy autograf
     * @param *car - wskaznik do niegraficznego auta
     * @param sc opisuje sciezke do  pliku grafiki auta
     * @param bk - opisuje zwrot startowy auta
     * */
    Autograf(Auto *car, QString sc, float bk);
    ~Autograf();

     /** Dodaje grafike auta do sceny*/
    void dodajauto(QGraphicsScene *scena);

    /** Zmienia pozycje i zwrot auta na scenie*/
    void zmienpozycje();

     /** Getter do niegraficznego wskaznika auta*/
    Auto* getcar() const;
};

#endif // AUTOGRAF_H
