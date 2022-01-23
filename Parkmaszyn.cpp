#include "Parkmaszyn.h"

Parkmaszyn::Parkmaszyn(Scena *scena)
{
    car=new Auto(4.8f,0.05f,"Ziomek", "agresywny","deszczowe", 0.9f, false);
    dodajauto(car, scena, ":/zdjecia/car1.png",180);
    car = new Auto(5.4f,0.09f,"Tomek", "pasywny","srednie", 1.2f, true);
    dodajauto(car, scena, ":/zdjecia/car2.png", 0);
    car = new Auto(4.8f,0.08f,"Zenek", "umiarkowany","srednie", 1.1f, true);
    dodajauto(car, scena, ":/zdjecia/car4.png", 0);
    car = new Auto(4.2f,0.06f,"Piotrek", "agresywny","miekkie", 1.3f, false);
    dodajauto(car, scena, ":/zdjecia/car2.png", 0);
    car=new Auto(4.5f,0.05f,"Witek", "umiarkowany","miekkie", 1.0f, true);
    dodajauto(car, scena, ":/zdjecia/car1.png", 180);
    car = new Auto(4.7f,0.02f,"Ziutek", "pasywny","deszczowe", 1.0f, true);
    dodajauto(car, scena, ":/zdjecia/car2.png", 0);

}

void Parkmaszyn::dodajauto(Auto *car, Scena *scena, QString sc, float kierunek)
{
     scena->dodajauto(car,sc,kierunek);
     Auta.push_back(car);
}

void Parkmaszyn::usunauto(int i)
{
    delete Auta[i];
    //Auta[i]->setvmax(0);
    Auta.erase(Auta.begin()+i);
}

std::vector<Auto *> Parkmaszyn::getvectoraut() const
{
    return Auta;
}

void Parkmaszyn::setvectoraut(std::vector<Auto *> auta)
{
    Auta=auta;
}

Auto *Parkmaszyn::getAuto(int i) const
{
    return Auta[i];
}


