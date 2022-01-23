#include "Kierowca.h"

Kierowca::Kierowca(std::string imie, std::string typ)
{
    if(typ=="agresywny")
    {
        this->typ="agresywny";
        wspagresji = 0.75f;
    }
    else if(typ=="pasywny")
    {
        this->typ="pasywny";
        wspagresji = 0.95f;
    }
    else
    {
        this->typ="umiarkowany";
        wspagresji = 0.85f;
    }
    nazwa=imie;


}

std::string Kierowca::getnazwa() const
{
    return nazwa;
}

float Kierowca::getwspagresji() const
{
    return wspagresji;
}
