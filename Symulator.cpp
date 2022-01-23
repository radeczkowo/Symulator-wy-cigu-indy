#include "Symulator.h"



Symulator::Symulator(Scena *scena, Parkmaszyn *pmaszyn, Menadzertorow *mentorow, int liczbaokrazen)
{
    this->liczbaokrazen=liczbaokrazen;
    ileukonczylo=0;
    this->start=scena->getstartbutton();
    this->scena=scena;
    this->mentorow=mentorow;
    this->pmaszyn=pmaszyn;
    timer = new QTimer();
    timer->setInterval(40);
    ustawauta();
    scena->inicjalizacjatabeli(pmaszyn->getvectoraut().size());


    QObject::connect(timer, &QTimer::timeout, [=](){
        numeryokrazen();
        usunauta();
        ukonczonywyscig();
        autaupdate();
        pozycja();

    });

    QObject::connect(start, &QPushButton::released, [=](){
        timer->start();
        scena->wlacztablicewynikow(pmaszyn->getvectoraut().size());

    });

}

struct porownaj {
      bool operator()(const Auto* l, const Auto* r) {
        return l->getokrazenie()*(l->gettrasa().size()-1)+l->getpozstand() > r->getokrazenie()*(r->gettrasa().size()-1)+r->getpozstand();
      }
};

void Symulator::autaupdate()
{

    for( size_t i = 0; i < pmaszyn->getvectoraut().size(); i++ )
    {

        pmaszyn->getAuto(i)->setpozycja((int)i+1);
        pmaszyn->getAuto(i)->zmienpozycje();
        pmaszyn->getAuto(i)->getopony()->update(pmaszyn->getAuto(i)->gettrasa()[(int)pmaszyn->getAuto(i)->getpozstand()].getnawierzchnia());
        pmaszyn->getAuto(i)->getsilnik()->czydziala();
        pmaszyn->getAuto(i)->getsilnik()->obliczmoc();
        scena->getautograf(i)->zmienpozycje();
        if(!pmaszyn->getAuto(i)->getstan())
        scena->ustawpozycje(i+ileukonczylo,pmaszyn->getAuto(i)->getkierowca()->getnazwa(),pmaszyn->getAuto(i)->getokrazenie(),false,false,pmaszyn->getAuto(i)->postepokrazenia());
    }
}

void Symulator::ustawauta()
{
    for( size_t i = 0; i < pmaszyn->getvectoraut().size(); i++ )
    {
      pmaszyn->getAuto(i)->ustawpozycjestartowa((int)i, mentorow->gettor(), pmaszyn->getvectoraut());
      scena->getautograf(i)->zmienpozycje();
    }
    pozycja();


}

void Symulator::pozycja()
{
    std::vector<Auto*> t = pmaszyn->getvectoraut();
    std::sort(t.begin(), t.end(), porownaj());
    pmaszyn->setvectoraut(t);
}

void Symulator::usunauta()
{
    for (size_t i = 0; i < pmaszyn->getvectoraut().size(); i++)
    {
        if (pmaszyn->getAuto(i)->getstan())
        {
            scena->ustawpozycje(pmaszyn->getvectoraut().size()-1+ileukonczylo,pmaszyn->getAuto(i)->getkierowca()->getnazwa(),0,false,true,0);
            for (size_t j = 0; j < scena->getvectorautagraf().size(); j++)
            {
                 if (scena->getautograf(j)->getcar()==pmaszyn->getAuto(i))
                 {
                     scena->usunautograf((int)j);
                     break;
                 }
            }
            pmaszyn->usunauto((int)i);
        }
    }
}

void Symulator::ukonczonywyscig()
{
    for (size_t i = 0; i < pmaszyn->getvectoraut().size(); i++)
    {
        if (pmaszyn->getAuto(i)->getokrazenie()>liczbaokrazen)
        {
            scena->ustawpozycje(ileukonczylo,pmaszyn->getAuto(i)->getkierowca()->getnazwa(),0,true,false,0);
            for (size_t j = 0; j < scena->getvectorautagraf().size(); j++)
            {
                 if (scena->getautograf(j)->getcar()==pmaszyn->getAuto(i))
                 {
                     scena->usunautograf((int)j);
                     break;
                 }
            }
            pmaszyn->usunauto((int)i);
            ileukonczylo++;
        }
    }
}

void Symulator::numeryokrazen()
{
    if(pmaszyn->getvectoraut().size()==0 || ileukonczylo>0)
    {
        scena->progresokrazen(biezaceokr,liczbaokrazen,true);
    }
    else
    {
        biezaceokrazenie();
        scena->progresokrazen(biezaceokr,liczbaokrazen,false);
    }
}

void Symulator::biezaceokrazenie()
{
        for (auto val : pmaszyn->getvectoraut()) {
             if (biezaceokr < val->getokrazenie()) biezaceokr = val->getokrazenie();
        }
}






