
#include "Autograf.h"

Autograf::Autograf(Auto *car,QString sc,float bk)
{
    this->car=car;
    bazowykierunek = bk;
    QPixmap pixmap(sc);
    pixmap =pixmap.scaled(QSize(20,14));
    pix = new QGraphicsPixmapItem(pixmap);
    pix->setTransformOriginPoint(10,7);

}

Autograf::~Autograf()
{
    delete pix;
}

void Autograf::dodajauto(QGraphicsScene *scena)
{
    scena->addItem(pix);
}


void Autograf::zmienpozycje()
{
    px=(car->getposx());
    py=(car->getposy());
    pix->setPos(px-10,py-7);
    pix->setRotation(-car->getkierunek()+bazowykierunek);

}

Auto *Autograf::getcar() const
{
    return car;

}


