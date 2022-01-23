#define M_PI           3.14159265358979323846f
#include "Auto.h"

Auto::Auto(float v, float a, std::string imiekierowcy, std::string typkierowcy, std::string opony,float mocsilnika, bool czydrs)
{
    if(czydrs)
    {
        silnik=new DRS(mocsilnika);
    }
    else
    {
        silnik= new Boost(mocsilnika);
    }
    popsuty = false;
    kierowca = new Kierowca(imiekierowcy, typkierowcy);
    this->opony = new Opony(opony);
    vmax=v;
    vsilnikopony=v;
    poz=0;
    przyspieszenie=a;
    hamowanie=5.5f*a;

}

Auto::~Auto()
{
    delete silnik;
    delete kierowca;
    delete opony;
}


void Auto::ustawpozycjestartowa(int numer, Tor *tor, std::vector<Auto *> Auta)
{
    predkosc=0;
    float w;
    okrazenie=1;
    predkoscoptymalna=vmax;
    this->Auta=Auta;
    this->tor=tor;
    this->trasa=tor->obliczoptymalnatrase(kierowca->getwspagresji());
    trasaoptymalna=trasa;
    poz = (float)numer*16;
    t = tor->obliczstandaryzowanatrase(poz,tor->gettor());
    Punkt A=(tor->obliczpunktsplajnufragmentu(t,tor->gettor()));
    w= tor->obliczgradientpunktufrag(t,tor->gettor());
    kierunek = w*180.0f/M_PI;
    if(numer%2==0)
    {
        A.y = A.y-10;
    }
    else
    {
        A.y = A.y+10;
    }
    posx=A.x;
    posy=A.y;
    obliczboki(w,A);
    konfigurujstart(A,poz);
    zaaktualizujdlugoscodcinka(0);

}

void Auto::zmienpozycje()
{
    float w;
    t = tor->obliczstandaryzowanatrase(poz,trasa);
    Punkt A=(tor->obliczpunktsplajnufragmentu(t,trasa));
    w=tor->obliczgradientpunktufrag(t,trasa);
    kierunek = w*180/M_PI;
    zaaktualizujdlugoscodcinka((int)t);
    resetujtrase(t,trasaoptymalna);
    posx=A.x;
    posy=A.y;
    obliczboki(w,A);
    sprawdzczyautowpoblizu();
    wyprzedzanie();
    stanupdate();
    a();  
    poz+=predkosc;
        if(poz>=tor->obliczdlugosctrasy(trasa))
        {
            okrazenie++;
            poz=poz-tor->obliczdlugosctrasy(trasa);
        }
}

void Auto::sprawdzczyautowpoblizu()
{
    Autaobok.clear();
    for(size_t i=0;i< Auta.size();i++)
    {
        if(Auta[i]!= this)
        {
            if(tor->odlegloscpomiedzypkt(Punkt(posx,posy),Punkt(Auta[i]->posx,Auta[i]->posy))<60)
            {
                Autaobok.push_back(Auta[i]);
            }
        }
    }
}




void Auto::zaaktualizujdlugoscodcinka(int t)
{
    t = int(t);
    trasa[t].setdlugosc(tor->obliczodleglosc(t,trasa,0.2f));


}

void Auto::konfigurujstart(Punkt A, float poz)
{
    int t;
    float odleglosc =1000;
    float minodleglosc = 1000;
    t = (int)tor->obliczstandaryzowanatrase(poz,trasa);
    trasa[trasa.size()-1].setstarty(A.y);

    //trasa[trasa.size()-1].start.y=A.y;
    for(int i = 0 ; i<= t; i++)
    {
        trasa[i].setstarty(A.y);
    }
    for(size_t i=t+1;(int)i<=t+3; i++)
    {
        int d=0;
        minodleglosc=1000;
        for(size_t j =0; j< trasa[i].getvectorpktszer().size();j++)
        {

            odleglosc+= tor->odlegloscpomiedzypkt(trasa[i+1].getstart(),trasa[i].getpktszer(j));
            odleglosc+= tor->odlegloscpomiedzypkt(Punkt(posx,posy),trasa[i].getpktszer(j));
            if(odleglosc<minodleglosc)
            {
                minodleglosc=odleglosc;
                d=(int)j;
            }
            odleglosc=0;
        }
        trasa[i].setstart(trasa[i].getpktszer(d));
        zaaktualizujdlugoscodcinka(i);
    }

}

