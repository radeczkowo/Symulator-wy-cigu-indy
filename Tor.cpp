#include "Tor.h"


Tor::Tor()
{
    this->punkty ={ {450, 50},{700, 50}, {800, 50},{910, 200},{800, 300},{700, 400},{700, 700},{150, 700},{140, 50},{160, 50}};
    szer = 60;
     inicjalizacjatoru();

}

Tor::~Tor()
{

}

void Tor::inicjalizacjatoru()
{
    std::vector<Fragmenttoru> pomocnik;
    std::vector<Fragmenttoru> pomocnikv2;
    std::vector<Punkt> srpunkty;
    std::vector<float> grad;

    for(int i=0;i<100;i++)
    {
        tab[i]=0;
    }

    for(size_t i=0;i<punkty.size();i++)
    {
       pomocnik.push_back(Fragmenttoru(punkty[i]));
    }
    for(size_t i=0;i<pomocnik.size();i++)
    {
        pomocnik[i].setdlugosc(obliczodleglosc((int)i,pomocnik,0.02f));
    }
    float w = obliczdlugosctrasy(pomocnik);
   // std::cout << w << std::endl;

    for(float i=0;i<w;i+=45)
    {
        float t=obliczstandaryzowanatrase(i,pomocnik);
        Punkt A=obliczpunktsplajnufragmentu(t,pomocnik);
        centrum.push_back(A);
        srpunkty.push_back(A);
        grad.push_back(obliczgradientpunktufrag(t,pomocnik));
        fragmenty.push_back(Fragmenttoru(A));
    }


    krawedzL= krawedzieL(60,grad, srpunkty);
    krawedzP= krawedzieP(60,grad, srpunkty);

     for(size_t i=0;i<fragmenty.size();i++)
     {
         fragmenty[i].setdlugosc(obliczodleglosc((int)i,fragmenty,0.02f));
     }
     fragmenty = utworzpunktyszer(fragmenty,0.6f);




}




