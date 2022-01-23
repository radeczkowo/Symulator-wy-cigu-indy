#ifndef SYMULATOR_H
#define SYMULATOR_H
#include<QTimer>
#include<Menadzertorow.h>
#include<Parkmaszyn.h>
#include<Scena.h>

/** Klasa symulatora odpowiedzialna za przebieg wyscigu */
class Symulator
{
private:
    QTimer *timer;
    int t=0;
    int n=0;
    Scena *scena;
    Parkmaszyn * pmaszyn;
    Menadzertorow * mentorow;
    QPushButton * start;
    int ileukonczylo;
    int liczbaokrazen;
    int biezaceokr;

public:
    /** Konstruktor symulatora
     * @param *scena - wskaznik do sceny w celu przeprowadzenia wysciguw  foie graficznej
     * @param *pmaszyn - wskaznik do parku maszyn w celu uzyskana dostepu do aut
     * @param mentorow - wskaznik do menadzera torow w celu uzyskania dostepu do toru
     * @param liczbaokrazen - liczba okrazaen wyscigu
     * */
    Symulator(Scena*scena, Parkmaszyn *pmaszyn, Menadzertorow *mentorow, int liczbaokrazen);

    /** Meroda aktualizujaca zachowanie aut i im podleglych klas */
    void autaupdate();

    /** Ustawianie aut przed wysicgiem na starcie */
    void ustawauta();

    /** Obliczanie biezacego rankingu auta w wyscigu*/
    void pozycja();

    /** usuwanie zepsutych aut*/
    void usunauta();

    /** Zaaktualizownie tablei wynikow po ukonczeniu wyscigu przez auto oraz usuwanie go z wyscigu*/
    void ukonczonywyscig();

    /** Sprawdzanie czy wyscig zostal ukonczony*/
    void numeryokrazen();

    /** Aktualizowanie biezacego okrazenia wyscigu*/
    void biezaceokrazenie();
};

#endif // SYMULATOR_H
