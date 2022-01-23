#include "Opony.h"

Opony::Opony(std::string typ)
{
    zuzycie=0;
    wspv=1.0f;
    pekniete = false;
    if(typ == "miekkie")
    {
        rodzaj=typ;
        wytrzymalosc=1200.0f; //1200
    }
    else if(typ == "deszczowe")
    {
        rodzaj=typ;
        wytrzymalosc=1350.0f; //1350
    }
    else
    {
        rodzaj="srednie";
        wytrzymalosc=1500.0f; //1500
    }

}

void Opony::update(std::string nawierzchnia)
{
    if(nawierzchnia == "sucha")
    {
        if(rodzaj=="miekkie")
        {
            wspv=1.0f;
            zuzycie=0.05f;
        }
        else if(rodzaj=="srednie")
        {
            wspv=0.9f;
            zuzycie=0.01f;
        }
        else
        {
            wspv=0.7f;
            zuzycie=0.1f;
        }
    }
    else if(nawierzchnia == "wilgotna")
    {
        if(rodzaj=="miekkie")
        {
            wspv=0.8f;
            zuzycie=0.05f;
        }
        else if(rodzaj=="srednie")
        {
            wspv=0.85f;
            zuzycie=0.01f;
        }
        else
        {
            wspv=0.9f;
            zuzycie=0.04f;
        }
    }
    else
    {
        if(rodzaj=="miekkie")
        {
            wspv=0.6f;
            zuzycie=0.1f;
        }
        else if(rodzaj=="srednie")
        {
            wspv=0.7f;
            zuzycie=0.05f;
        }
        else
        {
            wspv=1.0f;
            zuzycie=0.01f;
        }
    }
    obliczzuzycie();
    czypeklo();

}

void Opony::czypeklo()
{
    int liczba;
    srand(time(NULL));
    liczba = std::rand() % (int)wytrzymalosc;
    if(liczba<1)
    {
        pekniete=true;
    }

}

void Opony::obliczzuzycie()
{
    wytrzymalosc-=zuzycie;
}

float Opony::getwspv() const
{
    return wspv;
}

bool Opony::getstan() const
{
    return pekniete;
}