Punkt Tor::obliczpunktsplajnufragmentu(float t,std::vector<Fragmenttoru> punkty)
{
    int p0,p1,p2,p3;
    float t0,t1,t2,t3;

    p1 = (int)t;

    if(p1==(int)punkty.size()-1){
        p0=p1-1;
        p2=0;
        p3=1;
    }
    else if(p1==(int)punkty.size()-2){
        p0=p1-1;
        p2=p1+1;
        p3=0;
    }
    else if(p1==0){
        p0=((int)punkty.size())-1;
        p2=p1+1;
        p3=p1+2;
    }
    else
    {
        p0=p1-1;
        p2=p1+1;
        p3=p1+2;
    }
    t0=0.0;
    t1= sqrt(pow(punkty[p1].getstart().x-punkty[p0].getstart().x,2)+pow(punkty[p1].getstart().y-punkty[p0].getstart().y,2))+ t0;
    t2= sqrt(pow(punkty[p2].getstart().x-punkty[p1].getstart().x,2)+pow(punkty[p2].getstart().y-punkty[p1].getstart().y,2))+ t1;
    t3= sqrt(pow(punkty[p3].getstart().x-punkty[p2].getstart().x,2)+pow(punkty[p3].getstart().y-punkty[p2].getstart().y,2))+ t2;

    t = t - (int)t;
    //t= t1+(t2-t1)*t*fragmenty[p1].dlugosc/najdluzszyodc;
    t= t1+(t2-t1)*t;
    Punkt A1, A2, A3, B1, B2, C;
    A1.x = (t1-t)/(t1-t0)*punkty[p0].getstart().x + (t-t0)/(t1-t0)*punkty[p1].getstart().x;
    A1.y = (t1-t)/(t1-t0)*punkty[p0].getstart().y + (t-t0)/(t1-t0)*punkty[p1].getstart().y;

    A2.x = (t2-t)/(t2-t1)*punkty[p1].getstart().x + (t-t1)/(t2-t1)*punkty[p2].getstart().x;
    A2.y = (t2-t)/(t2-t1)*punkty[p1].getstart().y + (t-t1)/(t2-t1)*punkty[p2].getstart().y;

    A3.x = (t3-t)/(t3-t2)*punkty[p2].getstart().x + (t-t2)/(t3-t2)*punkty[p3].getstart().x;
    A3.y = (t3-t)/(t3-t2)*punkty[p2].getstart().y + (t-t2)/(t3-t2)*punkty[p3].getstart().y;

    B1.x = (t2-t)/(t2-t0)*A1.x + (t-t0)/(t2-t0)*A2.x;
    B1.y = (t2-t)/(t2-t0)*A1.y + (t-t0)/(t2-t0)*A2.y;

    B2.x = (t3-t)/(t3-t1)*A2.x + (t-t1)/(t3-t1)*A3.x;
    B2.y = (t3-t)/(t3-t1)*A2.y + (t-t1)/(t3-t1)*A3.y;

    C.x = (t2-t)/(t2-t1)*B1.x + (t-t1)/(t2-t1)*B2.x;
    C.y = (t2-t)/(t2-t1)*B1.y + (t-t1)/(t2-t1)*B2.y;

    return C;
}
float Tor::obliczgradientpunktufrag(float t, std::vector<Fragmenttoru> punkty)
{
    int p0,p1,p2,p3;
    float t0,t1,t2,t3;


    Punkt A;

    p1 = (int)t;

    if(p1==(int)punkty.size()-1){
        p0=p1-1;
        p2=0;
        p3=1;
    }
    else if(p1==(int)punkty.size()-2){
        p0=p1-1;
        p2=p1+1;
        p3=0;
    }
    else if(p1==0){
        p0=((int)punkty.size())-1;
        p2=p1+1;
        p3=p1+2;
    }
    else
    {
        p0=p1-1;
        p2=p1+1;
        p3=p1+2;
    }

    t0=0.0;
    t1= sqrt(pow(punkty[p1].getstart().x-punkty[p0].getstart().x,2)+pow(punkty[p1].getstart().y-punkty[p0].getstart().y,2))+ t0;
    t2= sqrt(pow(punkty[p2].getstart().x-punkty[p1].getstart().x,2)+pow(punkty[p2].getstart().y-punkty[p1].getstart().y,2))+ t1;
    t3= sqrt(pow(punkty[p3].getstart().x-punkty[p2].getstart().x,2)+pow(punkty[p3].getstart().y-punkty[p2].getstart().y,2))+ t2;

    t = t - (int)t;
    t= t1+(t2-t1)*t;
    Punkt A1, A2, A3, B1, B2, C;
    A1.x = (t1-t)/(t1-t0)*punkty[p0].getstart().x + (t-t0)/(t1-t0)*punkty[p1].getstart().x;
    A1.y = (t1-t)/(t1-t0)*punkty[p0].getstart().y + (t-t0)/(t1-t0)*punkty[p1].getstart().y;

    A2.x = (t2-t)/(t2-t1)*punkty[p1].getstart().x + (t-t1)/(t2-t1)*punkty[p2].getstart().x;
    A2.y = (t2-t)/(t2-t1)*punkty[p1].getstart().y + (t-t1)/(t2-t1)*punkty[p2].getstart().y;

    A3.x = (t3-t)/(t3-t2)*punkty[p2].getstart().x + (t-t2)/(t3-t2)*punkty[p3].getstart().x;
    A3.y = (t3-t)/(t3-t2)*punkty[p2].getstart().y + (t-t2)/(t3-t2)*punkty[p3].getstart().y;

    B1.x = (t2-t)/(t2-t0)*A1.x + (t-t0)/(t2-t0)*A2.x;
    B1.y = (t2-t)/(t2-t0)*A1.y + (t-t0)/(t2-t0)*A2.y;

    B2.x = (t3-t)/(t3-t1)*A2.x + (t-t1)/(t3-t1)*A3.x;
    B2.y = (t3-t)/(t3-t1)*A2.y + (t-t1)/(t3-t1)*A3.y;

    C.x = (t2-t)/(t2-t1)*B1.x + (t-t1)/(t2-t1)*B2.x;
    C.y = (t2-t)/(t2-t1)*B1.y + (t-t1)/(t2-t1)*B2.y;

    Punkt A1poch, A2poch, A3poch, B1poch, B2poch, Cpoch;

    A1poch.x = (1/(t1-t0))*(punkty[p1].getstart().x-punkty[p0].getstart().x);
    A1poch.y = (1/(t1-t0))*(punkty[p1].getstart().y-punkty[p0].getstart().y);

    A2poch.x = (1/(t2-t1))*(punkty[p2].getstart().x-punkty[p1].getstart().x);
    A2poch.y = (1/(t2-t1))*(punkty[p2].getstart().y-punkty[p1].getstart().y);

    A3poch.x = (1/(t3-t2))*(punkty[p3].getstart().x-punkty[p2].getstart().x);
    A3poch.y = (1/(t3-t2))*(punkty[p3].getstart().y-punkty[p2].getstart().y);

    B1poch.x = (1/(t2-t0))*(A2.x-A1.x) + ((t2-t)/(t2-t0))*A1poch.x + ((t-t0)/(t2-t0))*A2poch.x;
    B1poch.y = (1/(t2-t0))*(A2.y-A1.y) + ((t2-t)/(t2-t0))*A1poch.y + ((t-t0)/(t2-t0))*A2poch.y;

    B2poch.x = (1/(t3-t1))*(A3.x-A2.x) + ((t3-t)/(t3-t1))*A2poch.x + ((t-t1)/(t3-t1))*A3poch.x;
    B2poch.y = (1/(t3-t1))*(A3.y-A2.y) + ((t3-t)/(t3-t1))*A2poch.y + ((t-t1)/(t3-t1))*A3poch.y;

    Cpoch.x = (1/(t2-t1))*(B2.x-B1.x) + ((t2-t)/(t2-t1))*B1poch.x + ((t-t1)/(t2-t1))*B2poch.x;
    Cpoch.y = (1/(t2-t1))*(B2.y-B1.y) + ((t2-t)/(t2-t1))*B1poch.y + ((t-t1)/(t2-t1))*B2poch.y;

    return atan2(-Cpoch.y,Cpoch.x);

}