void Auto::resetujtrase(float t, std::vector<Fragmenttoru> punkty)
{

    if((int)t==0){
        trasa[trasa.size()-3].setstart(punkty[trasa.size()-3].getstart());
    }
    else if((int)t==1)
    {
        trasa[trasa.size()-2].setstart(punkty[trasa.size()-2].getstart());
    }

    else if((int)t==2)
    {
        trasa[trasa.size()-1].setstart(punkty[trasa.size()-1].getstart());
    }
    else
    {
        trasa[(int)t-3].setstart(punkty[(int)t-3].getstart());
    }

}


void Auto::wyprzedzanie()
{
        if(t<trasa.size()-3)
        {
            wyprzedzanieautaprzed((int)t+1,(int)t+2, Autaobok);

        }
        else if(t>=trasa.size()-3 && t<trasa.size()-2)
        {
            wyprzedzanieautaprzed((int)t+1,0, Autaobok);
        }
        else if(t>=trasa.size()-2 && t<trasa.size())
        {
             wyprzedzanieautaprzed(0,1, Autaobok);
        }

}

void Auto::obliczboki(float grad, Punkt A)
{
    przodl = Punkt(10.0f* cos(grad) + A.x,- 7.0f * cos(grad) + A.y);
    przod  = Punkt(10.0f* cos(grad) + A.x,- 10.0f * sin(grad) + A.y);
    przodp = Punkt(10.0f* cos(grad) + A.x, 7.0f * cos(grad) + A.y);
    tyll   = Punkt(-10.0f* cos(grad) + A.x, -7.0f * cos(grad) + A.y);
    tyl    = Punkt(-10.0f* cos(grad) + A.x, 10.0f * sin(grad) + A.y);
    tylp   = Punkt(-10.0f* cos(grad) + A.x, 7.0f * cos(grad) + A.y);
    bokl   = Punkt(7.0f* sin(grad) + A.x, 7.0f * cos(grad) + A.y);
    bokp   = Punkt(-7.0f* sin(grad) + A.x, -7.0f * cos(grad) + A.y);

}

bool Auto::odleglosctylprzod(float odl, Auto *car)
{
    if(tor->odlegloscpomiedzypkt(this->przod,car->tyl)<odl)
    {
        return false;
    }
    if(tor->odlegloscpomiedzypkt(this->przodl,car->tylp)<odl-3.0f)
    {
        return false;
    }
    if(tor->odlegloscpomiedzypkt(this->przodp,car->tyll)<odl-3.0f)
    {
        return false;
    }
    if(tor->odlegloscpomiedzypkt(this->przodl,car->tyll)<odl-2.0f)
    {
        return false;
    }
    if(tor->odlegloscpomiedzypkt(this->przodp,car->tylp)<odl-2.0f)
    {
        return false;
    }
    if(tor->odlegloscpomiedzypkt(Punkt(this->posx,this->posy),Punkt(car->posx,car->posy))<odl-3)
        return false;

    return true;
}


void Auto::a()
{
    vsilnikopony=opony->getwspv()*vmax*0.9f*silnik->getmoc();
    if(predkoscoptymalna>vsilnikopony)
    {
        predkoscoptymalna=vsilnikopony;
    }
    if(predkosc<predkoscoptymalna)
    {
        predkosc+=przyspieszenie;
    }
    if(predkosc>predkoscoptymalna)
    {
        predkosc-=hamowanie;
    }
    if(predkosc<0)
    {
        predkosc =0;
    }
}

void Auto::stanupdate()
{
    if(opony->getstan()||silnik->getstan())
    {
        popsuty=true;
    }
}

int Auto::postepokrazenia()
{
    return (int)((t/((float)trasa.size()-1.0f))*100.0f);
}

bool Auto::odsteptyl(float odl, Punkt A,Auto*car)
{
    if(tor->odlegloscpomiedzypkt(A,car->tyl)< odl-2)
        return false;
    if(tor->odlegloscpomiedzypkt(A,car->tylp)<odl-2)
        return false;
    if(tor->odlegloscpomiedzypkt(A,car->tyll)<odl-2)
        return false;
    if(tor->odlegloscpomiedzypkt(A,car->bokl)<odl-4)
        return false;
    if(tor->odlegloscpomiedzypkt(A,car->bokp)<odl-4)
        return false;
    if(tor->odlegloscpomiedzypkt(A,car->przod)< odl-2)
        return false;
    if(tor->odlegloscpomiedzypkt(A,car->przodp)<odl-3)
        return false;
    if(tor->odlegloscpomiedzypkt(A,car->przodl)<odl-3)
        return false;
    if(tor->odlegloscpomiedzypkt(A,Punkt(car->posx,car->posy))<odl)
        return false;
    return true;

}


