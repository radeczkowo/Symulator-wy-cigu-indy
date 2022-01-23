#include "DRS.h"

DRS::DRS(float moc)
{
    setmocmaks(moc);
    setmoc(0.8f*getmocmaks());
    wykorzystania=1000;
}

DRS::~DRS()
{

}



void DRS::obliczmoc()
{
    if(wykorzystania<=0)
    {
        setmoc(0.8f*getmocmaks());
        wykorzystania=1000;
    }
    if(wykorzystania>0&&wykorzystania<=100)
    {
        setmoc(1.2f*getmocmaks());
    }
    wykorzystania--;
}