Punkt Tor::obliczpunktsplajnu(float t,std::vector<Punkt> punkty)
{
    int p0,p1,p2,p3;
    float t0,t1,t2,t3;

    p1 = (int)t;

    if(p1==(int)punkty.size()-1){
        p0=p1-1;
        p2=0;
        p3=1;
    }
    else if(p1==(int)punkty.size()-2){
        p0=p1-1;
        p2=p1+1;
        p3=0;
    }
    else if(p1==0){
        p0=((int)punkty.size())-1;
        p2=p1+1;
        p3=p1+2;
    }
    else
    {
        p0=p1-1;
        p2=p1+1;
        p3=p1+2;
    }
    t0=0.0;
    t1= sqrt(pow(punkty[p1].x-punkty[p0].x,2)+pow(punkty[p1].y-punkty[p0].y,2))+ t0;
    t2= sqrt(pow(punkty[p2].x-punkty[p1].x,2)+pow(punkty[p2].y-punkty[p1].y,2))+ t1;
    t3= sqrt(pow(punkty[p3].x-punkty[p2].x,2)+pow(punkty[p3].y-punkty[p2].y,2))+ t2;

    t = t - (int)t;
    //t= t1+(t2-t1)*t*fragmenty[p1].dlugosc/najdluzszyodc;
    t= t1+(t2-t1)*t;
    Punkt A1, A2, A3, B1, B2, C;
    A1.x = (t1-t)/(t1-t0)*punkty[p0].x + (t-t0)/(t1-t0)*punkty[p1].x;
    A1.y = (t1-t)/(t1-t0)*punkty[p0].y + (t-t0)/(t1-t0)*punkty[p1].y;

    A2.x = (t2-t)/(t2-t1)*punkty[p1].x + (t-t1)/(t2-t1)*punkty[p2].x;
    A2.y = (t2-t)/(t2-t1)*punkty[p1].y + (t-t1)/(t2-t1)*punkty[p2].y;

    A3.x = (t3-t)/(t3-t2)*punkty[p2].x + (t-t2)/(t3-t2)*punkty[p3].x;
    A3.y = (t3-t)/(t3-t2)*punkty[p2].y + (t-t2)/(t3-t2)*punkty[p3].y;

    B1.x = (t2-t)/(t2-t0)*A1.x + (t-t0)/(t2-t0)*A2.x;
    B1.y = (t2-t)/(t2-t0)*A1.y + (t-t0)/(t2-t0)*A2.y;

    B2.x = (t3-t)/(t3-t1)*A2.x + (t-t1)/(t3-t1)*A3.x;
    B2.y = (t3-t)/(t3-t1)*A2.y + (t-t1)/(t3-t1)*A3.y;

    C.x = (t2-t)/(t2-t1)*B1.x + (t-t1)/(t2-t1)*B2.x;
    C.y = (t2-t)/(t2-t1)*B1.y + (t-t1)/(t2-t1)*B2.y;

    return C;
}