Kierowca *Auto::getkierowca() const
{
    return kierowca;
}

void Auto::setpozycja(int poz)
{
    pozycja = poz;
}

Opony *Auto::getopony() const
{
    return opony;
}

Silnik *Auto::getsilnik() const
{
    return silnik;
}

bool Auto::getstan() const
{
    return popsuty;
}

int Auto::getokrazenie() const
{
    return okrazenie;
}

std::vector<Fragmenttoru> Auto::gettrasa() const
{
    return trasa;
}

float Auto::getpozstand() const
{
    return t;
}

float Auto::getkierunek() const
{
    return kierunek;
}

float Auto::getposx() const
{
    return posx;
}

float Auto::getposy() const
{
    return posy;
}



void Auto::wyprzedzanieautaprzed(int t1, int t2, std::vector<Auto *> Auta)
{
    if(Auta.size()>0)
    {
        float v =10000;
        bool czymozliwe = false;
        bool czydalej=true;
        float odleglosc=1000;
        float odlegloscv2 = 1000;
        float minodlegloscv2 = 1000;
        float minodleglosc=1000;
        bool czyzablisko=false;
        int nrszr=0;
        int nrszr2=0;
        for(size_t i=0;i< trasa[t1].getvectorpktszer().size(); i++)
        {
            odlegloscv2=tor->odlegloscpomiedzypkt(Punkt(posx,posy),trasa[t1].getpktszer(i));
            if(odlegloscv2<minodlegloscv2)
            {
                minodlegloscv2=odlegloscv2;
                nrszr2=(int)i;
            }
             for(size_t j=0;j< Auta.size(); j++)
             {
                 if(!odleglosctylprzod(5.5f*kierowca->getwspagresji(),Auta[j]))
                 {
                     czyzablisko=true;
                     v=Auta[j]->predkosc;
                 }
                 if(!odsteptyl(16.0f*kierowca->getwspagresji(),trasa[t1].getpktszer(i),Auta[j])&&predkosc>=Auta[j]->predkosc)
                 {
                     czydalej=false;
                     break;
                 }
                 else
                 {
                     czydalej=true;
                 }
             }
                \
             if(czydalej)
             {
                 odleglosc=tor->odlegloscpomiedzypkt(Punkt(posx,posy),trasa[t1].getpktszer(i));
                 if(odleglosc<minodleglosc)
                 {
                     minodleglosc=odleglosc;
                     nrszr=(int)i;
                     czymozliwe=true;
                 }
             }

        }
        if(czymozliwe&&!czyzablisko)
        {
            trasa[t1].setstart(trasa[t1].getpktszer(nrszr));
            predkoscoptymalna = vsilnikopony;

        }
        else if(czymozliwe&&czyzablisko)
        {
            trasa[t1].setstart(trasa[t1].getpktszer(nrszr));
            predkoscoptymalna = 0.4f*predkosc;
        }
        else
        {
            trasa[t1].setstart(trasa[t1].getpktszer(nrszr2));
            predkoscoptymalna=0.4f*predkosc;

        }
        czymozliwe = false;
        minodlegloscv2=1000;
        minodleglosc=1000;
        for(size_t i=0;i< trasa[t1].getvectorpktszer().size(); i++)
        {
             for(size_t j=0;j< Auta.size(); j++)
             {
                 odlegloscv2=tor->odlegloscpomiedzypkt(trasa[t1].getstart(),trasa[t2].getpktszer(i));
                 if(odlegloscv2<minodleglosc)
                 {
                     minodleglosc=odlegloscv2;
                     nrszr=(int)i;
                 }
                 if(odsteptyl(16*kierowca->getwspagresji(),trasa[t2].getpktszer(i),Auta[j])&&predkosc>=Auta[j]->predkosc)
                 {
                     if(odlegloscv2<minodlegloscv2)
                     {
                         minodlegloscv2=odlegloscv2;
                         nrszr2=(int)i;
                         czymozliwe=true;
                     }

                 }
             }
        }
        if(czymozliwe)
        {
             trasa[t2].setstart(trasa[t2].getpktszer(nrszr2));
        }
        else
        {
           trasa[t2].setstart(trasa[t2].getpktszer(nrszr));
        }

    }
    else
        predkoscoptymalna=vsilnikopony;

}





