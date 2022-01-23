#include "Silnik.h"

Silnik::Silnik()
{
    wytrzymalosc=1150.0f;
    popsuty = false;

}

Silnik::~Silnik()
{
}

void Silnik::obliczmoc()
{

}

void Silnik::czydziala()
{
    int liczba;
    srand(time(NULL));
    liczba = std::rand() % (int)wytrzymalosc;
    if(liczba<1)
    {
        popsuty=true;
    }


}

float Silnik::getmocmaks() const
{
    return mocmaksyalna;
}

void Silnik::setmocmaks(float mocmaks)
{
    mocmaksyalna=mocmaks;
}

float Silnik::getmoc() const
{
    return moc;
}

void Silnik::setmoc(float moc)
{
    this->moc=moc;
}

bool Silnik::getstan() const
{
    return popsuty;
}