Punkt Tor::obliczpunktgradientu(float t,std::vector<Punkt> punkty)
{
    int p0,p1,p2,p3;
    float t0,t1,t2,t3;


    Punkt A;

    p1 = (int)t;

    if(p1==(int)punkty.size()-1){
        p0=p1-1;
        p2=0;
        p3=1;
    }
    else if(p1==(int)punkty.size()-2){
        p0=p1-1;
        p2=p1+1;
        p3=0;
    }
    else if(p1==0){
        p0=((int)punkty.size())-1;
        p2=p1+1;
        p3=p1+2;
    }
    else
    {
        p0=p1-1;
        p2=p1+1;
        p3=p1+2;
    }

    t0=0.0;
    t1= sqrt(pow(punkty[p1].x-punkty[p0].x,2)+pow(punkty[p1].y-punkty[p0].y,2))+ t0;
    t2= sqrt(pow(punkty[p2].x-punkty[p1].x,2)+pow(punkty[p2].y-punkty[p1].y,2))+ t1;
    t3= sqrt(pow(punkty[p3].x-punkty[p2].x,2)+pow(punkty[p3].y-punkty[p2].y,2))+ t2;

    t = t - (int)t;
    //t= t1+(t2-t1)*t*fragmenty[p1].dlugosc/najdluzszyodc;
    t= t1+(t2-t1)*t;
    Punkt A1, A2, A3, B1, B2, C;
    A1.x = (t1-t)/(t1-t0)*punkty[p0].x + (t-t0)/(t1-t0)*punkty[p1].x;
    A1.y = (t1-t)/(t1-t0)*punkty[p0].y + (t-t0)/(t1-t0)*punkty[p1].y;

    A2.x = (t2-t)/(t2-t1)*punkty[p1].x + (t-t1)/(t2-t1)*punkty[p2].x;
    A2.y = (t2-t)/(t2-t1)*punkty[p1].y + (t-t1)/(t2-t1)*punkty[p2].y;

    A3.x = (t3-t)/(t3-t2)*punkty[p2].x + (t-t2)/(t3-t2)*punkty[p3].x;
    A3.y = (t3-t)/(t3-t2)*punkty[p2].y + (t-t2)/(t3-t2)*punkty[p3].y;

    B1.x = (t2-t)/(t2-t0)*A1.x + (t-t0)/(t2-t0)*A2.x;
    B1.y = (t2-t)/(t2-t0)*A1.y + (t-t0)/(t2-t0)*A2.y;

    B2.x = (t3-t)/(t3-t1)*A2.x + (t-t1)/(t3-t1)*A3.x;
    B2.y = (t3-t)/(t3-t1)*A2.y + (t-t1)/(t3-t1)*A3.y;

    C.x = (t2-t)/(t2-t1)*B1.x + (t-t1)/(t2-t1)*B2.x;
    C.y = (t2-t)/(t2-t1)*B1.y + (t-t1)/(t2-t1)*B2.y;

    Punkt A1poch, A2poch, A3poch, B1poch, B2poch, Cpoch;

    A1poch.x = (1/(t1-t0))*(punkty[p1].x-punkty[p0].x);
    A1poch.y = (1/(t1-t0))*(punkty[p1].y-punkty[p0].y);

    A2poch.x = (1/(t2-t1))*(punkty[p2].x-punkty[p1].x);
    A2poch.y = (1/(t2-t1))*(punkty[p2].y-punkty[p1].y);

    A3poch.x = (1/(t3-t2))*(punkty[p3].x-punkty[p2].x);
    A3poch.y = (1/(t3-t2))*(punkty[p3].y-punkty[p2].y);

    B1poch.x = (1/(t2-t0))*(A2.x-A1.x) + ((t2-t)/(t2-t0))*A1poch.x + ((t-t0)/(t2-t0))*A2poch.x;
    B1poch.y = (1/(t2-t0))*(A2.y-A1.y) + ((t2-t)/(t2-t0))*A1poch.y + ((t-t0)/(t2-t0))*A2poch.y;

    B2poch.x = (1/(t3-t1))*(A3.x-A2.x) + ((t3-t)/(t3-t1))*A2poch.x + ((t-t1)/(t3-t1))*A3poch.x;
    B2poch.y = (1/(t3-t1))*(A3.y-A2.y) + ((t3-t)/(t3-t1))*A2poch.y + ((t-t1)/(t3-t1))*A3poch.y;

    Cpoch.x = (1/(t2-t1))*(B2.x-B1.x) + ((t2-t)/(t2-t1))*B1poch.x + ((t-t1)/(t2-t1))*B2poch.x;
    Cpoch.y = (1/(t2-t1))*(B2.y-B1.y) + ((t2-t)/(t2-t1))*B1poch.y + ((t-t1)/(t2-t1))*B2poch.y;

    return Cpoch;

}

