#include "Torgraf.h"
Torgraf::Torgraf(Tor *tor)
{
    this->tor=tor;
    pen.setColor(Qt::gray);
    pen.setWidth(1);

}

void Torgraf::rysujtor(QGraphicsScene *scena)
{
    rysujkrawedzie(scena);
    //scena->addPolygon(polygon, pen);
    //scena->addPolygon(polygonP, pen);
    //scena->addPolygon(polygonL, pen);


}

void Torgraf::rysujkrawedzie(QGraphicsScene *scena)
{
    std::vector<Punkt> centrum = tor->getcentrum();
    std::vector<Punkt> krawedzL= tor->getkrawedzL();
    std::vector<Punkt> krawedzP= tor->getkrawedzP();

    Punkt obecnyL(0,0), obecnyS(0,0),obecnyP(0,0);
    Punkt poprzedniL(krawedzL[0].x,krawedzL[0].y);
    Punkt poprzedniP(krawedzP[0].x,krawedzP[0].y);
    bool help = false;
    Punkt A1(0,0),A2(0,0);
    pen.setWidth(6);

    for(float t=0.0f; t<tor->getcentrum().size();t+=0.1f)
    {
        A1=tor->obliczpunktsplajnu(t,krawedzL);
        A2=tor->obliczpunktsplajnu(t,krawedzP);
        QLine linia(A1.x,A1.y,A2.x,A2.y);
        scena->addLine(linia,pen);
    }

    pen.setWidth(3);
    Punkt poprzedniS(centrum[0].x,centrum[0].y);
    for( float i = 0.0f; i <centrum.size(); i+=0.5f )
    {
            help = !help;
            if(help)
            {
                pen.setColor(Qt::white);
            }
            else
            {
                pen.setColor(Qt::gray);
            }
            obecnyS = Punkt(tor->obliczpunktsplajnu(i,centrum));
            QLine liniaS(poprzedniS.x,poprzedniS.y,obecnyS.x,obecnyS.y);
            scena->addLine(liniaS,pen);
            poprzedniS=obecnyS;
    }
    pen.setWidth(4);
    Punkt poprzedni(tor->gettor()[0].getpktszer(0).x,tor->gettor()[0].getpktszer(0).y);
    for( size_t i = 0; i <tor->gettor()[0].getvectorpktszer().size(); i+=2 )
    {
        help = !help;
        if(help)
        {
            pen.setColor(Qt::white);
        }
        else
        {
            pen.setColor(Qt::black);
        }
        obecnyS = Punkt(tor->gettor()[0].getpktszer(i));
        QLine liniaS(poprzedni.x,poprzedni.y,obecnyS.x,obecnyS.y);
        scena->addLine(liniaS,pen);
        poprzedni=obecnyS;

    }

    pen.setWidth(6);
    for( float i = 0.0f; i <krawedzL.size(); i+=0.9f )
    {
            help = !help;
            if(help)
            {
                pen.setColor(Qt::white);
            }
            else
            {
                pen.setColor(Qt::red);
            }
            obecnyL=Punkt(tor->obliczpunktsplajnu(i,krawedzL));
            obecnyP=Punkt(tor->obliczpunktsplajnu(i,krawedzP));
            QLine liniaL(poprzedniL.x,poprzedniL.y,obecnyL.x,obecnyL.y);
            QLine liniaP(poprzedniP.x,poprzedniP.y,obecnyP.x,obecnyP.y);
            scena->addLine(liniaL,pen);
            scena->addLine(liniaP,pen);
            poprzedniL=obecnyL;
            poprzedniP=obecnyP;
    }
    help = !help;
    if(help)
    {
        pen.setColor(Qt::white);
    }
    else
    {
        pen.setColor(Qt::red);
    }
    QLine liniaL(poprzedniL.x,poprzedniL.y,krawedzL[0].x,krawedzL[0].y);
    QLine liniaP(poprzedniP.x,poprzedniP.y,krawedzP[0].x,krawedzP[0].y);
    scena->addLine(liniaL,pen);
    scena->addLine(liniaP,pen);


}


