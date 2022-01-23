#include "Boost.h"

Boost::Boost(float moc)
{
    setmocmaks(moc);
    setmoc(0.8f*getmocmaks());
}

Boost::~Boost()
{
}

void Boost::obliczmoc()
{
    srand(time(NULL));
    int liczba = std::rand() % 100;
    if(liczba<=12)
    {
        setmoc(0.8f*getmocmaks());
    }
    else if(liczba>12&&liczba<=35)
    {
        setmoc(0.84f*getmocmaks());
    }
    else if(liczba>35&&liczba<=65)
    {
        setmoc(0.88f*getmocmaks());
    }
    else if(liczba>65&&liczba<=92)
    {
        setmoc(0.92f*getmocmaks());
    }
    else
    {
         setmoc(0.96f*getmocmaks());
    }

}
