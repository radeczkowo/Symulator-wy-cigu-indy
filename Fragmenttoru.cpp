#include "Fragmenttoru.h"

Fragmenttoru::Fragmenttoru(Punkt st)
{
    start=st;
    dlugosc=0;
    int liczba;
    srand(time(NULL));
    liczba = std::rand() % 100;
    if(liczba<7)
    {
        nawierzchnia = "mokra";
    }
    else if(liczba>=7 &&liczba<20)
    {
        nawierzchnia = "wilgotna";
    }
    else
    {
        nawierzchnia = "sucha";
    }
}

Punkt Fragmenttoru::getstart() const
{
    return start;
}

void Fragmenttoru::setstart(Punkt A)
{
    start = A;
}

void Fragmenttoru::setstarty(float y)
{
    start.y = y;
}

void Fragmenttoru::setstartx(float x)
{
    start.x = x;
}

std::string Fragmenttoru::getnawierzchnia() const
{
    return nawierzchnia;
}

void Fragmenttoru::setdlugosc(float dlugosc)
{
    this->dlugosc=dlugosc;
}

float Fragmenttoru::getdlugoc() const
{
    return dlugosc;
}

void Fragmenttoru::dodajpktszer(Punkt A)
{
    pktszer.push_back(A);
}

Punkt Fragmenttoru::getpktszer(int i) const
{
    return pktszer[i];
}

std::vector<Punkt> Fragmenttoru::getvectorpktszer() const
{
    return pktszer;
}


