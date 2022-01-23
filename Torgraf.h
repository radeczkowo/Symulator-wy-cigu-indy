#ifndef TORGRAF_H
#define TORGRAF_H
#include<Tor.h>
#include<QGraphicsScene>
#include<QGraphicsItem>

/** Klasa odpowiadajaca za graficzne przedstawienie toru*/
class Torgraf
{  
private:
    Tor *tor;
    QPolygon polygon;
    QPolygon polygonL;
    QPolygon polygonP;
    QPen pen;
    QLine line;
    QPoint punktt;

public:  
    /** Konstruktor toru
     * @param *tor - wskaznik do logicznego toru*/
    Torgraf(Tor*tor);

    /** Metoda odpwoiadajaca za rysowanie toru na scenie
     * @param *scena - wskaznik do sceny */
    void rysujtor(QGraphicsScene *scena);

    /** Metoda odpowiadajaca za rysowanie krawedzi toru i innych graficznych elementow
     * @param *scena - wskaznik do sceny */
    void rysujkrawedzie(QGraphicsScene *scena);

};

#endif // TORGRAF_H