float Tor::obliczgradientpunktu(float t,std::vector<Punkt> punkty)
{
    Punkt A=obliczpunktgradientu(t,punkty);
    return atan2(-A.y,A.x);
}


std::vector<Punkt> Tor::krawedzieL(float szer, std::vector<float> grad, std::vector<Punkt> sr)
{
    std::vector<Punkt> krawedzLL;

    for( size_t i = 0; i < sr.size(); i++ ){

        krawedzLL.push_back(Punkt(szer/2 * sin(grad[i]) + sr[i].x, szer/2 * cos(grad[i]) + sr[i].y));
    }
    return krawedzLL;

}

std::vector<Punkt> Tor::krawedzieP(float szer, std::vector<float> grad, std::vector<Punkt> sr)
{
    std::vector<Punkt> krawedzPP;
    for( size_t i = 0; i < sr.size(); i++ ){

        krawedzPP.push_back(Punkt(-szer/2 * sin(grad[i]) + sr[i].x,- szer/2 * cos(grad[i]) + sr[i].y));
    }
    return krawedzPP;

}

float Tor::obliczodleglosc(int i, std::vector<Fragmenttoru> fragmenty, float przedzial)
{
    float odleglosc=0;
    Punkt POP=obliczpunktsplajnufragmentu(float(i),fragmenty);
    Punkt OBE;

     for(float t=0.0;t<0.99999;t+=przedzial)
     {
         OBE = obliczpunktsplajnufragmentu(float(i) +t, fragmenty);
         odleglosc+=odlegloscpomiedzypkt(POP,OBE);
         POP = OBE;

     }

    return odleglosc;
}

float Tor::odlegloscpomiedzypkt(Punkt A, Punkt B)
{
    return sqrt(pow(B.x-A.x,2)+pow(B.y-A.y,2));
}



float Tor::obliczdlugosctrasy(std::vector<Fragmenttoru> fragmenty)
{
    float dlugosctrasy = 0;
    for( size_t i = 0; i < fragmenty.size(); i++ )
    {
          dlugosctrasy+=fragmenty[i].getdlugoc();
    }
    return dlugosctrasy;
 }


float Tor::obliczstandaryzowanatrase(float przemieszczenie, std::vector<Fragmenttoru> fragmenty)
{

   int nrwezla=0;
   while(przemieszczenie>fragmenty[nrwezla].getdlugoc())
   {
    przemieszczenie-=fragmenty[nrwezla].getdlugoc();
    nrwezla++;
   }

   return (float)nrwezla +przemieszczenie/fragmenty[nrwezla].getdlugoc();

}

