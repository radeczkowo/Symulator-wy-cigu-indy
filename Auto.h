#ifndef AUTO_H
#define AUTO_H
#include<Tor.h>
#include<cmath>
#include<Kierowca.h>
#include<Opony.h>
#include<DRS.h>
#include<Boost.h>

/** Klasa opisujaca zachowanie auta*/

class Auto
{
private:
    float predkoscoptymalna;
    float predkosc;
    float vsilnikopony;
    std::vector<Auto*> Auta;
    std::vector<Auto*> Autaobok;
    Punkt przod,tyl,przodl,przodp,tyll,tylp,bokl,bokp;
    float przyspieszenie;
    std::vector<Fragmenttoru> trasaoptymalna;
    float hamowanie;
    float vmax;
    Kierowca *kierowca;
    int pozycja;
    Silnik *silnik;
    Opony *opony;
    bool popsuty;
    int okrazenie;
    std::vector<Fragmenttoru> trasa;
    Tor *tor;
    float t;
    float poz;
    float kierunek;
    float posx, posy;

public:

    /** Konstruktor klasy auto
     * @param v - predkosc maksyalna auta
     * @param a - przyspieszenie auta
     * @param typkierowcy- okresla zachowanie auta na torze
     * @param opony - roszaj opon
     * @param mocsilnika - moc maksymalna silnika
     * @param czydrs - okresla czy zostanie wykrozystany boost czy drs
     * */
    Auto(float v, float a, std::string imiekierowcy, std::string typkierowcy, std::string opony, float mocsilnika, bool czydrs);
    ~Auto();

     /** metoda ustawiajaca auto na starcie
      * @param numer - okresla w jakiej odleglosci od mety i po jakiej stronie toru zanjdzie sie auto na starcie
      * *tor - wskaźnik do toru
      * Auta- vector zawierajacy wszystkie auta na torze, potrzebny do opisywania zachowania auta
      * */
    void ustawpozycjestartowa(int numer, Tor *tor, std::vector<Auto*> Auta);

    /** metoda okreslajaca przesuwanie sie auta na trasie oraz jego zwrot
     * */
    void zmienpozycje();

    /** sprawdza czy w poblizu znajduje sie inne auto
     * */
    void sprawdzczyautowpoblizu();

    /** aktualizuje dlugocs trasy do pokonania na danym odcinku t
     * */
    void zaaktualizujdlugoscodcinka(int t);

    /** funkcja opisujaca zachowanie auta na starcie
     * @param A - opisuje punkt startu danego auta
     * @param poz - opisuja pozycje auta na tracie w formie pokonanej drogi
     * */
    void konfigurujstart(Punkt A,  float poz);

     /** resetowanie drogi auta w na danym odcinku t do optymalnej drogi
      * @param punkty- optymalna trasa
      * */
    void resetujtrase(float t,std::vector<Fragmenttoru> punkty);

    /** metoda opisujaca zachowanie sie auta  na 2 najblizszych odcinkach gdy w poblizu znajduje sie inne auto lub auta
     * @param t1 - numer najblizszy odcinka trasy
     * @param t2 - numer drugiego -||-
     * @param Auta - vector zawierajacy wskazniki do aut w poblizu
     * */
    void wyprzedzanieautaprzed(int t1, int t2,  std::vector<Auto*> Auta);

    /** metoda wywyolujaca wyprzedzanieautaprzed z uszszegolnieniem zachowania w roznych miejscach toru
     * */
    void wyprzedzanie();

    /** metoda obliczajaca punkty na obwodzie auta
     * @param grad - gradient auta potrzenby do policzenia zwrotu
     * @param A - punkt aktualnej pozycji auta(srodka)
      */
    void obliczboki(float grad, Punkt A);

    /** sprawdzenie czy inne auto nie znajduje sie za blisko wybranych punktow danego auta od danych punktow innego auta
     * @param odl - bezpieczna odleglosc
     * @param *car - inne auto
     * */
    bool odleglosctylprzod(float odl, Auto* car);

    /** Okresla zmiany predkosci auta na trasie
     * */
    void a();

    /** sprawdza czy auto jest zdatne do jazdy
     * */
    void stanupdate();

    /** oblicza stopien pokonania okrazenia w formie procentowej
     * */
    int postepokrazenia();

    /** sprawdzenie czy inne auto nie znajduje sie za blisko srodka danego auta od danych punktow innego auta
     * @param odl - bezpieczna odleglosc
     * @param  *car - inne auto
     * @param A - punkt srodka auta
     * */
    bool odsteptyl(float odl, Punkt A, Auto *car);

    /** getter wskaznika do kierowcy
     * */
    Kierowca* getkierowca() const;

    /** setter pozycji auta(w formie postepu trasy)
     * */
    void setpozycja(int poz);

    /** getter wskaznika do opon
     * */
    Opony* getopony() const;

    /** getter wskaznika do silnika
     * */
    Silnik* getsilnik() const;

    /** getter stanu auta
     * */
    bool getstan() const;

    /** getter biezace okrazenia auta
     * */
    int getokrazenie() const;

    /** getter obecnej trasy auta
     * */
    std::vector<Fragmenttoru> gettrasa() const;

    /** getter pozycji standaryzowanej
     * */
    float getpozstand() const;

    /** getter gradientu auta
     * */
    float getkierunek() const;

    /** getter pozycji na osi x auta
     * */
    float getposx() const;

    /** getter pozycji na osi y auta
     * */
    float getposy() const;



};

#endif // AUTO_H
