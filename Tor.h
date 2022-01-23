#ifndef TOR_H
#define TOR_H
#include<Punkt.h>
#include<vector>
#include<iostream>
#include<cmath>
#include<Fragmenttoru.h>


/** Klasa toru odpowiedzialna za tworzenie go i generowanie tras*/
class Tor
{
private:
    std::vector<Fragmenttoru> fragmenty;
    std::vector<Punkt> krawedzL;
    std::vector<Punkt> krawedzP;
    std::vector<Punkt> centrum;
    std::vector<Punkt> punkty;
    float szer;
    float tab[200];

public:
    /** Konstruktor klasy tor */
    Tor();
    ~Tor();

    /** Metoda odpowiedzialna za przeprowadzenie obliczen na punktach z ktorych zostanie utworzony tor */
    void inicjalizacjatoru();

    /** Metoda obliczajaca punkt splajnu dla danego wektora punktow
     * @param t - droga od poczatku splajnu na koncu ktorej zostanie obliczony punkt
     * @param punkty - vector punktow splajnu */
    Punkt obliczpunktsplajnu(float t,std::vector<Punkt> punkty);

    /** Metoda obliczajaca punkt splajnu dla danego wektora fragmentow
     * @param t - droga od poczatku splajnu na koncu ktorej zostanie obliczony punkt
     * @param punkty - vector fragmentow splajnu */
    Punkt obliczpunktsplajnufragmentu(float t, std::vector<Fragmenttoru> punkty);

    /** Metoda obliczajaca gradeint danego miejsca splajnu dla danego wektora fragmentow
     * @param t - droga od poczatku splajnu na koncu ktorej zostanie obliczony gradient
     * @param punkty - vector fragmentow splajnu */
    float obliczgradientpunktufrag(float t, std::vector<Fragmenttoru> punkty);

    /** Metoda obliczajaca gradient danego miejsca splajnu dla danego wektora punktow
     * @param t - droga od poczatku splajnu na koncu ktorej zostanie obliczony gradient
     * @param punkty - vector punktow splajnu */
    float obliczgradientpunktu(float t,std::vector<Punkt> punkty);

    /** Metoda tworzaca lewa krawedz toru
     * @param szer - szerokosc toru
     * @param grad - vector gradeintow potrzebny do oblcizenia pozycji krawedzi wzgledem srodka toru
     * @param sr - vector punktow splajnu srodka toru */
    std::vector<Punkt> krawedzieL(float szer,std::vector<float> grad, std::vector<Punkt> sr );

    /** Metoda tworzaca prawa krawedz toru
     * @param szer - szerokosc toru
     * @param grad - vector gradeintow potrzebny do oblcizenia pozycji krawedzi wzgledem srodka toru
     * @param sr - vector punktow splajnu srodka toru */
    std::vector<Punkt> krawedzieP(float szer,std::vector<float> grad, std::vector<Punkt> sr);

    /** Metoda oblcizajaca dlugosc odcinka splajnu
     * @param i - numer fragmentu dla ktorego zostanie obliczona dlugosc
     * @param fragmenty - vector fragmentow
     * @param przedzial - okresla z jakim przyblizeniem bedzie obliczana dlugosc pomniejszych odcinkow
     * */
    float obliczodleglosc(int i, std::vector<Fragmenttoru> fragmenty, float przedzial);

    /** Metoda obliczajaca odleglosci pomiedzy dwoma punktami*/
    float odlegloscpomiedzypkt(Punkt A, Punkt B);

    /** Metoda obliczajaca punkt gradientu
     * @param numer odcinka
     * @param vector punktow splajnu
     * */
    Punkt obliczpunktgradientu(float t,std::vector<Punkt> punkty);

    /** Oblciza dlugosc calej trasy
     * @param fragmenty - vector fragmentow trasy
     * */
    float obliczdlugosctrasy(std::vector<Fragmenttoru> fragmenty);

    /** Metoda obliczajaca standaryzowana pozycje na trasie
     * @param przemieszczenie - pokonana odleglosc trasy
     * @param fragmenty - vector fragmentow trasy
     * */
    float obliczstandaryzowanatrase(float przemieszczenie,std::vector<Fragmenttoru> fragmenty);

    /** Metoda oblcizajaca optymalna trase
     * @param wsp - okresla jakie zapasay bezpieczenstwa przyjmie trasa*/
    std::vector<Fragmenttoru> obliczoptymalnatrase(float wsp);


    /** Metoda oblcizajaca punkty szerokosci dla danego vectora fragmentow
     * @param wsp - okresla jakie zapasay bezpieczenstwa przyjmie szerokosc*/
    std::vector<Fragmenttoru> utworzpunktyszer(std::vector<Fragmenttoru> frag, float wsp);

    /** Getter toru */
    std::vector<Fragmenttoru> gettor() const;

    /** Getter splanu srodka toeu*/
    std::vector<Punkt> getcentrum() const;

    /** Getter lewej krawedzi toru */
    std::vector<Punkt> getkrawedzL() const;

    /** Getter prawej krawedzi toru */
    std::vector<Punkt> getkrawedzP() const;





};

#endif // TOR_H