std::vector<Fragmenttoru> Tor::obliczoptymalnatrase(float wsp)
{
    std::vector<Fragmenttoru> optymalnatrasa;
    optymalnatrasa=fragmenty;
    for(size_t i=0;i<fragmenty.size();i++)
    {
        optymalnatrasa[i].getvectorpktszer().clear();
    }
    optymalnatrasa = utworzpunktyszer(optymalnatrasa, wsp);
    for(int n=0; n< 50;n++)
    {
        Punkt lewy,srodkowy,prawy,norlewy,norprawy,weklewy,wekprawy,wekwypadkowy,wypadkowynor,centralny,norcentralny;
        float dlugosclewy, dlugoscprawy, dlugoscwyp, centralnydlugosc;

        for(size_t i =0;i<optymalnatrasa.size();i++)
        {
            if(i==optymalnatrasa.size()-1)
            {
                lewy=(optymalnatrasa[i-1].getstart());
                srodkowy=(optymalnatrasa[i].getstart());
                prawy=(optymalnatrasa[0].getstart());
            }
            else if(i==0)
            {
                lewy=(optymalnatrasa[optymalnatrasa.size()-1].getstart());
                srodkowy=(optymalnatrasa[i].getstart());
                prawy=(optymalnatrasa[i+1].getstart());
            }
            else
            {
                lewy=(optymalnatrasa[i-1].getstart());
                srodkowy=(optymalnatrasa[i].getstart());
                prawy=(optymalnatrasa[i+1].getstart());
            }


            weklewy.x=lewy.x-srodkowy.x;
            weklewy.y=lewy.y-srodkowy.y;
            wekprawy.x=prawy.x-srodkowy.x;
            wekprawy.y=prawy.y-srodkowy.y;

            dlugosclewy= sqrt(weklewy.x*weklewy.x+weklewy.y*weklewy.y);
            if(dlugosclewy==0)
            {
                dlugosclewy= 1;
            }
            dlugoscprawy= sqrt(wekprawy.x*wekprawy.x+wekprawy.y*wekprawy.y);
            if(dlugoscprawy==0)
            {
                dlugoscprawy= 1;
            }

            norlewy.x = weklewy.x/dlugosclewy;
            norlewy.y = weklewy.y/dlugosclewy;
            norprawy.x = wekprawy.x/dlugoscprawy;
            norprawy.y = wekprawy.y/dlugoscprawy;


            wekwypadkowy.x=norlewy.x+norprawy.x;
            wekwypadkowy.y= norlewy.y+norprawy.y;
            dlugoscwyp = sqrt(wekwypadkowy.x*wekwypadkowy.x+wekwypadkowy.y*wekwypadkowy.y);
            if(dlugoscwyp==0)
            {
                dlugoscwyp=1;
            }
            wypadkowynor.x = wekwypadkowy.x/dlugoscwyp;
            wypadkowynor.y = wekwypadkowy.y/dlugoscwyp;
            centralny =obliczpunktgradientu((float)i,centrum);

            centralnydlugosc = sqrt(centralny.x*centralny.x + centralny.y*centralny.y);
            if(centralnydlugosc==0)
            {
                centralnydlugosc=1;
            }
            norcentralny.x=centralny.x/centralnydlugosc;
            norcentralny.y=centralny.y/centralnydlugosc;
            float iloczynskalarny= - norcentralny.y*wypadkowynor.x+norcentralny.x*wypadkowynor.y;
            tab[i] += (iloczynskalarny*2.3f);


        }


        for (size_t i = 0; i < centrum.size(); i++)
                    {
                        if (tab[i] >= szer/2/(0.4f+wsp))
                        {
                           tab[i] = szer/2/(0.4f+wsp);
                        }

                        if (tab[i] <= -szer/2/(0.4f+wsp))
                        {
                            tab[i] = -szer/2/(0.4f+wsp);
                        }
                        Punkt g = obliczpunktgradientu((float)i, centrum);
                        float glen = sqrtf(g.x*g.x + g.y*g.y);     
                        if(glen==0)
                        {
                            glen =1;
                        }
                        g.x /= glen; g.y /= glen;

                        optymalnatrasa[i].setstartx(centrum[i].x  - g.y * tab[i]);
                        optymalnatrasa[i].setstarty(centrum[i].y  + g.x * tab[i]);
                    }
    }
    return optymalnatrasa;
}

std::vector<Fragmenttoru> Tor::utworzpunktyszer(std::vector<Fragmenttoru> frag, float wsp)
{
    Punkt B;
    for(size_t i=0; i<fragmenty.size()-1; i++)
    {
        float d = obliczgradientpunktufrag((float)i,fragmenty);
        for(float j= -((szer/2)/(0.4f+wsp));j<=((szer/2)/(0.4f+wsp));j+=2.0f)
        {
            B.x = (j * sin(d) + fragmenty[i].getstart().x);
            B.y = (j* cos(d) + fragmenty[i].getstart().y);
            frag[i].dodajpktszer(B);
        }
    }
    return frag;
}

std::vector<Fragmenttoru> Tor::gettor() const
{
    return fragmenty;
}

std::vector<Punkt> Tor::getcentrum() const
{
    return centrum;
}

std::vector<Punkt> Tor::getkrawedzL() const
{
    return krawedzL;

}

std::vector<Punkt> Tor::getkrawedzP() const
{
    return krawedzP;
}





